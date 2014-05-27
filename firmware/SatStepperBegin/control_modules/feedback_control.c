#include <stdlib.h>
#include "utils/macros.h"
#include "state.h"
#include "sensors/encoder/encoder.h"
#include "control_algo.h"
#include "feedback_control.h"

static uint16_t algoStepInEncTicks      = 0;
static uint32_t commAngleInEncTicks     = 0;
static uint32_t minimalMgnVectsMismatch = 0;

static int16_t encTicsInOneAlgoStep() {
    int16_t encoderTicsOnEngineRevol =      gConfig.encoderRange
                                        /   gConfig.motorReduction;
    int16_t algoStepsInOneRevol = getEngineStepMultiplier()
                                    * gConfig.oneRevolEngineSteps;
    return encoderTicsOnEngineRevol / algoStepsInOneRevol;
}

static void recomputeAlgoConsts() {
    algoStepInEncTicks = encTicsInOneAlgoStep();

    commAngleInEncTicks =   gState.currentCommAngle *
                            (uint32_t)algoStepInEncTicks;
    commAngleInEncTicks >>= COMM_ANGLE_RANK;

    minimalMgnVectsMismatch = commAngleInEncTicks - algoStepInEncTicks;
}

static int32_t calculateNextPolePos(int32_t currentPos,
                                    int_fast8_t direction) {
    // int32_t nextSwitchPos = currentPos - currentPos % algoStepInEncTicks
                            // + direction * commAngleInEncTicks;
//
    // return nextSwitchPos;

    int_fast8_t posSign = (currentPos >= 0) ? 1 : -1;

    int32_t nextPolePos =
            currentPos - currentPos % algoStepInEncTicks
            + (int32_t)direction
                * (commAngleInEncTicks
                    - commAngleInEncTicks % algoStepInEncTicks
                    + algoStepInEncTicks);

    nextPolePos += (int32_t)((posSign - direction) / 2)
                    * algoStepInEncTicks;

    return nextPolePos;
}

static void restoreSynchronicity(int32_t currentPos) {
    int32_t trueSteps = (currentPos - gState.reference.encoder)
                        / algoStepInEncTicks;

    if (gState.encoder.direction < 0 && currentPos < 0) {
        trueSteps -= 1;
    } else if (gState.encoder.direction > 0 && currentPos > 0) {
        trueSteps += 1;
    }

    int32_t controlledSteps = gState.stepTicker - gState.reference.stepTicker;

    if (trueSteps != controlledSteps) {
        // gState.stepTicker += trueSteps - controlledSteps;
        gState.stepTicker = gState.reference.stepTicker + trueSteps;
    }
}

#define TARGET_REACHED(currentPos, activePolePos)       \
    activePolePos - algoStepInEncTicks < currentPos     \
    && activePolePos + algoStepInEncTicks > currentPos  \
    && labs(gState.setPoint.position - activePolePos)   \
        <= algoStepInEncTicks / 2

void switchPhasesIfNecessary() {
    int32_t currentPos = ((int32_t)gState.encoder.raw * gConfig.encoderRange
                            + gState.encoder.precise)
                            * gConfig.motorReduction;

    static int32_t activePolePos = 0;

    int_fast8_t direction = (currentPos <= gState.setPoint.position) ? 1 : -1;

    if (activePolePos == 0) {
        activePolePos = calculateNextPolePos(currentPos, direction);
    }

    int32_t magneticVectorsMismatch = activePolePos - currentPos;

    if (TARGET_REACHED(currentPos, activePolePos)) {
        // stop();
        return;
    }
    else if (labs(magneticVectorsMismatch) <= minimalMgnVectsMismatch) {
        activePolePos = calculateNextPolePos(currentPos, direction);
        step(direction);
    }
    else if (labs(magneticVectorsMismatch) > commAngleInEncTicks) {
        restoreSynchronicity(currentPos);
        activePolePos = calculateNextPolePos(currentPos, direction);
        step(direction);
    }
}

void enableFeedbackControl() {
    recomputeAlgoConsts();
    setSharedEncoderHandler(&switchPhasesIfNecessary);
}

void disableFeedbackControl() {
    clearSharedEncoderHandler();
}

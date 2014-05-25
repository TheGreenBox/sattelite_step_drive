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

static int32_t calculateNextSwitchPos(  int32_t currentPos,
                                        int_fast8_t direction) {
    int32_t nextSwitchPos = currentPos - currentPos % algoStepInEncTicks
                            + direction * commAngleInEncTicks;

    return nextSwitchPos;
}

static void restoreSynchronicity(int32_t currentPos) {
    int32_t trueSteps = (currentPos - gState.reference.encTicksToMotor)
                        / algoStepInEncTicks;

    if (gState.encoder.direction < 0 && currentPos < 0) {
        trueSteps -= 1;
    } else if (gState.encoder.direction > 0 && currentPos > 0) {
        trueSteps += 1;
    }

    int32_t controlledSteps = gState.stepTicker - gState.reference.stepTicker;

    if (trueSteps != controlledSteps) {
        gState.stepTicker += trueSteps - controlledSteps;
    }
}

void switchPhasesIfNecessary() {
    int32_t currentPos = ((int32_t)gState.encoder.raw * gConfig.encoderRange
                            + gState.encoder.precise) * gConfig.motorReduction;

    static int32_t thisSwitchPos = 0;

    int_fast8_t direction = (currentPos < gState.setPoint.position) ? 1 : -1;

    if (thisSwitchPos == 0) {
        thisSwitchPos = calculateNextSwitchPos(currentPos, direction);
    }

    int32_t magneticVectorsMismatch = thisSwitchPos - currentPos;

    if (currentPos <= gState.setPoint.position + algoStepInEncTicks
        && currentPos >= gState.setPoint.position - algoStepInEncTicks) {
        thisSwitchPos = currentPos - currentPos % algoStepInEncTicks;
        return;
    }
    else if (labs(magneticVectorsMismatch) <= minimalMgnVectsMismatch) {
        thisSwitchPos = calculateNextSwitchPos(currentPos, direction);
        step(direction);
    }
    else if (labs(magneticVectorsMismatch) > commAngleInEncTicks) {
        restoreSynchronicity(currentPos);
        thisSwitchPos = calculateNextSwitchPos(currentPos, direction);
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

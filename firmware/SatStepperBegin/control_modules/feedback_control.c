#include <stdlib.h>
#include <limits.h>
#include "utils/macros.h"
#include "state.h"
#include "sensors/encoder/encoder.h"
#include "control_algo.h"
#include "feedback_control.h"

static int32_t algoStepInEncTicks      = 0;
static int32_t commAngleInEncTicks     = 0;
static int32_t minimalMgnVectsMismatch = 0;

int32_t getAlgoStepSizeInEncTicks() {
    return algoStepInEncTicks;
}

static int32_t computeOneAlgoStepInEncTicks() {
    int32_t encoderTicsOnEngineRevol =      gConfig.encoderRange
                                        /   gConfig.motorReduction;
    int32_t algoStepsInOneRevol = getEngineStepMultiplier()
                                    * gConfig.oneRevolEngineSteps;
    return encoderTicsOnEngineRevol / algoStepsInOneRevol;
}

void recomputeAlgoConsts() {
    algoStepInEncTicks = computeOneAlgoStepInEncTicks();

    commAngleInEncTicks =   gState.currentCommAngle *
                            (uint32_t)algoStepInEncTicks;
    commAngleInEncTicks >>= COMM_ANGLE_RANK;

    minimalMgnVectsMismatch = commAngleInEncTicks - algoStepInEncTicks;
}

static int32_t experimentalCalculateNextPolePos(int32_t direction) {
    int32_t currentPos = gState.encoder.total;

    int32_t pos;
    if (direction > 0) {
        int32_t T = currentPos + commAngleInEncTicks - algoStepInEncTicks;
        pos = T - T % algoStepInEncTicks;
        pos += algoStepInEncTicks;
    }
    else {
        int32_t D = currentPos - commAngleInEncTicks + algoStepInEncTicks;
        int32_t _remainder = D % algoStepInEncTicks;
        if (_remainder == 0) {
            pos = D;
        }
        else {
            pos = D - D % algoStepInEncTicks + algoStepInEncTicks;
        }
        pos -= algoStepInEncTicks;
    }

    return pos;
}

// TODO: very similar to experimentalCalculateNextPolePos, rework them
static experimentalRestore(int32_t direction) {
    int32_t currentPos = gState.encoder.total - gState.reference.encoder;

    int32_t trueSteps;
    if (direction > 0) {
        int32_t T = currentPos + commAngleInEncTicks - algoStepInEncTicks;
        trueSteps = T / algoStepInEncTicks;
    }
    else {
        int32_t D = currentPos - commAngleInEncTicks + algoStepInEncTicks;
        int32_t _remainder = D % algoStepInEncTicks;
        if (_remainder == 0) {
            trueSteps = D / algoStepInEncTicks;
        }
        else {
            trueSteps = D / algoStepInEncTicks + 1;
        }
    }

    gState.stepTicker = gState.reference.stepTicker + trueSteps;
}

static int32_t calculateNextPolePos(int32_t currentPos,
                                    int32_t direction) {
    int32_t posSign = (currentPos >= 0) ? 1 : -1;

    int32_t nextPolePos =
            currentPos - currentPos % algoStepInEncTicks
            + direction * (commAngleInEncTicks
                            - commAngleInEncTicks % algoStepInEncTicks
                            + algoStepInEncTicks);

    nextPolePos += ((posSign - direction) / 2)
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

    int32_t controlledSteps = gState.stepTicker
                                - gState.reference.stepTicker;

    if (trueSteps != controlledSteps) {
        // gState.stepTicker += trueSteps - controlledSteps;
        gState.stepTicker = gState.reference.stepTicker + trueSteps;
    }
}

#define TARGET_REACHED(currentPos, activePolePos)           \
    activePolePos - algoStepInEncTicks      < currentPos    \
    && activePolePos + algoStepInEncTicks   > currentPos    \
    && labs(gState.setPoint.position - activePolePos)       \
        <= algoStepInEncTicks / 2

#define STEP_IN_PROGRESS(mgnVectsMismatch, direction)       \
    minimalMgnVectsMismatch <  mgnVectsMismatch * direction \
    && commAngleInEncTicks  >= mgnVectsMismatch * direction

#define TIME_FOR_NEXT_STEP(mgnVectsMismatch, direction)                 \
    minimalMgnVectsMismatch >= mgnVectsMismatch * direction             \
    && minimalMgnVectsMismatch - algoStepInEncTicks < mgnVectsMismatch  \
                                                        * direction

void switchPhasesIfNecessary() {
    int32_t currentPos = gState.encoder.total;

    static int32_t activePolePos = LONG_MIN;

    int32_t direction = (currentPos <= gState.setPoint.position) ? 1 : -1;

    if (activePolePos == LONG_MIN) {
        int32_t remainder = currentPos % algoStepInEncTicks;
        activePolePos = currentPos - remainder;
        if (remainder >= algoStepInEncTicks / 2) {
            activePolePos += algoStepInEncTicks;
        }
    }

    int32_t magneticVectorsMismatch = activePolePos - currentPos;

    if (TARGET_REACHED(currentPos, activePolePos)) {
        // stop();
        return;
    }
    else if (STEP_IN_PROGRESS(magneticVectorsMismatch, direction)) {
        return;
    }
    else if (TIME_FOR_NEXT_STEP(magneticVectorsMismatch, direction)) {
        // activePolePos = calculateNextPolePos(currentPos, direction);
        activePolePos = experimentalCalculateNextPolePos(direction);
        // activePolePos += direction * algoStepInEncTicks;
        step(direction);
    }
    else {
        // restoreSynchronicity(currentPos);
        experimentalRestore(direction);
        // activePolePos = calculateNextPolePos(currentPos, direction);
        activePolePos = experimentalCalculateNextPolePos(direction);

        // wrong, need to add delta from restore
        // activePolePos += direction * algoStepInEncTicks;

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

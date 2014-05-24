#include <stdlib.h>
#include "utils/macros.h"
#include "../state.h"
#include "../sensors/encoder/encoder.h"
#include "control_algo.h"
#include "feedback_control.h"

static uint16_t algoStepInEncTicks  = 0;
static uint32_t commAngleInEncTicks = 0;
static uint32_t minimalDeviation    = 0;

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

    minimalDeviation = commAngleInEncTicks - algoStepInEncTicks;
}

void switchPhasesIfNecessary() {
    int32_t currentPos = ((int32_t)gState.encoder.raw * gConfig.encoderRange
                            + gState.encoder.precise) * gConfig.motorReduction;

    static int32_t thisSwitchPos = 0;

    int_fast8_t errorSign = (currentPos < gState.setPoint.position) ? 1 : -1;

    if (thisSwitchPos == 0) {
        thisSwitchPos = currentPos - currentPos % algoStepInEncTicks
                        + errorSign*commAngleInEncTicks;
    }

    // int32_t delta = thisSwitchPos - currentPos;
    // int32_t commDelta = commAngleInEncTicks - algoStepInEncTicks;

    if (currentPos <= gState.setPoint.position + algoStepInEncTicks
        && currentPos >= gState.setPoint.position - algoStepInEncTicks) {
        return;
    }

    int32_t stepError = thisSwitchPos - currentPos;
    // int_fast8_t errorSign = SIGN(stepError);

    if (abs(stepError) <= minimalDeviation) {
        thisSwitchPos = currentPos - currentPos % algoStepInEncTicks
                        + errorSign*commAngleInEncTicks;
        // switchPhasesOnce();
        step((currentPos < gState.setPoint.position) ? 1 : -1);
    }
    else if (abs(stepError) > commAngleInEncTicks) {
        thisSwitchPos = currentPos - currentPos % algoStepInEncTicks
                        + errorSign*commAngleInEncTicks;
        step((currentPos < gState.setPoint.position) ? -1 : 1);
    }
}

void enableFeedbackControl() {
    recomputeAlgoConsts();
    setSharedEncoderHandler(&switchPhasesIfNecessary);
}

void disableFeedbackControl() {
    clearSharedEncoderHandler();
}

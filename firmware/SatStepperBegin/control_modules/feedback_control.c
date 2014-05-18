#include <stdlib.h>
#include "../state.h"
#include "../sensors/encoder/encoder.h"
#include "feedback_control.h"

static inline int32_t currentRelativePos() {
    int32_t fullSensorDeviation = gState.encoder.raw * gConfig.encoderRange
                                    + gState.encoder.precise;
    return fullSensorDeviation * gConfig.motorReduction;
}

static inline int16_t encTicsInOneAlgoStep() {
    int16_t encoderTicsOnEngineRevol =      gConfig.encoderRange
                                        /   gConfig.motorReduction;
    int16_t algoStepsInOneRevol = getEngineStepMultiplier()
                                    * gConfig.oneRevolEngineSteps;
    return  encoderTicsOnEngineRevol / algoStepsInOneRevol;
}

static inline int_fast8_t rotationDirection() {
    return (currentRelativePos() < gState.setPoint.position) ? 1 : -1;
}

void switchPhasesIfNecessary() {
    static int32_t lastSwitchPos = 0;

    int32_t currentPos = currentRelativePos();
    int16_t algoStepInEncTicks = encTicsInOneAlgoStep();

    int32_t commAngleInEncTicks = gState.currentCommAngle * algoStepInEncTicks;
    commAngleInEncTicks <<= COMM_ANGLE_RANK;

    if (abs(currentPos - lastSwitchPos) >= commAngleInEncTicks) {
        lastSwitchPos = currentPos - currentPos % algoStepInEncTicks;
        switchPhasesOnce();
    }
}

void switchPhasesOnce() {
    step(rotationDirection());
}

void enableFeedbackControl() {
    setSharedEncoderHandler(&switchPhasesIfNecessary);
}

void disableFeedbackControl() {
    clearSharedEncoderHandler();
}

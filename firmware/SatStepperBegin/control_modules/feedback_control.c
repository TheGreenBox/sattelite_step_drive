#include <stdlib.h>
#include "../state.h"
#include "../sensors/encoder/encoder.h"
#include "feedback_control.h"

static inline int64_t currentRelativePos() {
    int64_t fullSensorDeviation = gState.encoder.raw * gConfig.encoderRange
                                    + gState.encoder.precise;
    int64_t rotorDevInOneRevol  = fullSensorDeviation * gConfig.motorReduction;

    return rotorDevInOneRevol;
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
    static int64_t lastSwitchPos = 0;

    int64_t relativePos = currentRelativePos();
    int16_t algoStepInEncTicks = encTicsInOneAlgoStep();

    int64_t commAngleInEncTicks = gState.currentCommAngle * algoStepInEncTicks;
    commAngleInEncTicks <<= COMM_ANGLE_RANK;

    if (abs(relativePos - lastSwitchPos) >= commAngleInEncTicks) {
        lastSwitchPos = relativePos - relativePos % algoStepInEncTicks;
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

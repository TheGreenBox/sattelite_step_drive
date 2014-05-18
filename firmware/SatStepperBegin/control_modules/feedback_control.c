#include <stdlib.h>
#include "../state.h"
#include "feedback_control.h"

static inline int64_t currentRelativePos() {
    int64_t rawSensorDeviation  =   (gState.encoder.raw % gConfig.motorReduction)
                                    * gConfig.encoderRange;
    int64_t fullSensorDeviation = rawSensorDeviation + gState.encoder.precise;
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
    commAngleInEncTicks = commAngleInEncTicks << COMM_ANGLE_RANG;

    if (abs(relativePos - lastSwitchPos) >= commAngleInEncTicks) {
        lastSwitchPos = relativePos - relativePos % algoStepInEncTicks;
        step(rotationDirection());
    }
}

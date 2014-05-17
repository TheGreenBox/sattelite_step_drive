#include "../state.h"
#include "../utils/macros.h"
#include "../sensors/encoder/encoder.h"
#include "commutation_angle.h"

static inline int64_t totalEncoderTicks() {
    return gState.encoder.raw * ENCODER_RANGE + gState.encoder.precise;
}

static inline int64_t currentReletivePos() {
    int64_t rawSensorDeviation  =   (gState.encoder.raw % MOTOR_REDUCTION)
                                    * ENCODER_RANGE;
    int64_t fullSensorDeviation =   rawSensorDeviation + gState.encoder.precise;
    int64_t rotorDevInOneRevol = fullSensorDeviation * MOTOR_REDUCTION;

    return rotorDevInOneRevol;
}

uint_fast8_t nextAlgoStepByCommAngle() {
    int_fast8_t nextState;

    int64_t currentRelativePos = currentReletivePos();
    float fuzzyEngineStep = currentRelativePos
                            / currentAlgo->engineStepDegree;

    int_fast8_t direction = (totalEncoderTicks() <= gState.setPoint.position)
                            ? 1 : -1;

    // if (direction > 0) {
        // nextState = floor(fuzzyEngineStep + gState.currentCommAngle);
    // }
    // else {
        // nextState = ceil(fuzzyEngineStep - gState.currentCommAngle);
    // }

    return nextState % currentAlgo->algoStepsNumber;
}

#include <stdio.h>
#include "connection_types.h"
#include "utils/macros.h"

const int_fast8_t onePhaseConnA[ONE_PHASE_CONNECTION_STEPS] = {1, 0, -1,  0};
const int_fast8_t onePhaseConnB[ONE_PHASE_CONNECTION_STEPS] = {0, 1,  0, -1};
const float onePhasePwmCoeff[ONE_PHASE_CONNECTION_PWM_STEPS]= {1};

const int_fast8_t twoPhaseConnA[TWO_PHASE_CONNECTION_STEPS] = {1, -1, -1,  1};
const int_fast8_t twoPhaseConnB[TWO_PHASE_CONNECTION_STEPS] = {1,  1, -1, -1};
const float twoPhasePwmCoeff[TWO_PHASE_CONNECTION_PWM_STEPS]= {1};

const int_fast8_t halfPhaseConnA[HALF_PHASE_CONNECTION_STEPS]   = {1, 1, 0, -1, -1, -1,  0,  1};
const int_fast8_t halfPhaseConnB[HALF_PHASE_CONNECTION_STEPS]   = {0, 1, 1,  1,  0, -1, -1, -1};
const float halfPhasePwmCoeff[HALF_PHASE_CONNECTION_PWM_STEPS]  = {1, 0.707};

ConnectionParams onePhaseParameters = {
    onePhaseConnA,
    onePhaseConnB,

    ONE_PHASE_CONNECTION_STEPS,

    onePhasePwmCoeff,
    ONE_PHASE_CONNECTION_PWM_STEPS,
    ENGINE_STEP_DEGREE
};

ConnectionParams twoPhaseParameters = {
    twoPhaseConnA,
    twoPhaseConnB,

    TWO_PHASE_CONNECTION_STEPS,

    twoPhasePwmCoeff,
    TWO_PHASE_CONNECTION_PWM_STEPS,
    ENGINE_STEP_DEGREE
};

ConnectionParams halfPhaseParameters = {
    halfPhaseConnA,
    halfPhaseConnB,

    HALF_PHASE_CONNECTION_STEPS,

    halfPhasePwmCoeff,
    HALF_PHASE_CONNECTION_PWM_STEPS,
    ENGINE_STEP_DEGREE / 2
};

ConnectionParams* engineConnection = NULL;

void setConnectionType(uint_fast8_t connectionType) {
    switch (connectionType) {
        case ONE_PHASE_CONNECTION:
            engineConnection = &onePhaseParameters;
            break;
        case TWO_PHASE_CONNECTION:
            engineConnection = &twoPhaseParameters;
            break;
        case HALF_PHASE_CONNECTION:
            engineConnection = &halfPhaseParameters;
            break;
        default:
            // TODO: add static assert here
    }
}

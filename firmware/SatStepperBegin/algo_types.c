#include <stdio.h>
#include "utils/macros.h"
#include "state.h"
#include "algo_types.h"

static const int_fast8_t onePhaseAlgoA[ONE_PHASE_ALGO_STEPS]   = {1, 0, -1,  0};
static const int_fast8_t onePhaseAlgoB[ONE_PHASE_ALGO_STEPS]   = {0, 1,  0, -1};
static const float onePhasePwmCoeff[ONE_PHASE_ALGO_PWM_STEPS]  = {1};

static const int_fast8_t twoPhaseAlgoA[TWO_PHASE_ALGO_STEPS]   = {1, -1, -1,  1};
static const int_fast8_t twoPhaseAlgoB[TWO_PHASE_ALGO_STEPS]   = {1,  1, -1, -1};
static const float twoPhasePwmCoeff[TWO_PHASE_ALGO_PWM_STEPS]  = {1};

static const int_fast8_t halfPhaseAlgoA[HALF_PHASE_ALGO_STEPS] = {1, 1, 0, -1, -1, -1,  0,  1};
static const int_fast8_t halfPhaseAlgoB[HALF_PHASE_ALGO_STEPS] = {0, 1, 1,  1,  0, -1, -1, -1};
static const float halfPhasePwmCoeff[HALF_PHASE_ALGO_PWM_STEPS]= {1, 0.707};

AlgoParams onePhaseParameters = {
    onePhaseAlgoA,
    onePhaseAlgoB,

    ONE_PHASE_ALGO_STEPS,

    onePhasePwmCoeff,
    ONE_PHASE_ALGO_PWM_STEPS,
    ENGINE_STEP_DEGREE
};

AlgoParams twoPhaseParameters = {
    twoPhaseAlgoA,
    twoPhaseAlgoB,

    TWO_PHASE_ALGO_STEPS,

    twoPhasePwmCoeff,
    TWO_PHASE_ALGO_PWM_STEPS,
    ENGINE_STEP_DEGREE
};

AlgoParams halfPhaseParameters = {
    halfPhaseAlgoA,
    halfPhaseAlgoB,

    HALF_PHASE_ALGO_STEPS,

    halfPhasePwmCoeff,
    HALF_PHASE_ALGO_PWM_STEPS,
    ENGINE_STEP_DEGREE / 2
};

AlgoParams* currentAlgo = NULL;

void setAlgoType(uint_fast8_t algoType) {
    switch (algoType) {
        case ONE_PHASE_ALGO:
            currentAlgo = &onePhaseParameters;
            break;
        case TWO_PHASE_ALGO:
            currentAlgo = &twoPhaseParameters;
            break;
        case HALF_PHASE_ALGO:
            currentAlgo = &halfPhaseParameters;
            break;
        default:
            // TODO: add static assert here
    }
}

#include <stdio.h>
#include "utils/macros.h"
#include "state.h"
#include "algo_types.h"
#include "pwm_wrap_module.h"

static const int_fast8_t onePhaseAlgoA[ONE_PHASE_ALGO_STEPS]   = {1, 0, -1,  0};
static const int_fast8_t onePhaseAlgoB[ONE_PHASE_ALGO_STEPS]   = {0, 1,  0, -1};
static const uint16_t onePhasePwmCoeff[ONE_PHASE_ALGO_PWM_STEPS]  = {1 * PWM_COEFF_DEVIDER};

static const int_fast8_t twoPhaseAlgoA[TWO_PHASE_ALGO_STEPS]   = {1, -1, -1,  1};
static const int_fast8_t twoPhaseAlgoB[TWO_PHASE_ALGO_STEPS]   = {1,  1, -1, -1};
static const uint16_t twoPhasePwmCoeff[TWO_PHASE_ALGO_PWM_STEPS]  = {1 * PWM_COEFF_DEVIDER};

static const int_fast8_t halfPhaseAlgoA[HALF_PHASE_ALGO_STEPS] = {1, 1, 0, -1, -1, -1,  0,  1};
static const int_fast8_t halfPhaseAlgoB[HALF_PHASE_ALGO_STEPS] = {0, 1, 1,  1,  0, -1, -1, -1};
static const uint16_t halfPhasePwmCoeff[HALF_PHASE_ALGO_PWM_STEPS]= {1 * PWM_COEFF_DEVIDER, 0.707 * PWM_COEFF_DEVIDER};

AlgoParams onePhaseParameters = {
    onePhaseAlgoA,
    onePhaseAlgoB,

    ONE_PHASE_ALGO_STEPS,

    onePhasePwmCoeff,
    ONE_PHASE_ALGO_PWM_STEPS,
    ONE_PHASE_ALGO_STEP_MULTIPL
};

AlgoParams twoPhaseParameters = {
    twoPhaseAlgoA,
    twoPhaseAlgoB,

    TWO_PHASE_ALGO_STEPS,

    twoPhasePwmCoeff,
    TWO_PHASE_ALGO_PWM_STEPS,
    TWO_PHASE_ALGO_STEP_MULTIPL
};

AlgoParams halfPhaseParameters = {
    halfPhaseAlgoA,
    halfPhaseAlgoB,

    HALF_PHASE_ALGO_STEPS,

    halfPhasePwmCoeff,
    HALF_PHASE_ALGO_PWM_STEPS,
    HALF_PHASE_ALGO_STEP_MULTIPL
};

AlgoParams* currentAlgo = NULL;

uint_fast8_t getEngineStepMultiplier() {
    return currentAlgo->engineStepMultiplier;
}

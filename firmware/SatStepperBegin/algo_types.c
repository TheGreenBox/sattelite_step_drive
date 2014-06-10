/**
 * Organization:    The Green Box
 * Project name:    Satellite stepper drive
 *
 * @file            algo_types.h
 * @brief           Available phase switch algorithms library
 *
 */
#include <stdio.h>
#include "utils/macros.h"
#include "state.h"
#include "algo_types.h"
#include "pwm_wrap_module.h"

enum MinimalEngineStepMultipliers {
    ONE_PHASE_ALGO_STEP_MULTIPL     = 1,
    TWO_PHASE_ALGO_STEP_MULTIPL     = 1,
    HALF_PHASE_ALGO_STEP_MULTIPL    = 2
};

enum PhaseStepsByConnection {
    ONE_PHASE_ALGO_STEPS  = 4,
    TWO_PHASE_ALGO_STEPS  = 4,
    HALF_PHASE_ALGO_STEPS = 8
};

enum PwmStepsByConnection {
    ONE_PHASE_ALGO_PWM_STEPS  = 1,
    TWO_PHASE_ALGO_PWM_STEPS  = 1,
    HALF_PHASE_ALGO_PWM_STEPS = 2
};

static const int_fast8_t onePhaseAlgoA[ONE_PHASE_ALGO_STEPS]   = {1, 0, -1,  0};
static const int_fast8_t onePhaseAlgoB[ONE_PHASE_ALGO_STEPS]   = {0, 1,  0, -1};
static const uint16_t onePhasePwmCoeff[ONE_PHASE_ALGO_PWM_STEPS]  = {1 * PWM_COEFF_DIVIDER};

static const int_fast8_t twoPhaseAlgoA[TWO_PHASE_ALGO_STEPS]   = {1, -1, -1,  1};
static const int_fast8_t twoPhaseAlgoB[TWO_PHASE_ALGO_STEPS]   = {1,  1, -1, -1};
static const uint16_t twoPhasePwmCoeff[TWO_PHASE_ALGO_PWM_STEPS]  = {1 * PWM_COEFF_DIVIDER};

static const int_fast8_t halfPhaseAlgoA[HALF_PHASE_ALGO_STEPS] = {1, 1, 0, -1, -1, -1,  0,  1};
static const int_fast8_t halfPhaseAlgoB[HALF_PHASE_ALGO_STEPS] = {0, 1, 1,  1,  0, -1, -1, -1};
static const uint16_t halfPhasePwmCoeff[HALF_PHASE_ALGO_PWM_STEPS]= {1 * PWM_COEFF_DIVIDER, 0.707 * PWM_COEFF_DIVIDER};

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

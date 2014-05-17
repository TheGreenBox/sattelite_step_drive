#ifndef _ALGO_TYPES_H_
#define _ALGO_TYPES_H_

#include <stdint.h>

typedef struct _AlgoParams {
    const int_fast8_t* phaseA;
    const int_fast8_t* phaseB;

    const uint_fast8_t algoStepsNumber;

    const uint16_t* pwmCoeff;
    const uint_fast8_t algoPwmStepsNumber;

    const uint_fast8_t engineStepMultiplier;
} AlgoParams;

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

extern AlgoParams onePhaseParameters;
extern AlgoParams twoPhaseParameters;
extern AlgoParams halfPhaseParameters;

enum EngineAlgoTypes {
    ONE_PHASE_ALGO    = 1,
    TWO_PHASE_ALGO    = 2,
    HALF_PHASE_ALGO   = 3
};

uint_fast8_t getEngineStepMultiplier();

#endif //_ALGO_TYPES_H_

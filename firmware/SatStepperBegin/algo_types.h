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

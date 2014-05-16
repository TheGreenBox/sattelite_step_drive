#ifndef _CONNECTION_TYPES_H_
#define _CONNECTION_TYPES_H_

#include <stdint.h>

typedef struct _ConnectionParams {
    const int_fast8_t* phaseA;
    const int_fast8_t* phaseB;

    const uint_fast8_t algoStepsNumber;

    const float* pwmCoeff;
    const uint_fast8_t algoPwmStepsNumber;

    const float engineStepDegree;
} ConnectionParams;

enum PhaseStepsByConnection {
    ONE_PHASE_CONNECTION_STEPS  = 4,
    TWO_PHASE_CONNECTION_STEPS  = 4,
    HALF_PHASE_CONNECTION_STEPS = 8
};

enum PwmStepsByConnection {
    ONE_PHASE_CONNECTION_PWM_STEPS  = 1,
    TWO_PHASE_CONNECTION_PWM_STEPS  = 1,
    HALF_PHASE_CONNECTION_PWM_STEPS = 2
};

extern ConnectionParams onePhaseParameters;
extern ConnectionParams twoPhaseParameters;
extern ConnectionParams halfPhaseParameters;

extern ConnectionParams* engineConnection;

enum EngineConnetionTypes {
    ONE_PHASE_CONNECTION    = 1,
    TWO_PHASE_CONNECTION    = 2,
    HALF_PHASE_CONNECTION   = 3
};

void setConnectionType(uint_fast8_t connectionType);

#endif //_CONNECTION_TYPES_H_

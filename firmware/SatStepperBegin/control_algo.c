/* ========================================================
 * Organization: The green box
 *
 * Project name: Satellite stepper drive
 * File name: control_algo.c
 * Description: module for setting algo type and sending
 * A and B phase states for next step
 * Author: SNikitin
 * ========================================================
 */

#include <stdio.h>
#include "control_algo.h"

#include "state.h"

//arrays of step by step phase states for different algorythms
static int onePhaseAlgoA[ONE_PHASE_STEPS_NUMBER]  = {1, 0, -1,  0};
static int onePhaseAlgoB[ONE_PHASE_STEPS_NUMBER]  = {0, 1,  0, -1};

static unsigned onePhasePwmDuty[ONE_PHASE_PWM_STEPS_NUMBER]  = {MAX_PWM_DUTY};


static int twoPhaseAlgoA[TWO_PHASE_STEPS_NUMBER]  = {1, -1, -1,  1};
static int twoPhaseAlgoB[TWO_PHASE_STEPS_NUMBER]  = {1,  1, -1, -1};

static unsigned twoPhasePwmDuty[TWO_PHASE_PWM_STEPS_NUMBER]  = {MAX_PWM_DUTY};


static int halfPhaseAlgoA[HALF_PHASE_STEPS_NUMBER] = {1, 1, 0, -1, -1, -1,  0,  1};
static int halfPhaseAlgoB[HALF_PHASE_STEPS_NUMBER] = {0, 1, 1,  1,  0, -1, -1, -1};

static unsigned halfPhasePwmDuty[HALF_PHASE_PWM_STEPS_NUMBER] = { (unsigned)(MAX_PWM_DUTY*1), (unsigned)(MAX_PWM_DUTY*0.707) };

typedef struct _AlgoType {
    int* phaseA;
    int* phaseB;

    unsigned algoStepsNumber;

    unsigned* pwmDuty;
    unsigned algoPwmStepsNumber;
} AlgoType;

//const structure variables init
AlgoType onePhaseParametrs = {
    onePhaseAlgoA,
    onePhaseAlgoB,

    ONE_PHASE_STEPS_NUMBER,

    onePhasePwmDuty,
    ONE_PHASE_PWM_STEPS_NUMBER
};

AlgoType twoPhaseParametrs = {
    twoPhaseAlgoA,
    twoPhaseAlgoB,

    ONE_PHASE_STEPS_NUMBER,

    twoPhasePwmDuty,
    TWO_PHASE_PWM_STEPS_NUMBER
};

AlgoType halfPhaseParametrs = {
    halfPhaseAlgoA,
    halfPhaseAlgoB,

    HALF_PHASE_STEPS_NUMBER,

    halfPhasePwmDuty,
    HALF_PHASE_PWM_STEPS_NUMBER
};

static AlgoType* pCurrentAlgoStruct = NULL;

// sets control algorythm type that will be used
int setAlgoType(unsigned short algoTypeCode) {
    switch (algoTypeCode) {
        case CTRL_ALGO_ONE_PHASE:
            pCurrentAlgoStruct = &onePhaseParametrs;
            break;
        case CTRL_ALGO_TWO_PHASE:
            pCurrentAlgoStruct = &twoPhaseParametrs;
            break;
        case CTRL_ALGO_HALF_PHASE:
            pCurrentAlgoStruct = &halfPhaseParametrs;
            break;
        default:
            return 1;
    }
    return 0;
}

// writes phase states for next step to PWM registers
int getPhasePulseByStep(long long step, int* phaseA, int* phaseB) {
    // if setAlgoType wasn't used
    if (pCurrentAlgoStruct == NULL) {
        return 1;
    }
    long int nextStep = step % pCurrentAlgoStruct->algoStepsNumber;
    if (nextStep < 0) {
        nextStep = pCurrentAlgoStruct->algoStepsNumber + nextStep;
    }
    *phaseA = pCurrentAlgoStruct->phaseA[nextStep];
    *phaseB = pCurrentAlgoStruct->phaseB[nextStep];
    return 0;
}

int getPwmDutyByStep(long long step, unsigned currentPwmDuty, unsigned* pwmDuty) {
    if (pCurrentAlgoStruct == NULL) {
        return 1;
    }
    long int nextStep = step % pCurrentAlgoStruct->algoPwmStepsNumber;
    if (nextStep < 0) {
        nextStep = pCurrentAlgoStruct->algoStepsNumber + nextStep;
    }

    unsigned long pwm = MAX_PWM_DUTY - currentPwmDuty;
    pwm *= pCurrentAlgoStruct->pwmDuty[nextStep];
    pwm /= MAX_PWM_DUTY;
    *pwmDuty = (unsigned)(MAX_PWM_DUTY - pwm);

    return 0;
}

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
static int onePhaseAlgoA[ONE_PHASE_STEPS_NUMBER]  = { 1 , 0 , -1 ,  0 };
static int onePhaseAlgoB[ONE_PHASE_STEPS_NUMBER]  = { 0 , 1 ,  0 , -1 };

static unsigned onePhasePwmDuration[ONE_PHASE_PWM_STEPS_NUMBER]  = { MAX_PWM_DURATION };


static int twoPhaseAlgoA[TWO_PHASE_STEPS_NUMBER]  = { 1 , -1 , -1 ,  1 };
static int twoPhaseAlgoB[TWO_PHASE_STEPS_NUMBER]  = { 1 ,  1 , -1 , -1 };

static unsigned twoPhasePwmDuration[TWO_PHASE_PWM_STEPS_NUMBER]  = { MAX_PWM_DURATION };


static int halfPhaseAlgoA[HALF_PHASE_STEPS_NUMBER] = { 1 , 1 , 0 , -1 , -1 , -1,   0 ,  1 };
static int halfPhaseAlgoB[HALF_PHASE_STEPS_NUMBER] = { 0 , 1 , 1 ,  1 ,  0 , -1 , -1 , -1 };

static unsigned halfPhasePwmDuration[HALF_PHASE_PWM_STEPS_NUMBER] = { (unsigned)(MAX_PWM_DURATION*1), (unsigned)(MAX_PWM_DURATION*0.707) };

typedef struct _AlgoType {
    int* phaseA;
    int* phaseB;

    unsigned algoStepsNumber;

    unsigned* pwmDuration;
    unsigned algoPwmStepsNumber;
} AlgoType;

//const structure variables init
AlgoType onePhaseParametrs = {
    .phaseA = onePhaseAlgoA,
    .phaseB = onePhaseAlgoB,

    .algoStepsNumber = ONE_PHASE_STEPS_NUMBER,

    .pwmDuration = onePhasePwmDuration,
    .algoPwmStepsNumber = ONE_PHASE_PWM_STEPS_NUMBER
}

AlgoType twoPhaseParametrs = {
    .phaseA = twoPhaseAlgoA,
    .phaseB = twoPhaseAlgoB,

    .algoStepsNumber = ONE_PHASE_STEPS_NUMBER,

    .pwmDuration = twoPhasePwmDuration,
    .algoPwmStepsNumber = TWO_PHASE_PWM_STEPS_NUMBER
}

AlgoType halfPhaseParametrs = {
    .phaseA = halfPhaseAlgoA,
    .phaseB = halfPhaseAlgoB,

    .algoStepsNumber = HALF_PHASE_STEPS_NUMBER,

    .pwmDuration = halfPhasePwmDuration,
    .algoPwmStepsNumber = HALF_PHASE_PWM_STEPS_NUMBER
}

static struct AlgoType* pCurrentAlgoStruct = NULL;

// sets control algorythm type that will be used
int setAlgoType(unsigned short algoTypeCode)
{
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
int getPhasePulseByStep(long long step, int* phaseA, int* phaseB)
{
    // if setAlgoType wasn't used
    if (pCurrentAlgoStruct == NULL) {
        return 1;
    }
    unsigned nextStep = step % pCurrentAlgoStruct->algoStepsNumber;
    *phaseA = pCurrentAlgoStruct->phaseA[nextStep];
    *phaseB = pCurrentAlgoStruct->phaseB[nextStep];
    return 0;
}

int getPwmDurationByStep(long long step, unsigned currentPwmDuration, unsigned* pwmDuration)
{
    if (pCurrentAlgoStruct == NULL) {
        return 1;
    }
    unsigned nextStep = step % pCurrentAlgoStruct->algoPwmStepsNumber;

    unsigned long pwm = MAX_PWM_DURATION - currentPwmDuration;
    pwm *= pCurrentAlgoStruct->pwmDuration[nextStep];
    pwm /= MAX_PWM_DURATION;
    *pwmDuration = (unsigned)(MAX_PWM_DURATION - pwm);

    return 0;
}

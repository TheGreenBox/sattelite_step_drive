/* ========================================================
 * Organization: The green box
 *
 * Project name: Satellite stepper drive
 * File name: control_algo.c
 * Description: module for setting algo type and sending
 * A and B phase states for next step
 * ========================================================
 */

#include <stdio.h>
#include "control_algo.h"

#include "state.h"

const int onePhaseAlgoA[ONE_PHASE_ALGO_STEPS] = {1, 0, -1,  0};
const int onePhaseAlgoB[ONE_PHASE_ALGO_STEPS] = {0, 1,  0, -1};

const unsigned onePhasePwmDuty[ONE_PHASE_ALGO_PWM_STEPS] = {MAX_PWM_DUTY};


const int twoPhaseAlgoA[TWO_PHASE_ALGO_STEPS] = {1, -1, -1,  1};
const int twoPhaseAlgoB[TWO_PHASE_ALGO_STEPS] = {1,  1, -1, -1};

const unsigned twoPhasePwmDuty[TWO_PHASE_ALGO_PWM_STEPS] = {MAX_PWM_DUTY};


const int halfPhaseAlgoA[HALF_PHASE_ALGO_STEPS] = {1, 1, 0, -1, -1, -1,  0,  1};
const int halfPhaseAlgoB[HALF_PHASE_ALGO_STEPS] = {0, 1, 1,  1,  0, -1, -1, -1};

const unsigned halfPhasePwmDuty[HALF_PHASE_ALGO_PWM_STEPS] = {  (unsigned)(MAX_PWM_DUTY*1),
                                                                (unsigned)(MAX_PWM_DUTY*0.707) };

typedef struct _AlgoType {
    const int* phaseA;
    const int* phaseB;

    const unsigned algoStepsNumber;

    const unsigned* pwmDuty;
    const unsigned algoPwmStepsNumber;
} AlgoType;

AlgoType onePhaseParametrs = {
    onePhaseAlgoA,
    onePhaseAlgoB,

    ONE_PHASE_ALGO_STEPS,

    onePhasePwmDuty,
    ONE_PHASE_ALGO_PWM_STEPS
};

AlgoType twoPhaseParametrs = {
    twoPhaseAlgoA,
    twoPhaseAlgoB,

    TWO_PHASE_ALGO_STEPS,

    twoPhasePwmDuty,
    TWO_PHASE_ALGO_PWM_STEPS
};

AlgoType halfPhaseParametrs = {
    halfPhaseAlgoA,
    halfPhaseAlgoB,

    HALF_PHASE_ALGO_STEPS,

    halfPhasePwmDuty,
    HALF_PHASE_ALGO_PWM_STEPS
};

static AlgoType* currentAlgo        = NULL;
static uint_fast8_t feedbackFlag    = FEEDBACK_DISABLED;

void setAlgoType(uint_fast8_t algoType) {
    switch (algoType) {
        case ONE_PHASE_CTRL_ALGO:
            currentAlgo = &onePhaseParametrs;
            break;
        case TWO_PHASE_CTRL_ALGO:
            currentAlgo = &twoPhaseParametrs;
            break;
        case HALF_PHASE_CTRL_ALGO:
            currentAlgo = &halfPhaseParametrs;
            break;
        default:
        // TODO: add static assert here
    }
}

void setFeedbackFlagTo(uint_fast8_t state) {
    feedbackFlag = state;
}

static unsigned getNextAlgoStepNum() {
    int nextStep;

    if (feedbackFlag == FEEDBACK_ENABLED) {
        // nextStep = nextAlgoStepByCommAngle();
    }
    else {
        nextStep = gState.stepTicker % currentAlgo->algoStepsNumber;
        if (nextStep < 0) {
            nextStep = currentAlgo->algoStepsNumber + nextStep;
        }
    }

    return (unsigned)nextStep;
}

PhaseSigns getNextPhaseSigns() {
    PhaseSigns phaseSigns;

    if (currentAlgo == NULL) {
        phaseSigns.A       = 0;
        phaseSigns.B       = 0;
        return phaseSigns;
    }

    unsigned nextStep = getNextAlgoStepNum();

    phaseSigns.A = currentAlgo->phaseA[nextStep];
    phaseSigns.B = currentAlgo->phaseB[nextStep];

    return phaseSigns;
}

// TODO: this mustn't be here, it will be done in current feedback module
uint16_t getPwmDutyByStep() {
    if (currentAlgo == NULL) {
        return MAX_PWM_DUTY;
    }

    unsigned nextStep = getNextAlgoStepNum();

    uint16_t pwm = MAX_PWM_DUTY - gState.motorControl.pwmDutyCycle;
    pwm *= currentAlgo->pwmDuty[nextStep] / MAX_PWM_DUTY;

    return (MAX_PWM_DUTY - pwm);
}

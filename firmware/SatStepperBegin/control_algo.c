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

const int_fast8_t onePhaseAlgoA[ONE_PHASE_ALGO_STEPS] = {1, 0, -1,  0};
const int_fast8_t onePhaseAlgoB[ONE_PHASE_ALGO_STEPS] = {0, 1,  0, -1};

const float onePhasePwmCoeff[ONE_PHASE_ALGO_PWM_STEPS] = {1};


const int_fast8_t twoPhaseAlgoA[TWO_PHASE_ALGO_STEPS] = {1, -1, -1,  1};
const int_fast8_t twoPhaseAlgoB[TWO_PHASE_ALGO_STEPS] = {1,  1, -1, -1};

const float twoPhasePwmCoeff[TWO_PHASE_ALGO_PWM_STEPS] = {1};


const int_fast8_t halfPhaseAlgoA[HALF_PHASE_ALGO_STEPS] = {1, 1, 0, -1, -1, -1,  0,  1};
const int_fast8_t halfPhaseAlgoB[HALF_PHASE_ALGO_STEPS] = {0, 1, 1,  1,  0, -1, -1, -1};

const float halfPhasePwmCoeff[HALF_PHASE_ALGO_PWM_STEPS] = {1, 0.707};

typedef struct _AlgoType {
    const int_fast8_t* phaseA;
    const int_fast8_t* phaseB;

    const uint_fast8_t algoStepsNumber;

    const float* pwmCoeff;
    const uint_fast8_t algoPwmStepsNumber;
} AlgoType;

AlgoType onePhaseParametrs = {
    onePhaseAlgoA,
    onePhaseAlgoB,

    ONE_PHASE_ALGO_STEPS,

    onePhasePwmCoeff,
    ONE_PHASE_ALGO_PWM_STEPS
};

AlgoType twoPhaseParametrs = {
    twoPhaseAlgoA,
    twoPhaseAlgoB,

    TWO_PHASE_ALGO_STEPS,

    twoPhasePwmCoeff,
    TWO_PHASE_ALGO_PWM_STEPS
};

AlgoType halfPhaseParametrs = {
    halfPhaseAlgoA,
    halfPhaseAlgoB,

    HALF_PHASE_ALGO_STEPS,

    halfPhasePwmCoeff,
    HALF_PHASE_ALGO_PWM_STEPS
};

static AlgoType* currentAlgo    = NULL;
controlAlgoFlags ctrlFlags      = {0};

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

static uint_fast8_t getNextAlgoStepNum() {
    int_fast8_t nextStep;

    if (ctrlFlags.feedbackActive) {
        // nextStep = nextAlgoStepByCommAngle();
    }
    else {
        nextStep = gState.stepTicker % currentAlgo->algoStepsNumber;
        if (nextStep < 0) {
            nextStep = currentAlgo->algoStepsNumber + nextStep;
        }
    }

    return (uint_fast8_t)nextStep;
}

PhaseSigns getNextPhaseSigns() {
    PhaseSigns phaseSigns;

    if (currentAlgo == NULL) {
        phaseSigns.A = 0;
        phaseSigns.B = 0;
        return phaseSigns;
    }

    uint_fast8_t nextStep = getNextAlgoStepNum();

    phaseSigns.A = currentAlgo->phaseA[nextStep];
    phaseSigns.B = currentAlgo->phaseB[nextStep];

    return phaseSigns;
}

// TODO: this mustn't be here, it will be done in current feedback module
uint16_t getPwmDutyByStep() {
    if (currentAlgo == NULL) {
        return MAX_PWM_DUTY;
    }

    uint_fast8_t nextPwmStep = getNextAlgoStepNum() % currentAlgo->algoPwmStepsNumber;

    uint16_t pwm = MAX_PWM_DUTY - gState.motorControl.pwmDutyCycle;
    pwm *= currentAlgo->pwmCoeff[nextPwmStep];

    return (MAX_PWM_DUTY - pwm);
}

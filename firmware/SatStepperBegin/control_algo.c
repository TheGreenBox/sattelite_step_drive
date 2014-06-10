/**
 * Organization:    The Green Box
 * Project name:    Satellite stepper drive
 *
 * @file            control_algo.c
 * @brief           Module for setting phase switch algo
 *                  type and step in positive or negative
 *                  direction
 *
 */

#include <stdio.h>
#include "utils/macros.h"
#include "state.h"
#include "algo_types.h"
#include "control_algo.h"
#include "pwm_wrap_module.h"

static AlgoParams* currentAlgo = NULL;

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
        // default:
            // TODO: add static assert here
    }
}

uint_fast8_t getEngineStepMultiplier() {
    return currentAlgo->engineStepMultiplier;
}

void stop() {
    setADirection(0);
    setBDirection(0);
    setCoeff(0);
}

void step(int_fast8_t dist) {
    if (currentAlgo == NULL) {
        return;
    }

    gState.stepTicker += dist;

    int_fast8_t nextStep = gState.stepTicker % currentAlgo->algoStepsNumber;
    if (nextStep < 0) {
        nextStep += currentAlgo->algoStepsNumber;
    }
    setADirection(currentAlgo->phaseA[nextStep]);
    setBDirection(currentAlgo->phaseB[nextStep]);

    int_fast8_t nextPwmStep =  gState.stepTicker % currentAlgo->algoPwmStepsNumber;
    if (nextPwmStep < 0) {
        nextPwmStep += currentAlgo->algoPwmStepsNumber;
    }
    setCoeff(currentAlgo->pwmCoeff[nextPwmStep]);
}

void nextStep() {
    step(1);
}

void prevStep() {
    step(-1);
}

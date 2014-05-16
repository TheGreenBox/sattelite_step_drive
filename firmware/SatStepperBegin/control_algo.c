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
#include "utils/macros.h"
#include "state.h"
#include "connection_types.h"
#include "control_algo.h"

#include "control_modules/commutation_angle.h"

controlAlgoFlags ctrlFlags = {0};

static uint_fast8_t getNextAlgoStepNum() {
    int_fast8_t nextStep;

    if (ctrlFlags.feedbackActive) {
        // nextStep = nextAlgoStepByCommAngle();
    }
    else {
        nextStep = gState.stepTicker % engineConnection->algoStepsNumber;
        if (nextStep < 0) {
            nextStep += engineConnection->algoStepsNumber;
        }
    }

    return (uint_fast8_t)nextStep;
}

PhaseSigns getNextPhaseSigns() {
    PhaseSigns phaseSigns;

    if (engineConnection == NULL) {
        phaseSigns.A = 0;
        phaseSigns.B = 0;
        return phaseSigns;
    }

    uint_fast8_t nextStep = getNextAlgoStepNum();

    phaseSigns.A = engineConnection->phaseA[nextStep];
    phaseSigns.B = engineConnection->phaseB[nextStep];

    return phaseSigns;
}

// TODO: this mustn't be here, it will be done in current feedback module
uint16_t getPwmDutyByStep() {
    if (engineConnection == NULL) {
        return MAX_PWM_DUTY;
    }

    uint_fast8_t nextPwmStep = getNextAlgoStepNum() % engineConnection->algoPwmStepsNumber;

    uint16_t pwm = MAX_PWM_DUTY - gState.motorControl.pwmDutyCycle;
    pwm *= engineConnection->pwmCoeff[nextPwmStep];

    return (MAX_PWM_DUTY - pwm);
}

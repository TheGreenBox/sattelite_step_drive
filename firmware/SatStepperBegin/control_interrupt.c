/* ========================================================
 * Organization: The Green Box
 *
 * Project name: Satellite stepper drive
 * File name:  control_interrupt.c
 * Description: Module for control interrupt functions
 * ========================================================
 */
#include <PeripheralHeaderIncludes.h>

#include "control_interrupt.h"
#include "state.h"
#include "control_algo.h"
#include "timers.h"
#include "pwm_wrap_module.h"

// for debug purposes
unsigned int cycleLimiter(unsigned val, unsigned hi, unsigned low) {
    ++val;
    if (val > hi) {
        return low;
    }
    return val;
}

void motorISR(void) {
    if (gState.motorControl.rotationDirection == 0) {
        setADirection(0);
        setBDirection(0);
        setPwm(MAX_PWM_DUTY);
        return;
    }

    if (gState.motorControl.rotationDirection > 0) {
        ++gState.stepTicker;
    }
    else {
        ++gState.stepTicker;
    }

    int phaseVSignA, phaseVSignB;

    getPhasePulseByStep(gState.stepTicker,
                        &phaseVSignA , &phaseVSignB);

    setADirection(phaseVSignA);
    setBDirection(phaseVSignB);

    unsigned pwmDuty;

    getPwmDutyByStep(gState.stepTicker,
                     gState.motorControl.pwmDutyCycle,
                     &pwmDuty);
    setPwm(pwmDuty);

    // set speed step motor
    setTimer0Peiod(gState.motorControl.stepTimeout);
}

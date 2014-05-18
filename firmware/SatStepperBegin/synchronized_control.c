/* ========================================================
 * Organization: The Green Box
 *
 * Project name: Satellite stepper drive
 * File name:    synchronized_control.h
 * Description:  Module for control interrupt functions
 * ========================================================
 */
#include <PeripheralHeaderIncludes.h>

#include "synchronized_control.h"
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

void syncControlInterruptHadler(void) {
    if (gState.motorControl.rotationDirection == 0) {
        stop();
    }
    else {
        step(gState.motorControl.rotationDirection);
    }
}

void enableSyncControl() {
    timer0Init(&syncControlInterruptHadler);
}

void disableSyncControl() {
    timer0Init(&emptyTimerIntrHandler);
}

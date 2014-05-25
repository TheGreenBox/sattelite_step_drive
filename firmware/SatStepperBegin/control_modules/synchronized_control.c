/* ========================================================
 * Organization: The Green Box
 *
 * Project name: Satellite stepper drive
 * File name:    synchronized_control.h
 * Description:  Module for control interrupt functions
 * ========================================================
 */
#include "synchronized_control.h"
#include "state.h"
#include "control_algo.h"
#include "timers.h"
#include "utils/macros.h"

void syncControlInterruptHandler(void) {
    int32_t settedPosInMotorTick =  ( gState.setPoint.position
                                        * (int32_t)gConfig.oneRevolEngineSteps
                                        * (int32_t)getEngineStepMultiplier()
                                    ) / gConfig.encoderRange;
    int32_t delta = settedPosInMotorTick - gState.stepTicker;
    if (delta > 0) {
        step(1);
    }
    else if (delta < 0) {
        step(-1);
    }
    else if (delta == 0) {
        stop();
    }
}

void enableSyncControl() {
    setTimerIntrHandler(0, &syncControlInterruptHandler);
}

void disableSyncControl() {
    clearTimerIntrHandler(0);
}

/* ========================================================
 * Organization: The Green Box
 *
 * Project name: Satellite stepper drive
 * File name:  main.c
 * Description:
 * Author: SNikitin, AKindyakov
 * ========================================================
 */

#include "PeripheralHeaderIncludes.h"
#include "pwm_wrap_module.h"
#include "control_algo.h"
#include "led_control.h"
#include "init.h"
#include "control_interrupt.h"
#include "timers.h"
#include "state.h"

void init() {
    deviceInit();
    initPwm(gConfig.pwmPeriod);
    motorControlInit();
    timer0Init(&motorISR);
    timer1Init(&emptyFunction);
    setTimerPeriodByNum(0, 20000);

    enableGlobalInterrupts();

    setGreenStatusLed(1);
    gState.stepTicker = 0;
}

void mainLoop() {
    while (1) {
        // Put here debug functions
        // For instance - function for simulate input signal
    }
}

int main(void) {
    init();

    activate_pwm_driver();
    setAlgoType(gConfig.algoType);

    mainLoop();

    return 0;
}

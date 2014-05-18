/* ========================================================
 * Organization: The Green Box
 *
 * Project name: Satellite stepper drive
 * File name:    main.c
 * Description:
 * ========================================================
 */

#include <PeripheralHeaderIncludes.h>
#include "pwm_wrap_module.h"
#include "algo_types.h"
#include "control_algo.h"
#include "led_control.h"
#include "init.h"
#include "synchronized_control.h"
#include "timers.h"
#include "state.h"

void init() {
    deviceInit();
    initPwm(gConfig.pwmPeriod);
    stateInit();
    timer0Init(&emptyTimerIntrHandler);
    timer1Init(&emptyTimerIntrHandler);
    setTimerPeriodByNum(0, 20000);

    enableGlobalInterrupts();

    setGreenStatusLed(1);
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

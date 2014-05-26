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
#include "control_modules/synchronized_control.h"
#include "control_modules/feedback_control.h"
#include "elementary_motions.h"
#include "timers.h"
#include "state.h"

void init() {
    deviceInit();
    initPwm();
    stateInit();
    timersInit();
    setTimerPeriodByNum(0, 20000);
    setTimerPeriodByNum(1, 20000);

    enableGlobalInterrupts();

    setGreenStatusLed(1);
}

void mainLoop() {

    // just for testing
    encoderCalibration();

    while (1) {
        // TODO: remove this when current feedback is ready
        setPwm(MAX_PWM / 30);
    }
}

int main(void) {
    init();

    activate_pwm_driver();
    setAlgoType(gConfig.algoType);

    mainLoop();

    return 0;
}

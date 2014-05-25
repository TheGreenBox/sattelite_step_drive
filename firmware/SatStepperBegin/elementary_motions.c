/**
 * Organization: The green box
 * Project name: Satellite stepper drive
 *
 * @file    elementary_motions.c
 * @brief   Pretty little simple algos for elemetnaty motions
 *  github issue: [#54](https://github.com/TheGreenBox/sattelite_step_drive/issues/54)
 */


#include "state.h"
#include "control_algo.h"
#include "pwm_wrap_module.h"
#include "elementary_motions.h"
#include "utils/macros.h"
#include "control_modules/synchronized_control.h"
#include "control_modules/feedback_control.h"

void encoderCalibrating() {
    setPwm(MAX_PWM / 30);
    disableFeedbackControl();
    enableSyncControl();

    gState.setPoint.position = gConfig.encoderRange + gState.encoder.precise;
    while (gState.encoder.raw == 0) {
        DELAY_US(100);
    }

    gState.setPoint.position = gState.encoder.precise;
    disableSyncControl();
    stop();
    setPwm(0);
}


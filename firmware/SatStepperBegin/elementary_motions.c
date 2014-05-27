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

static void lockReferenceData() {
    gState.reference.encoder    =   gState.encoder.raw
                                    * (int32_t)gConfig.encoderRange
                                    + gState.encoder.precise;
    gState.reference.stepTicker = gState.stepTicker;
}

void encoderCalibration() {
    // TODO: remove this when current feedback is ready
    setPwm(MAX_PWM / 30);

    disableFeedbackControl();

    gState.setPoint.position = gConfig.encoderRange
                                + gState.encoder.precise + 1000;

    enableSyncControl();
    while (gState.encoder.raw * gConfig.encoderRange
            + gState.encoder.precise <= gConfig.encoderRange + 1000) {
        // TODO: remove this when current feedback is ready
        setPwm(MAX_PWM / 30);
    }

    disableSyncControl();
    stop();
    setPwm(0);

    lockReferenceData();

    gState.setPoint.position = gState.reference.encoder;
}

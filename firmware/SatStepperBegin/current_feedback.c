/**
 * Organization: The green box
 * Project name: Satellite stepper drive
 *
 * @file    current_feedback.c
 * @brief   Header for current feedback logic module
 *  [github issue #44](https://github.com/TheGreenBox/sattelite_step_drive/issues/44)
 */

#include <stdint.h>
#include "adc.h"
#include "pwm_wrap_module.h"
#include "current_feedback.h"

static int16_t settedCurrent = 0;
static uint16_t constPwm = 0;
static uint16_t vcc = 12 << 10;

#define CURENT_2_ADC 300
#define PWM_2_ADC_CURENT 18

#define VCC_NOMINAL 1400
#define MAX_POSITIVE_CURRENT ((1 << (ADC_BITNESS - 1)) << CURENT_COEFF_RANK) / CURENT_2_ADC

void setCurrent(uint16_t current) {
    if (current > MAX_POSITIVE_CURRENT) {
        current = MAX_POSITIVE_CURRENT;
    }
    settedCurrent = current;
    settedCurrent *= CURENT_2_ADC;
    settedCurrent >>= CURENT_COEFF_RANK;
    constPwm = settedCurrent / PWM_2_ADC_CURENT;
    setPwm(constPwm);
}

#define CORRECT_PWM_BY_ADC_CURENT(adc) \
    int16_t current = (int16_t)adc - (1 << (ADC_BITNESS - 1)); \
    int32_t delta = settedCurrent - current; \
    delta *= vcc; \
    delta /= VCC_NOMINAL; \
    setPwm(delta + (int16_t)constPwm);

void correctPwmByAdcCurrentChA(uint16_t adc) {
    if (pwmState->direct.a < 0) {
        CORRECT_PWM_BY_ADC_CURENT(adc)
    }
}

void correctPwmByAdcCurrentChB(uint16_t adc) {
    if (pwmState->direct.a > 0) {
        CORRECT_PWM_BY_ADC_CURENT(adc)
    }
}

void correctPwmByAdcCurrentChC(uint16_t adc) {
    if (pwmState->direct.b < 0) {
        CORRECT_PWM_BY_ADC_CURENT(adc)
    }
}

void correctPwmByAdcCurrentChD(uint16_t adc) {
    if (pwmState->direct.b > 0) {
        CORRECT_PWM_BY_ADC_CURENT(adc)
    }
}

void correctPwmByAdcCurrentChVCC(uint16_t adc) {
    vcc = adc;
}

void currentFeedbackInit() {
    setAdcChanelHandler(0, &correctPwmByAdcCurrentChA);
    setAdcChanelHandler(1, &correctPwmByAdcCurrentChB);
    setAdcChanelHandler(2, &correctPwmByAdcCurrentChC);
    setAdcChanelHandler(3, &correctPwmByAdcCurrentChD);
    setAdcChanelHandler(4, &correctPwmByAdcCurrentChVCC);
}


/**
 * Organization: The green box
 * Project name: Satellite stepper drive
 *
 * @file    current_feedback.c
 * @brief   Header for current feedback logic module
 *  [issue](https://github.com/TheGreenBox/sattelite_step_drive/issues/44)
 */

#define ADC_2_CURRENT 300
#define CURRENT_COEFF_RANK 10
#define CURRENT_COEFF_DIVIDER (1 << PWM_COEFF_RANK)

static void emptySharedHandler() {}
static int32_t setCurrent = 0;
// >>> (2**11)/300. = 6.82666 * 300.

static const uint16_t maxPositiveCurrent = ((float)(1<<11)/ADC_2_CURRENT.) * CURRENT_COEFF_DIVIDER;

void setCurrent(uint16_t current) {
    if (current > maxPositiveCurrent) {
        current = maxPositiveCurrent;
    }
    setCurrent = current;
    setCurrent *= ADC_2_CURRENT;
    setCurrent >>= CURRENT_COEFF_RANK;
}

void correctPwmByAdc(ECurrentChannel ch, uint16_t adc) {
    switch(ch) {
        case ECurrentChA:
        case ECurrentChB:
        case ECurrentChC:
        case ECurrentChD:
            break;
        case ECurrentChVCC:
            break;
    }
}

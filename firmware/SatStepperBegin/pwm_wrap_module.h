/* ========================================================
 * Organization: The green box
 *
 * Project name: Satellite stepper drive
 * File name: pwm_wrap_module.h
 * Description: head for pwm control module
 * ========================================================
 */

#ifndef _PWM_WRAP_MODULE__H_
#define _PWM_WRAP_MODULE__H_

#include <stdint.h>

void initPwm();

#define MAX_PWM (uint16_t)1024
void setPwm(uint16_t pwm);

#define PWM_COEFF_RANK 10
#define PWM_COEFF_DIVIDER (1 << PWM_COEFF_RANK)
void setCoeff(uint16_t pwmCoeff);

void setADirection(int_fast8_t direct);
void setBDirection(int_fast8_t direct);

void activate_pwm_driver();
void deactivate_pwm_driver();

typedef struct _PwmState {
    int16_t coeff;
    struct _direct {
        int_fast8_t a;
        int_fast8_t b;
    } direct;
} PwmState;

extern const PwmState* const pwmState;

#endif //_PWM_WRAP_MODULE__H_


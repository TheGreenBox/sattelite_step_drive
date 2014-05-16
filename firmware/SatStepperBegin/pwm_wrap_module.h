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

void initPwm(uint16_t prescaler);

void setPwm(uint16_t pwmDutyCycle);

void setADirection(int_fast8_t direct);
void setBDirection(int_fast8_t direct);

void activate_pwm_driver();
void deactivate_pwm_driver();

#endif //_PWM_WRAP_MODULE__H_


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

void initPwm( short int prescaler );

void setPwm( unsigned pwmDutyCycle );

void setADirection(int direct);
void setBDirection(int direct);

void resetDriver( int );

#endif //_PWM_WRAP_MODULE__H_


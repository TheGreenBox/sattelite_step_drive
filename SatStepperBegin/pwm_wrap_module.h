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

typedef void (* _pwmTimerInterruptHandler)(void);

void initPwm( _pwmTimerInterruptHandler, short int prescaler );

void setPwm( short int aPwm, short int bPwm );

void setADirection(int direct);
void setBDirection(int direct);

void resetDriver( int );

#endif //_PWM_WRAP_MODULE__H_


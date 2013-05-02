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
void setPwm( int apwm, int bpwm );


void resetDriver( int );

#endif //_PWM_WRAP_MODULE__H_


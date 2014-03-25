/* ========================================================
 * Organization: The Green Box
 *
 * Project name: Satellite stepper drive
 * File name:  SatStepperBegin/timers.h
 * Description:
 * ========================================================
 */

#ifndef _CONTROL_TIMER_H_
#define _CONTROL_TIMER_H_

#include "stdint.h"

typedef void (* _controlTimerInterruptHandler)(void);

void timer0Init(_controlTimerInterruptHandler);
void timer1Init(_controlTimerInterruptHandler);

// [period] = [10^3] / [System Clock Frequency in Hz]
void setTimerPeriodByNum(uint_fast8_t timerNum, uint32_t period);
void stopTimerByNum(uint_fast8_t timerNum);
void startTimerByNum(uint_fast8_t timerNum);

#endif //_CONTROL_TIMER_H_


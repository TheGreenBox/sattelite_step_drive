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
void emptyTimerIntrHandler();

void timer0Init(_controlTimerInterruptHandler);
void timer1Init(_controlTimerInterruptHandler);

void installTimer0IntrHandler(_controlTimerInterruptHandler);
void installTimer1IntrHandler(_controlTimerInterruptHandler);

void setTimerPeriodByNum(uint_fast8_t timerNum, uint32_t periodInUsec);
void stopTimerByNum(uint_fast8_t timerNum);
void startTimerByNum(uint_fast8_t timerNum);

#endif //_CONTROL_TIMER_H_

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

void timer0Init();
void timer1Init();

<<<<<<< HEAD
void setTimer0IntrHandler(_controlTimerInterruptHandler);
void clearTimer0IntrHandler();

void setTimer1IntrHandler(_controlTimerInterruptHandler);
void clearTimer1IntrHandler();
=======
void installTimer0IntrHandler(_controlTimerInterruptHandler);
void installTimer1IntrHandler(_controlTimerInterruptHandler);
>>>>>>> 43da75bbeb3629a01497d820b8bf6a3439c3e1d6

void setTimerPeriodByNum(uint_fast8_t timerNum, uint32_t periodInUsec);
void stopTimerByNum(uint_fast8_t timerNum);
void startTimerByNum(uint_fast8_t timerNum);

#endif //_CONTROL_TIMER_H_

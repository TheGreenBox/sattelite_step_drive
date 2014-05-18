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

#define ALL_TIMERS 3

typedef void (* _controlTimerInterruptHandler)(void);

void timersInit();

void setTimerIntrHandler(  uint_fast8_t timerNum,
                            _controlTimerInterruptHandler handler);
void clearTimerIntrHandler(uint_fast8_t timerNum);

void setTimerPeriodByNum(uint_fast8_t timerNum, uint32_t periodInUsec);
void stopTimerByNum(uint_fast8_t timerNum);
void startTimerByNum(uint_fast8_t timerNum);

#endif //_CONTROL_TIMER_H_

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

#include <PeripheralHeaderIncludes.h>

typedef void (* _controlTimerInterruptHandler)(void);

void timer0Init(_controlTimerInterruptHandler);
void timer1Init(_controlTimerInterruptHandler);

// [period] = [10^3] / [System Clock Frequency in Hz]
void setTimerPeriodByNum(unsigned timerNum, unsigned period);
void stopTimerByNum(unsigned timerNum);
void startTimerByNum(unsigned timerNum);

#endif //_CONTROL_TIMER_H_


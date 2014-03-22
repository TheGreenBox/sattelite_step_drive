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

void setTimer0Period(unsigned period); // 10^3 / System Clock Frequency in Hz
void setTimer1Period(unsigned period); // 10^3 / System Clock Frequency in Hz

void timer0Stop();
void timer1Stop();

void timer0Start();

#endif //_CONTROL_TIMER_H_


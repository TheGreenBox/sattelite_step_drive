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

void setTimer0Peiod(unsigned _period); // ~ usec*10
void setTimer1Peiod(unsigned _period); // ~ usec*10

void timer0Stop();
void timer1Stop();

void timer0Start();

#endif //_CONTROL_TIMER_H_


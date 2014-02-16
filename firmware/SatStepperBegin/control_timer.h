/* ========================================================
 * Organization: The Green Box
 *
 * Project name: Satellite stepper drive
 * File name:  SatStepperBegin/control_timer.h
 * Description:
 * Author:  AKindyakov
 * ========================================================
 */

#ifndef _CONTROL_TIMER_H_
#define _CONTROL_TIMER_H_

#include <PeripheralHeaderIncludes.h>

typedef void (* _controlTimerInterruptHandler)(void);

void timer0Init( _controlTimerInterruptHandler );

void setTimer0Peiod(unsigned _period); // ~ usec*10

void timer0Stop();

void timer0Start();

#endif //_CONTROL_TIMER_H_


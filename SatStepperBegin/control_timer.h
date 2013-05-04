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
void timer_init( _controlTimerInterruptHandler );

#endif //_CONTROL_TIMER_H_


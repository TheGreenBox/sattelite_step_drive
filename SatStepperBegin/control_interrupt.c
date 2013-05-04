/* ========================================================
 * Organization: The Green Box
 * 
 * Project name: Satellite stepper drive
 * File name:  control_interrupt.c 
 * Description: Module for control interrupt functions 
 * Author: SNikitin
 * ========================================================
 */
#include "PeripheralHeaderIncludes.h"
#include "control_interrupt.h"
#include "state.h"


unsigned int cycleLimiter (unsigned val, unsigned hi, unsigned low)
{
    ++val;
    if (val > hi)
    {
        return low;
    }
    return val;
}

void motorISR(void)
{   
    gState.motorControl.pwmLevelA = cycleLimiter(gState.motorControl.pwmLevelA, gConfig.pwmPeriod, 0);
    gState.motorControl.pwmLevelB = cycleLimiter(gState.motorControl.pwmLevelB, gConfig.pwmPeriod, 0);
    // Enable more interrupts from this timer
    EPwm1Regs.ETCLR.bit.INT = 1;
    // Acknowledge interrupt to recieve more interrupts from PIE group 3
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;
}

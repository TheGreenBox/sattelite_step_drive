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

unsigned int _PWM_LEVEL_A = 20000;
unsigned int _PWM_LEVEL_B = 20000;

unsigned short pwm_period = 30000;

unsigned int cycleLimiter (unsigned val, unsigned hi, unsigned low)
{
    ++val;
    if (val > hi)
    {
        return low;
    }
    return val;
}

interrupt void motorISR(void)
{   
    _PWM_LEVEL_A = cycleLimiter(_PWM_LEVEL_A, pwm_period, 0);
    _PWM_LEVEL_B = cycleLimiter(_PWM_LEVEL_B, pwm_period, 0);
    // Enable more interrupts from this timer
    EPwm1Regs.ETCLR.bit.INT = 1;
    // Acknowledge interrupt to recieve more interrupts from PIE group 3
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;
}

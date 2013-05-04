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
#include "control_algo.h"
#include "pwm_wrap_module.h"


unsigned int cycleLimiter (unsigned val, unsigned hi, unsigned low)     //for debug purposes
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
	int phaseVSignA;
	int phaseVSignB;

	getNextStep(&phaseVSignA , &phaseVSignB);
    setADirection(phaseVSignA);
    setBDirection(phaseVSignB);
}    

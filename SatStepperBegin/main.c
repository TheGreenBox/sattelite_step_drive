/* ========================================================
 * Organization: The Green Box
 * 
 * Project name: Satellite stepper drive
 * File name:  main.c 
 * Description:
 * Author: SNikitin, AKindyakov 
 * ========================================================
 */

#include "PeripheralHeaderIncludes.h"
#include "pwm_wrap_module.h"
#include "control_algo.h"
#include "led_control.h"


interrupt void motorISR(void)
{   
    toggleRedLed2();
}

void defaultInit()
{
    deviceInit();
    initPwm( &motorISR, 30000 );
    resetDriver( 1 );
    // Enable CPU INT3 for EPWM1_INT:
    IER |= M_INT3;
    // Enable global Interrupts and higher priority real-time debug events:
    EINT;   // Enable Global interrupt INTM
    ERTM;	// Enable Global realtime interrupt DBGM
    setGreenStatusLed(1);
}

void mainLoop()
{
    while (1)
    {
        
    }
}

int main(void) 
{
	defaultInit();
    resetDriver( 0 );
    setADirection(-1);
    setBDirection(1);
    setPwm( 15000, 5000 );

    mainLoop();

	return 0;
}


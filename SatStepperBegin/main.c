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
#include "init.h"
#include "control_interrupt.h"
#include "state.h"

//global variables


void defaultInit()
{
	deviceInit();
    initPwm( &motorISR, gConfig.pwmPeriod );
    resetDriver( 1 );
    // Enable CPU INT3 for EPWM1_INT:
    IER |= M_INT3;
    // Enable global Interrupts and higher priority real-time debug events:
    EINT;   // Enable Global interrupt INTM
    ERTM;	// Enable Global realtime interrupt DBGM
    
    gState.motorControl.pwmLevelA = 20000;
    gState.motorControl.pwmLevelB = 20000;
    gState.motorControl.phaseVSignA = 1;
    gState.motorControl.phaseVSignB = 1;
    
    setGreenStatusLed(1);
}
void mainLoop()
{
    while (1)
    {

        setADirection(gState.motorControl.phaseVSignA);
        setBDirection(gState.motorControl.phaseVSignB);
    	setPwm( gState.motorControl.pwmLevelA , gState.motorControl.pwmLevelB );
    }
}

int main(void) 
{
	defaultInit();
    resetDriver( 0 );
    setADirection( gState.motorControl.phaseVSignA );
    setBDirection( gState.motorControl.phaseVSignB );
    setPwm( gState.motorControl.pwmLevelA , gState.motorControl.pwmLevelB );

    mainLoop();

	return 0;
}


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
#include "control_timer.h"
#include "state.h"

//global variables


void defaultInit()
{
	deviceInit();
    initPwm( gConfig.pwmPeriod );
    resetDriver( 1 );
   
    gState.motorControl.pwmLevelA = 900;
    gState.motorControl.pwmLevelB = 900;
    gState.motorControl.stepTimeout = 0xFFFF;
    
    timer0Init( &motorISR );
    
    // Enable CPU INT3 for EPWM1_INT:
    IER |= M_INT1;
    // Enable global Interrupts and higher priority real-time debug events:
    EINT;   // Enable Global interrupt INTM
    ERTM;	// Enable Global realtime interrupt DBGM
    setAlgoType(3);
    setGreenStatusLed(1);
}

void mainLoop()
{
    while (1)
    {
    	setPwm(gState.motorControl.pwmLevelA, gState.motorControl.pwmLevelB);
        setTimer0Peiod(gState.motorControl.stepTimeout);
    }
}

int main(void) 
{
	defaultInit();
    resetDriver( 0 );

    mainLoop();

	return 0;
}


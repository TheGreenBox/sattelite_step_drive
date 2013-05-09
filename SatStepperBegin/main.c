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

void defaultInit()
{
    deviceInit();
    initPwm( gConfig.pwmPeriod );
    motorControlInit();
    timer0Init( &motorISR );
    
    enableGlobalInterrupts();
    
    setGreenStatusLed(1);
}

void mainLoop()
{
    while (1)
    {
        // Put here debug functions 
        // For instance - fuction for simulate input signal
    }
}

int main(void) 
{
    defaultInit();
    
    resetDriver(0);
    setAlgoType(gConfig.algoType);

    mainLoop();

    return 0;
}


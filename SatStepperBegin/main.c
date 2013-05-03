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

// --- global var --- 
unsigned int PWM_LEVEL_A = 20000;
unsigned int PWM_LEVEL_B = 20000;
int ROTATION_DIRECT_A = 1;
int ROTATION_DIRECT_B = 1;

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
    PWM_LEVEL_A = cycleLimiter(PWM_LEVEL_A, pwm_period, 0);
    PWM_LEVEL_B = cycleLimiter(PWM_LEVEL_B, pwm_period, 0);
    // Enable more interrupts from this timer
    EPwm1Regs.ETCLR.bit.INT = 1;
    // Acknowledge interrupt to recieve more interrupts from PIE group 3
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;
}

void defaultInit()
{
    deviceInit();
    initPwm( &motorISR, pwm_period );
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

        setADirection(ROTATION_DIRECT_A);
        setBDirection(ROTATION_DIRECT_B);
    	setPwm( PWM_LEVEL_A , PWM_LEVEL_B );
    }
}

int main(void) 
{
	defaultInit();
    resetDriver( 0 );
    setADirection(ROTATION_DIRECT_A);
    setBDirection(ROTATION_DIRECT_B);
    setPwm( PWM_LEVEL_A , PWM_LEVEL_B );

    mainLoop();

	return 0;
}


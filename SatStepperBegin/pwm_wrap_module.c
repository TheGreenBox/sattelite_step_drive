/* ========================================================
 * Organization: The green box 
 *   
 * Project name: Satellite stepper drive
 * File name: init.c
 * Description: pwm control
 * ========================================================
 */

#include <PeripheralHeaderIncludes.h>

static void initAPWM()
{
    
    // Enable CNT_zero interrupt using EPWM1 Time-base
    EPwm1Regs.ETSEL.bit.INTEN = 1;   // Enable EPWM1INT generation
    EPwm1Regs.ETSEL.bit.INTSEL = 1;  // Enable interrupt CNT_zero event
    EPwm1Regs.ETPS.bit.INTPRD = 1;   // Generate interrupt on the 1st event
    EPwm1Regs.ETCLR.bit.INT = 1;     // Enable more interrupts
    
    // Enable CPU INT3 for EPWM1_INT:
    IER |= M_INT3;
}

static void initBPWM()
{
    
}

void initPwm( _pwmTimerInterruptHandler )
{
    EALLOW;	// This is needed to write to EALLOW protected registers
    PieVectTable.EPWM1_INT = _pwmTimerInterruptHandler;
    EDIS;
    
    initBPWM();
    initBPWM();
}

void setPwm( int aPwm,  int bPwm )
{

}

void resetDriver(int drv_reset)
{
    if( drv_reset )
    {
        GpioDataRegs.GPACLEAR.bit.GPIO19 = 1;
        GpioDataRegs.GPBCLEAR.bit.GPIO32 = 1;
    }
    else
    {
        GpioDataRegs.GPASET.bit.GPIO19 = 1;
        GpioDataRegs.GPBSET.bit.GPIO32 = 1;
    }
}

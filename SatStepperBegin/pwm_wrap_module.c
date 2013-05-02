/* ========================================================
 * Organization: The green box 
 *   
 * Project name: Satellite stepper drive
 * File name: init.c
 * Description: pwm control
 * ========================================================
 */

#include <PeripheralHeaderIncludes.h>
#include "pwm_wrap_module.h"

static void initAPWM( short int prescaler )
{
    // Enable CNT_zero interrupt using EPWM1 Time-base
    EPwm1Regs.ETSEL.bit.INTEN  = 1;  // Enable EPWM1INT generation
    EPwm1Regs.ETSEL.bit.INTSEL = 1;  // Enable interrupt CNT_zero event
    EPwm1Regs.ETPS.bit.INTPRD  = 1;  // Generate interrupt on the 1st event
    EPwm1Regs.ETCLR.bit.INT    = 1;  // Enable more interrupts
    
    // Enable CPU INT3 for EPWM1_INT:
    IER |= M_INT3;

    EPwm1Regs.TBCTL.bit.SYNCOSEL = 0;   // Pass through

    // Allow each timer to be sync'ed
    EPwm1Regs.TBCTL.bit.PHSEN = 1;

    // Init Timer-Base Period Register for EPWM1-EPWM3
    EPwm1Regs.TBPRD = v.PeriodMax;

    // Init Compare Register for EPWM1-EPWM3
    EPwm1Regs.CMPA.half.CMPA = v.PeriodMax;

    // Init Timer-Base Phase Register for EPWM1-EPWM3
    EPwm1Regs.TBPHS.half.TBPHS = 0;

    // Init Timer-Base Control Register for EPWM1-EPWM3
    EPwm1Regs.TBCTL.all = PWM_INIT_STATE;

    // Init Compare Control Register for EPWM1-EPWM3
    EPwm1Regs.CMPCTL.all = CMPCTL_INIT_STATE;

    // Init Action Qualifier Output A Register for EPWM1-EPWM3
    EPwm1Regs.AQCTLA.all = AQCTLA_INIT_STATE;

    // Init Action Qualifier Output A Register for EPWM1-EPWM3
    EPwm1Regs.AQCTLB.all = AQCTLB_INIT_STATE;

    // Init Action Qualifier S/W Force Register for EPWM1-EPWM2
    EPwm1Regs.AQSFRC.all = AQSFRC_INIT_STATE;

    // Init Dead-Band Generator Control Register for EPWM1-EPWM3
    EPwm1Regs.DBCTL.all = DBCTL_INIT_STATE;

    // Init PWM Chopper Control Register for EPWM1-EPWM3
    EPwm1Regs.PCCTL.all = PCCTL_INIT_STATE;
    
    // Enable EALLOW
    EALLOW;

    // Init Trip Zone Select Register
    EPwm1Regs.TZSEL.all = TZSEL_INIT_STATE;

    // Init Trip Zone Control Register
    EPwm1Regs.TZCTL.all = TZCTL_INIT_STATE;
    
    // Disable EALLOW
    EDIS;
}

static void initBPWM( short int prescaler )
{
    // Pass through
    EPwm2Regs.TBCTL.bit.SYNCOSEL = 0;
    
    // Allow each timer to be sync'ed
    EPwm2Regs.TBCTL.bit.PHSEN = 1;

    // Init Timer-Base Period Register for EPWM1-EPWM3
    EPwm2Regs.TBPRD = v.PeriodMax;

    // Init Compare Register for EPWM1-EPWM3
    EPwm2Regs.CMPA.half.CMPA = v.PeriodMax;

    // Init Timer-Base Phase Register for EPWM1-EPWM3
    EPwm2Regs.TBPHS.half.TBPHS = 0;

    // Init Timer-Base Control Register for EPWM1-EPWM3
    EPwm2Regs.TBCTL.all = PWM_INIT_STATE;

    // Init Compare Control Register for EPWM1-EPWM3
    EPwm2Regs.CMPCTL.all = CMPCTL_INIT_STATE;

    // Init Action Qualifier Output A Register for EPWM1-EPWM3
    EPwm2Regs.AQCTLA.all = AQCTLA_INIT_STATE;

    // Init Action Qualifier Output A Register for EPWM1-EPWM3
    EPwm2Regs.AQCTLB.all = AQCTLB_INIT_STATE;

    // Init Action Qualifier S/W Force Register for EPWM1-EPWM2
    EPwm2Regs.AQSFRC.all = AQSFRC_INIT_STATE;

    // Init Dead-Band Generator Control Register for EPWM1-EPWM3
    EPwm2Regs.DBCTL.all = DBCTL_INIT_STATE;

    // Init PWM Chopper Control Register for EPWM1-EPWM3
    EPwm2Regs.PCCTL.all = PCCTL_INIT_STATE;

    EALLOW; // Enable EALLOW

    // Init Trip Zone Select Register
    EPwm2Regs.TZSEL.all = TZSEL_INIT_STATE;

    // Init Trip Zone Control Register
    EPwm2Regs.TZCTL.all = TZCTL_INIT_STATE;

    EDIS;  // Disable EALLOW
}

void initPwm( _pwmTimerInterruptHandler int_hanler, short int prescaler )
{
    EALLOW; // This is needed to write to EALLOW protected registers
    PieVectTable.EPWM1_INT = int_hanler;
    EDIS;
    
    initAPWM( prescaler );
    initBPWM( prescaler );
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

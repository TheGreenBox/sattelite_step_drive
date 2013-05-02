/* ========================================================
 * Organization: The green box 
 *   
 * Project name: Satellite stepper drive
 * File name: init.c
 * Description: pwm control
 * ========================================================
 */

#include <PeripheralHeaderIncludes.h>
#include <f2803xbmsk.h>
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

    EPwm1Regs.TBCTL.bit.SYNCOSE = 0;   // Pass through

    // Allow each timer to be sync'ed
    EPwm1Regs.TBCTL.bit.PHSEN = 1;

    // Init Timer-Base Period Register for EPWM1-EPWM3
    EPwm1Regs.TBPRD = prescaler;

    // Init Compare Register for EPWM1-EPWM3
    EPwm1Regs.CMPA.half.CMPA = prescaler;

    // Init Timer-Base Phase Register for EPWM1-EPWM3
    EPwm1Regs.TBPHS.half.TBPHS = 0;

    // Init Timer-Base Control Register for EPWM1-EPWM3
    EPwm1Regs.TBCTL.all = FREE_RUN_FLAG
                          + PRDLD_IMMEDIATE
                          + TIMER_CNT_UPDN
                          + HSPCLKDIV_PRESCALE_X_1
                          + CLKDIV_PRESCALE_X_1
                          + PHSDIR_CNT_UP
                          + CNTLD_DISABLE;

    // Init Compare Control Register for EPWM1-EPWM3
    EPwm1Regs.CMPCTL.all = LOADAMODE_ZRO
                           + LOADBMODE_ZRO
                           + SHDWAMODE_SHADOW
                           + SHDWBMODE_SHADOW;

    // Init Action Qualifier Output A Register for EPWM1-EPWM3
    EPwm1Regs.AQCTLA.all = CAU_SET + CAD_CLEAR;

    // Init Action Qualifier Output A Register for EPWM1-EPWM3
    EPwm1Regs.AQCTLB.all = CAU_SET + CAD_CLEAR;

    // Init Action Qualifier S/W Force Register for EPWM1-EPWM2
    EPwm1Regs.AQSFRC.all = RLDCSF_PRD;

    // Init Dead-Band Generator Control Register for EPWM1-EPWM3
    EPwm1Regs.DBCTL.all = BP_DISABLE;

    // Init PWM Chopper Control Register for EPWM1-EPWM3
    EPwm1Regs.PCCTL.all = CHPEN_DISABLE;
    
    // Enable EALLOW
    EALLOW;

    // Init Trip Zone Select Register
    EPwm1Regs.TZSEL.all = ENABLE_TZ2_OST + ENABLE_TZ3_OST;

    // Init Trip Zone Control Register
    EPwm1Regs.TZCTL.all = TZA_FORCE_LO + TZB_FORCE_LO
                          + DCAEVT1_HI_Z + DCAEVT2_HI_Z
                          + DCBEVT1_HI_Z + DCBEVT2_HI_Z;
    
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
    EPwm2Regs.TBPRD = prescaler;

    // Init Compare Register for EPWM1-EPWM3
    EPwm2Regs.CMPA.half.CMPA = prescaler;

    // Init Timer-Base Phase Register for EPWM1-EPWM3
    EPwm2Regs.TBPHS.half.TBPHS = 0;

    // Init Timer-Base Control Register for EPWM1-EPWM3
    EPwm2Regs.TBCTL.all = FREE_RUN_FLAG
                          + PRDLD_IMMEDIATE
                          + TIMER_CNT_UPDN
                          + HSPCLKDIV_PRESCALE_X_1
                          + CLKDIV_PRESCALE_X_1
                          + PHSDIR_CNT_UP
                          + CNTLD_DISABLE;

    // Init Compare Control Register for EPWM1-EPWM3
    EPwm2Regs.CMPCTL.all = LOADAMODE_ZRO
                           + LOADBMODE_ZRO
                           + SHDWAMODE_SHADOW
                           + SHDWBMODE_SHADOW;

    // Init Action Qualifier Output A Register for EPWM1-EPWM3
    EPwm2Regs.AQCTLA.all = CAU_SET + CAD_CLEAR;

    // Init Action Qualifier Output A Register for EPWM1-EPWM3
    EPwm2Regs.AQCTLB.all = CAU_SET + CAD_CLEAR;

    // Init Action Qualifier S/W Force Register for EPWM1-EPWM2
    EPwm2Regs.AQSFRC.all = RLDCSF_PRD;

    // Init Dead-Band Generator Control Register for EPWM1-EPWM3
    EPwm2Regs.DBCTL.all = BP_DISABLE;

    // Init PWM Chopper Control Register for EPWM1-EPWM3
    EPwm2Regs.PCCTL.all = CHPEN_DISABLE;

    EALLOW; // Enable EALLOW

    // Init Trip Zone Select Register
    EPwm2Regs.TZSEL.all = ENABLE_TZ2_OST + ENABLE_TZ3_OST;

    // Init Trip Zone Control Register
    EPwm2Regs.TZCTL.all = TZA_FORCE_LO + TZB_FORCE_LO
                          + DCAEVT1_HI_Z + DCAEVT2_HI_Z
                          + DCBEVT1_HI_Z + DCBEVT2_HI_Z;

    EDIS;  // Disable EALLOW
}

void initPwm( _pwmTimerInterruptHandler int_hanler, short int prescaler )
{
    EALLOW; // This is needed to write to EALLOW protected registers
    PieVectTable.EPWM1_INT = int_hanler;
    EDIS;
    
    // Enable PIE group 3 interrupt 1 for EPWM1_INT
    PieCtrlRegs.PIEIER3.bit.INTx1 = 1;
    
    initAPWM( prescaler );
    initBPWM( prescaler );
}

void setPwm( short int aPwm, short int bPwm )
{
    EPwm1Regs.CMPA.half.CMPA = aPwm;
    EPwm2Regs.CMPA.half.CMPA = bPwm;
}

void setADirection(int direct)
{
    if ( direct == 0 )
    {   
        //EPWM1A forced low
        EPwm1Regs.AQCSFRC.bit.CSFA = 1;
        //EPWM1B forced low
        EPwm1Regs.AQCSFRC.bit.CSFB = 1;
    }
    else
    {
        if ( direct > 0 ) 
        {
            //Forcing Disabled on EPWM1A
            EPwm1Regs.AQCSFRC.bit.CSFA = 0;
            //EPWM1B forced low
            EPwm1Regs.AQCSFRC.bit.CSFB = 1;
        }
        else
        {   
            //EPWM1A forced low
            EPwm1Regs.AQCSFRC.bit.CSFA = 1;
            //EPWM1B forced low
            EPwm1Regs.AQCSFRC.bit.CSFB = 1;
        }
    }
}

void setBDirection(int direct)
{
    if ( direct == 0 )
    {   
        //EPWM1A forced low
        EPwm2Regs.AQCSFRC.bit.CSFA = 1;
        //EPWM1B forced low
        EPwm2Regs.AQCSFRC.bit.CSFB = 1;
    }
    else
    {
        if ( direct > 0 ) 
        {
            //Forcing Disabled on EPWM1A
            EPwm2Regs.AQCSFRC.bit.CSFA = 0;
            //EPWM1B forced low
            EPwm2Regs.AQCSFRC.bit.CSFB = 1;
        }
        else
        {   
            //EPWM1A forced low
            EPwm2Regs.AQCSFRC.bit.CSFA = 1;
            //EPWM1B forced low
            EPwm2Regs.AQCSFRC.bit.CSFB = 1;
        }
    }
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

/* ========================================================
 * Organization: The Green Box
 * 
 * Project name: Satellite stepper drive
 * File name:  SatStepperBegin/control_timer.c 
 * Description:
 * Author:  AKindyakov 
 * ========================================================
 */

//-----------------------------------------------------------------------------
#include <PeripheralHeaderIncludes.h>
//-----------------------------------------------------------------------------
#include "f2803xbmsk.h"
#include "control_timer.h"
//-----------------------------------------------------------------------------

static _controlTimerInterruptHandler _tmr0Handler;

interrupt void TMR0_Interrupt(void)
{
    _tmr0Handler();
    CpuTimer0Regs.TCR.all.TIF = 0;
    
    // The TIMH:TIM is loaded with the value in the PRDH:PRD,
    //  and the prescaler counter (PSCH:PSC) is loaded with the
    //  value in the timer divide- down register (TDDRH:TDDR).
    CpuTimer0Regs.TCR.all.TRB = 0;
}

void timer0Init( _controlTimerInterruptHandler handler )
{
    _tmr0Handler = handler;
 
    EALLOW; // This is needed to write to EALLOW protected registers
    PieVectTable.TINT0 = TMR0_Interrupt;
    EDIS;
   
    // Enable PIE for TINT0
    PieCtrlRegs.PIEIER1.bit.INTx7 = 1;
    
    // enable timer 0 interrupt
    CpuTimer0Regs.TCR.bits.TIE = 1;
    // free run mode switch on
    CpuTimer0Regs.TCR.bits.FREE = 1;
    CpuTimer0Regs.TCR.bits.SOFT = 0; 

    // set preload value and timer prescaler 
    CpuTimer0Regs.PRD.all = 0xFFFF;
    CpuTimer0Regs.TPR.all = 0x0258; //600 
}

void setTimer0Peiod(int _period) // ~ usec
{
    CpuTimer0Regs.PRD.all = _period;
}

void timer0Stop()
{
    CpuTimer0Regs.TCR.bits.TSS = 1;
}

void timer0Start()
{
    // still i don't know how to start int without
    // initialisation
}


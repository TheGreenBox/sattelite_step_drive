/* ========================================================
 * Organization: The Green Box
 *
 * Project name: Satellite stepper drive
 * File name:  SatStepperBegin/timers.c
 * Description:
 * ========================================================
 */

#include <PeripheralHeaderIncludes.h>
#include "utils/macros.h"
#include "timers.h"

static _controlTimerInterruptHandler _tmr0Handler;
static _controlTimerInterruptHandler _tmr1Handler;

interrupt void TMR0_Interrupt(void)
{
    _tmr0Handler();
    // CpuTimer0Regs.TCR.bit.TIF = 0; // TODO: writes of 0 are ignored, check it

    // TIMH:TIM is loaded with the value in the PRDH:PRD,
    // PSCH:PSC is loaded with the value in the TDDRH:TDDR.
    CpuTimer0Regs.TCR.bit.TRB = 1;

    // Acknowledge interrupt to recieve more interrupts from PIE group 1
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
}

interrupt void TMR1_Interrupt(void)
{
    _tmr1Handler();
    // CpuTimer1Regs.TCR.bit.TIF = 0;
    CpuTimer1Regs.TCR.bit.TRB = 1;
    // TINT1 is not part of any interrupt group, so it doesn't require
    // acknowledgement
}

void timer0Init(_controlTimerInterruptHandler handler)
{
    _tmr0Handler = handler;

    EALLOW; // This is needed to write to EALLOW protected registers
    PieVectTable.TINT0 = TMR0_Interrupt;
    EDIS;

    // Enable PIE for TINT0
    PieCtrlRegs.PIEIER1.bit.INTx7 = 1;
    IER |= M_INT1;

    // enable timer 0 interrupt
    CpuTimer0Regs.TCR.bit.TIE = 1;
    // free run mode switch on
    CpuTimer0Regs.TCR.bit.FREE = 1;
    CpuTimer0Regs.TCR.bit.SOFT = 0;

    // set preload value and timer prescaler
    CpuTimer0Regs.PRD.all           = 0xFFFF;
    CpuTimer1Regs.TPR.bit.TDDR      = 0xFF;
    CpuTimer1Regs.TPRH.bit.TDDRH    = 0xFF;
}

void timer1Init(_controlTimerInterruptHandler handler)
{
    _tmr1Handler = handler;

    EALLOW; // This is needed to write to EALLOW protected registers
    PieVectTable.TINT1 = &TMR1_Interrupt;
    EDIS;

    // Enable TINT1
    IER |= M_INT13;

    // enable timer 0 interrupt
    CpuTimer1Regs.TCR.bit.TIE = 1;
    // free run mode switch on
    CpuTimer1Regs.TCR.bit.FREE = 1;
    CpuTimer1Regs.TCR.bit.SOFT = 0;

    // set preload value and timer prescaler
    CpuTimer1Regs.PRD.all           = 0xFFFF;
    CpuTimer1Regs.TPR.bit.TDDR      = 0xFF;
    CpuTimer1Regs.TPRH.bit.TDDRH    = 0xFF;
}

static volatile struct CPUTIMER_REGS* const timerRegs[3] = {
    &CpuTimer0Regs,
    &CpuTimer1Regs,
    &CpuTimer2Regs
};

void setTimerPeriodByNum(uint_fast8_t timerNum, uint32_t periodInUsec) {
    // The TIMH:TIM is loaded with the value in the PRDH:PRD,
    // and the prescaler counter (PSCH:PSC) is loaded with the
    // value in the timer divide-down register (TDDRH:TDDR).

    uint16_t timerDivider =     timerRegs[timerNum]->TPR.bit.TDDR
                            +  (timerRegs[timerNum]->TPRH.bit.TDDRH << 8) + 1;
    uint32_t period = (periodInUsec * timerDivider) / (10*CPU_CLOCK_SPEED);
    timerRegs[timerNum]->PRD.all    = period;
    // timerRegs[timerNum]->PRD.all = periodInUsec;
}

void stopTimerByNum(uint_fast8_t timerNum) {
    timerRegs[timerNum]->TCR.bit.TSS = 1;
}

void startTimerByNum(uint_fast8_t timerNum) {
    // still i don't know how to start int without
    // initialisation
}

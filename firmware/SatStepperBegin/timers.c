/* ========================================================
 * Organization: The Green Box
 *
 * Project name: Satellite stepper drive
 * File name:  SatStepperBegin/timers.c
 * Description:
 * ========================================================
 */

#include <stddef.h>
#include <PeripheralHeaderIncludes.h>
#include "utils/macros.h"
#include "timers.h"

static volatile struct CPUTIMER_REGS* const timerRegs[3] = {
    &CpuTimer0Regs,
    &CpuTimer1Regs,
    &CpuTimer2Regs
};

static _controlTimerInterruptHandler _tmr0Handler;
static _controlTimerInterruptHandler _tmr1Handler;

void emptyTimerIntrHandler(){}

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

static inline void setTimerSettingsToDefaultByNum(uint_fast8_t timerNum) {
    // enable timer interrupt
    timerRegs[timerNum]->TCR.bit.TIE = 1;
    // free run mode switch on
    timerRegs[timerNum]->TCR.bit.FREE = 1;
    timerRegs[timerNum]->TCR.bit.SOFT = 0;

    // set preload value and timer prescaler
    timerRegs[timerNum]->PRD.all           = 0xFFFF;
    timerRegs[timerNum]->TPR.bit.TDDR      = 0x0;
    timerRegs[timerNum]->TPRH.bit.TDDRH    = 0x0;
}

void timer0Init() {
    clearTimer0IntrHandler();

    EALLOW; // This is needed to write to EALLOW protected registers
    PieVectTable.TINT0 = TMR0_Interrupt;
    EDIS;

    // Enable PIE for TINT0
    PieCtrlRegs.PIEIER1.bit.INTx7 = 1;
    IER |= M_INT1;

    setTimerSettingsToDefaultByNum(0);
}

void timer1Init() {
    clearTimer1IntrHandler();

    EALLOW; // This is needed to write to EALLOW protected registers
    PieVectTable.TINT1 = &TMR1_Interrupt;
    EDIS;

    // Enable TINT1
    IER |= M_INT13;

    setTimerSettingsToDefaultByNum(1);
}

void setTimer0IntrHandler(_controlTimerInterruptHandler handler) {
    if (handler != NULL) {
        _tmr0Handler = handler;
    }
}

void clearTimer0IntrHandler() {
    _tmr0Handler = &emptyTimerIntrHandler;
}

void setTimer1IntrHandler(_controlTimerInterruptHandler handler) {
    if (handler != NULL) {
        _tmr1Handler = handler;
    }
}

void clearTimer1IntrHandler() {
    _tmr1Handler = &emptyTimerIntrHandler;
}

void setTimerPeriodByNum(uint_fast8_t timerNum, uint32_t periodInUsec) {
    // The TIMH:TIM is loaded with the value in the PRDH:PRD,
    // and the prescaler counter (PSCH:PSC) is loaded with the
    // value in the timer divide-down register (TDDRH:TDDR).

    uint16_t timerDivider =     timerRegs[timerNum]->TPR.bit.TDDR
                            +  (timerRegs[timerNum]->TPRH.bit.TDDRH << 8) + 1;
    uint32_t period = (periodInUsec * 10*CPU_CLOCK_SPEED) / timerDivider;

    timerRegs[timerNum]->PRD.all = period;
    // timerRegs[timerNum]->PRD.all = periodInUsec;
}

void stopTimerByNum(uint_fast8_t timerNum) {
    timerRegs[timerNum]->TCR.bit.TSS = 1;
}

void startTimerByNum(uint_fast8_t timerNum) {
    // still i don't know how to start int without
    // initialisation
}

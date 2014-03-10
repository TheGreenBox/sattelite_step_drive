/**
* @brief
*
*/

//void input_encoder_signal_handler(bool A, bool nA,
//                                  bool B, bool nB,
//                                  bool index, bool nIndex) {
//
//}

#include <PeripheralHeaderIncludes.h>

#include "f2803xbmsk.h"
#include "control_timer.h"

interrupt void encoderInputInterruptHandler(void)
{
    //handler_body(); //TODO: write

}

void timer0Init( _controlTimerInterruptHandler handler )
{
    EALLOW; // This is needed to write to EALLOW protected registers
    PieVectTable.TINT0 = TMR0_Interrupt;
    EDIS;

    // 00 Interrupt generated on a falling edge (high-to-low transition)
    // 01 Interrupt generated on a rising edge (low-to-high transition)
    // 10 Interrupt generated on a falling edge (high-to-low transition)
    // 11 Interrupt generated on both a falling edge and a rising edge
    //  (high-to-low and low-to-high transition)
    XIntruptRegs.XINT1CR.XINTCR_BITS.Polarity = 0b11;

    GpioCtrlRegs.GPAMUX2.bit.GPIO21 = 1;

    XIntruptRegs.XINT1CR.XINTCR_BITS.Enable = 1;

    // Enable PIE for XINT1
    PieCtrlRegs.PIEIER12.bit.INTx1 = 1;

    IER |= M_INT12;
}

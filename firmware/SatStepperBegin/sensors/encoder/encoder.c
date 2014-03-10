/**
* @brief
*
*/

//void inputEncoder_signal_handler(bool A, bool nA,
//                                  bool B, bool nB,
//                                  bool index, bool nIndex) {
//
//}

#include <PeripheralHeaderIncludes.h>

#include "f2803xbmsk.h"

interrupt void encoderInputInterruptHandler(void)
{
    //handler_body(); //TODO: write
}

void encoderInit()
{
    EALLOW; // This is needed to write to EALLOW protected registers
    //PieVectTable.TINT0 = TMR0_Interrupt;
    EDIS;

    // 00 Interrupt generated on a falling edge (high-to-low transition)
    // 01 Interrupt generated on a rising edge (low-to-high transition)
    // 10 Interrupt generated on a falling edge (high-to-low transition)
    // 11 Interrupt generated on both a falling edge and a rising edge
    //  (high-to-low and low-to-high transition)
    XIntruptRegs.XINT1CR.bit.POLARITY = 3;
    XIntruptRegs.XINT2CR.bit.POLARITY = 3;
    XIntruptRegs.XINT3CR.bit.POLARITY = 3;

    XIntruptRegs.XINT1CR.bit.ENABLE   = 1;
    XIntruptRegs.XINT2CR.bit.ENABLE   = 1;
    XIntruptRegs.XINT3CR.bit.ENABLE   = 1;

    //XIntruptRegs.XINT1CR.XINTCR_BITS.Enable = 1;

    // Enable PIE for XINT1
    PieCtrlRegs.PIEIER12.bit.INTx1 = 1;

    IER |= M_INT12;
}

/**
 * Organization: The Green Box
 * Project name:    Satellite stepper drive
 *
 * @file    encoder.c
 * @brief
 *  [wiki](https://github.com/TheGreenBox/sattelite_step_drive/wiki/sensor_encoder)
 */

#include <PeripheralHeaderIncludes.h>
#include <f2803xbmsk.h>

#include "encoder.h"
#include "gray_code_decoder.h"
#include "state.h"

#define ENCODER_RANGE 1000  //TODO: check it!!
#define ENCODER_HALF_OF_RANGE ENCODER_RANGE/2

interrupt void encoderInputABIntHandler(void) {
#ifdef DEBUG
    ASSERT(
        GpioDataRegs.GPADAT.bit.GPIO20 == GpioDataRegs.GPADAT.bit.GPIO24,
        ++gState.encoder.errors
    );
    ASSERT(
        GpioDataRegs.GPADAT.bit.GPIO21 == GpioDataRegs.GPADAT.bit.GPIO25,
        ++gState.encoder.errors
    );
#endif // DEBUG

    static int oldA = 0, oldB = 0;
    gState.encoder.precise += GREY_CODE_STEP_DECODER(
        oldA,
        oldB,
        GpioDataRegs.GPADAT.bit.GPIO20,
        GpioDataRegs.GPADAT.bit.GPIO21
    );
    oldA = GpioDataRegs.GPADAT.bit.GPIO20;
    oldB = GpioDataRegs.GPADAT.bit.GPIO21;

    // Acknowledge interrupt to recieve more interrupts from PIE group 1
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
}

interrupt void encoderInputCIntHandler(void) {
#ifdef _DEBUG
    ASSERT(
        GpioDataRegs.GPADAT.bit.GPIO23 == GpioDataRegs.GPADAT.bit.GPIO26,
        ++gState.encoder.errors
    );
#endif // DEBUG
    STATIC_ASSERT(ENCODER_RANGE);

    if (GpioDataRegs.GPADAT.bit.GPIO23) {
        if (gState.encoder.precise > ENCODER_HALF_OF_RANGE) {
            gState.encoder.raw += 1;
            gState.encoder.precise = 0;
        }
        else {
            gState.encoder.raw -= 1;
            gState.encoder.precise = ENCODER_RANGE;
        }
    }

    // Acknowledge interrupt to recieve more interrupts from PIE group 12
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP12;
}

void encoderInit() {
    EALLOW; // This is needed to write to EALLOW protected registers
    PieVectTable.XINT1 = encoderInputABIntHandler;
    PieVectTable.XINT2 = encoderInputABIntHandler;
    PieVectTable.XINT3 = encoderInputCIntHandler;

    /*
    * 00 Interrupt generated on a falling edge (high-to-low transition)
    * 01 Interrupt generated on a rising edge (low-to-high transition)
    * 10 Interrupt generated on a falling edge (high-to-low transition)
    * 11 Interrupt generated on both a falling edge and a rising edge
    *      (high-to-low and low-to-high transition)
    */
    XIntruptRegs.XINT1CR.bit.POLARITY = 3;
    XIntruptRegs.XINT2CR.bit.POLARITY = 3;
    XIntruptRegs.XINT3CR.bit.POLARITY = 1;

    XIntruptRegs.XINT1CR.bit.ENABLE   = 1;
    XIntruptRegs.XINT2CR.bit.ENABLE   = 1;
    XIntruptRegs.XINT3CR.bit.ENABLE   = 1;

    /*
    * GPIO20 -> S1A -> Encoder1A
    * GPIO21 -> S1B -> Encoder1B
    * GPIO23 -> S1C -> Encoder1C
    * GPIO24 -> S2A -> Encoder2A
    * GPIO25 -> S2B -> Encoder2B
    * GPIO26 -> S2C -> Encoder2C
    */

    // Encoder1A - A
    GpioIntRegs.GPIOXINT1SEL.bit.GPIOSEL = 20;

    // Encoder1B - B
    GpioIntRegs.GPIOXINT2SEL.bit.GPIOSEL = 21;

    // Encoder1C - C
    GpioIntRegs.GPIOXINT3SEL.bit.GPIOSEL = 23;

    // Enable PIE for XINT1 and XINT2
    PieCtrlRegs.PIEIER1.bit.INTx4 = 1;
    PieCtrlRegs.PIEIER1.bit.INTx5 = 1;
    // Enable PIE for XINT1
    PieCtrlRegs.PIEIER12.bit.INTx1 = 1;

    // Enable PIE interrupt group for XINT1 and XINT2
    IER |= M_INT1;
    // Enable PIE interrupt group for XINT3
    IER |= M_INT12;
    EDIS;

    // init global encoder counter
    gState.encoder.raw     = 0;
    gState.encoder.precise = 0;
#ifdef DEBUG
    gState.encoder.errors  = 0;
#endif // DEBUG
}

/* TODO: don't forget about it! -->
* External Interrupt n Counter (XINTnCTR) Field Descriptions
* This is a free running 16-bit up-counter that is clocked  at the  SYSCLKOUT
* rate.  The  counter value is reset to 0x0000 when a valid interrupt edge is
* detected and  then  continues  counting until the next valid interrupt edge
* is detected. When the interrupt is disabled, the counter stops. The counter
* is a  free-running  counter  and wraps around to zero when the max value is
* reached. The counter is a read  only register and can only be reset to zero
* by a valid interrupt edge or by reset. ->|
*/


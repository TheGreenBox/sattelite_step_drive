/**
 * Organization:    The Green Box
 * Project name:    Satellite stepper drive
 *
 * @file            led_control.c
 * @brief           STATUS LED, LED2, LED3 control module
 *
 */

#include "PeripheralHeaderIncludes.h"
#include "led_control.h"

void setGreenStatusLed(int setState)
{
    if (setState == 0) {
        GpioDataRegs.GPASET.bit.GPIO22   = 0;
        GpioDataRegs.GPACLEAR.bit.GPIO22 = 1;
    } else {
        GpioDataRegs.GPACLEAR.bit.GPIO22 = 0;
        GpioDataRegs.GPASET.bit.GPIO22   = 1;
    }
}

void setRedLed2(int setState)
{
    if (setState == 0) {
        GpioDataRegs.GPASET.bit.GPIO31   = 0;
        GpioDataRegs.GPACLEAR.bit.GPIO31 = 1;
    } else {
        GpioDataRegs.GPACLEAR.bit.GPIO31 = 0;
        GpioDataRegs.GPASET.bit.GPIO31   = 1;
    }
}

void setRedLed3(int setState)
{
    if (setState == 0) {
        GpioDataRegs.GPBSET.bit.GPIO32   = 0;
        GpioDataRegs.GPBCLEAR.bit.GPIO32 = 1;
    } else {
        GpioDataRegs.GPBCLEAR.bit.GPIO32 = 0;
        GpioDataRegs.GPBSET.bit.GPIO32   = 1;
    }
}

void toggleGreenStatusLed()
{
    GpioDataRegs.GPATOGGLE.bit.GPIO22 = 1;
}

void toggleRedLed2()
{
    GpioDataRegs.GPATOGGLE.bit.GPIO31 = 1;
}

void toggleRedLed3()
{
    GpioDataRegs.GPBTOGGLE.bit.GPIO32 = 1;
}

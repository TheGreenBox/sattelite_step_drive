/* ========================================================
 * Organization: The Green Box
 *
 * Project name: Satellite stepper drive
 * File name: macros.h
 * Description: Useful macros used across the project
 * ========================================================
 */

#ifndef _MACROS__H_
#define _MACROS__H_

#define CPU_CLOCK_SPEED 6.000L   // for 60 Mhz; 10.000L for a 100MHz CPU clock speed
#define ADC_usDELAY     10000L
#define DELAY_US(A)     DSP28x_usDelay(((((long double) A * 1000.0L)    \
                        / (long double)CPU_CLOCK_SPEED) - 9.0L) / 5.0L)

extern void DSP28x_usDelay(unsigned long Count);

// To receive more interrupts from this PIE group, acknowledge this interrupt
// Writing 0 to bits is ignored, so there is no point using OR operator
#define ACKNOWLEDGE_ONE_MORE_INTERRUPT_FROM_GROUP(GROUP_ID) \
    PieCtrlRegs.PIEACK.all = GROUP_ID

#define __ASSERT_CONCAT(a, b) a##b
#define STATIC_ASSERT(e) \
    enum { __ASSERT_CONCAT(static_assert_, __LINE__) = 1/(!!(e)) }

#define ASSERT(condition, event) \
    if (!condition) { \
        event; \
    }

#define SIGN(arg) \
    ((arg & (1 << 8*sizeof(arg) - 1)) ? -1 : 1)

#define PI 3.14159265358979

#endif //_MACROS__H_

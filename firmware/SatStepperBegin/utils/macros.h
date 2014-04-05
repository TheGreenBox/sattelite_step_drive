/* ========================================================
 * Organization: The Green Box
 *
 * Project name: Satellite stepper drive
 * File name: macros.h
 * Description: Useful macros used across the project
 * ========================================================
 */

#ifndef _MACROS_H_
#define _MACROS_H_

#define CPU_CLOCK_SPEED 6.000L   // for 60 Mhz; 10.000L for a 100MHz CPU clock speed
#define ADC_usDELAY     10000L
#define DELAY_US(A)     DSP28x_usDelay(((((long double) A * 1000.0L)    \
                        / (long double)CPU_CLOCK_SPEED) - 9.0L) / 5.0L)

extern void DSP28x_usDelay(unsigned long Count);

// To receive more interrupts from this PIE group, acknowledge this interrupt
// Writing 0 to bits is ignored, so there is no point using OR operator
#define ACKNOWLEDGE_ONE_MORE_INTERRUPT_FROM_GROUP(GROUP_ID) \
    PieCtrlRegs.PIEACK.all = GROUP_ID


#define CREATE_DUAL_DEBUG_RECORDER(name, capacity, rtype) \
static volatile rtype name##_first [capacity] = {0, }; \
static volatile rtype name##_second[capacity] = {0, }; \
    void debugRecorder_##name (int a, int b) { \
        static unsigned long int index = 0; \
        name##_first[index]  = a; \
        name##_second[index] = b; \
        ++index; \
        if (index >= capacity) { \
            index = 0; \
        } \
    }


#endif //_MACROS_H_

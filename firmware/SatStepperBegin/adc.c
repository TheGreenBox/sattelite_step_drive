/**
 * Organization: The Green Box
 * Project name: Satellite stepper drive
 *
 * @file adc.c
 * @brief ADC initialization and interrupts
 *  [github issue #44](https://github.com/TheGreenBox/sattelite_step_drive/issues/44),
 *  [github issue #47](https://github.com/TheGreenBox/sattelite_step_drive/issues/47)
 */


#include "PeripheralHeaderIncludes.h"
#include "utils/macros.h"
#include "state.h"
#include "adc.h"

// Functions that will be run from RAM need to be assigned to
// a different section. This section will then be mapped to a load and
// run address using the linker cmd file.
#define Device_cal (void (*)(void) )0x3D7C80

static void emptySharedHandler(uint16_t adc) {}
TSharedAdcHandler adcHandlers[NUM_ACTIVE_ADC_CHANELS] = {
    &emptySharedHandler,
    &emptySharedHandler,
    &emptySharedHandler,
    &emptySharedHandler,
    &emptySharedHandler
};

static void adcCalibrate() {
    EALLOW; // Below registers are "protected", allow access.

    //---------------------------------------------------
    // The Device_cal function, which copies the ADC & oscillator calibration values
    // from TI reserved OTP into the appropriate trim registers, occurs automatically
    // in the Boot ROM. If the boot ROM code is bypassed during the debug process, the
    // following function MUST be called for the ADC and oscillators to function according
    // to specification.

    // Enable ADC peripheral clock
    SysCtrlRegs.PCLKCR0.bit.ADCENCLK = 1;
    // Auto-calibrate from TI OTP
    (*Device_cal)();
    // Return ADC clock to original state
    // SysCtrlRegs.PCLKCR0.bit.ADCENCLK = 0;
    EDIS; // Disable register access
}

static void powerUpAdc() {
    EALLOW; // Below registers are "protected", allow access.

    // *IMPORTANT*
    // To powerup the ADC the ADCENCLK bit should be set first to enable
    // clocks, followed by powering up the bandgap, reference circuitry, and ADC core.
    // Before the first conversion is performed a 5ms delay must be observed
    // after power up to give all analog circuits time to power up and settle

    // Please note that for the delay function below to operate correctly the
    // CPU_RATE define statement in the DSP2803x_Examples.h file must
    // contain the correct CPU clock period in nanoseconds.
    AdcRegs.ADCCTL1.bit.ADCBGPWD  = 1;      // Power ADC BG
    AdcRegs.ADCCTL1.bit.ADCREFPWD = 1;      // Power reference
    AdcRegs.ADCCTL1.bit.ADCPWDN   = 1;      // Power ADC
    AdcRegs.ADCCTL1.bit.ADCENABLE = 1;      // Enable ADC
    AdcRegs.ADCCTL1.bit.ADCREFSEL = 0;      // Select interal BG

    DELAY_US(ADC_usDELAY);  // Delay before converting ADC channels

    AdcRegs.ADCCTL1.bit.INTPULSEPOS = 1;    // INT pulse generation after conversion
    AdcRegs.ADCCTL1.bit.TEMPCONV    = 0;    // Temperature sensor disconnected from ADC

    EDIS; // Disable register access
}

static void socSetUp() {
    // The term SOC is configuration set defining the single conversion
    // of a single channel. In that set there are three configurations:
    // the trigger source that starts the conversion, the channel to convert,
    // and the acquisition (sample) window size. Each SOC is independently
    // configured and can have any combination of the trigger, channel,
    // and sample window size available. Multiple SOC’s can be configured
    // for the same trigger, channel, and/or acquisition window as desired.

    EALLOW; // Below registers are "protected", allow access.

    AdcRegs.ADCINTSOCSEL1.all       = 0;    // TRIGSEL field determines SOCx triggers
    AdcRegs.ADCINTSOCSEL2.all       = 0;    // TRIGSEL field determines SOCx triggers

    AdcRegs.ADCSOC0CTL.bit.CHSEL    = 0;    // ChSelect: ADC A0-> Phase A
    AdcRegs.ADCSOC0CTL.bit.TRIGSEL  = 2;    // Set SOC0 start trigger on TINT1 (CPU Timer 0), due to round-robin SOC0 converts first then SOC1
    AdcRegs.ADCSOC0CTL.bit.ACQPS    = 6;    // Set SOC0 S/H Window to 7 ADC Clock Cycles, (6 ACQPS plus 1)

    AdcRegs.ADCSOC1CTL.bit.CHSEL    = 1;    // ChSelect: ADC A1-> Phase B
    AdcRegs.ADCSOC1CTL.bit.TRIGSEL  = 2;
    AdcRegs.ADCSOC1CTL.bit.ACQPS    = 6;

    AdcRegs.ADCSOC2CTL.bit.CHSEL    = 2;    // ChSelect: ADC A2-> Phase C
    AdcRegs.ADCSOC2CTL.bit.TRIGSEL  = 2;
    AdcRegs.ADCSOC2CTL.bit.ACQPS    = 6;

    AdcRegs.ADCSOC3CTL.bit.CHSEL    = 3;    // ChSelect: ADC A3-> Phase D
    AdcRegs.ADCSOC3CTL.bit.TRIGSEL  = 2;
    AdcRegs.ADCSOC3CTL.bit.ACQPS    = 6;

    AdcRegs.ADCSOC4CTL.bit.CHSEL    = 4;    // ChSelect: ADC A4-> DC Bus Voltage
    AdcRegs.ADCSOC4CTL.bit.TRIGSEL  = 2;
    AdcRegs.ADCSOC4CTL.bit.ACQPS    = 6;

    EDIS; // Disable register access
}

static const uint_fast16_t ADC_INTERRUPT_GROUP = PIEACK_GROUP10;

interrupt void ADCINT3_ISR(void) {
    gState.adc[0] = AdcResult.ADCRESULT0;
    adcHandlers[0](AdcResult.ADCRESULT0);
    ACKNOWLEDGE_ONE_MORE_INTERRUPT_FROM_GROUP(ADC_INTERRUPT_GROUP);
}

interrupt void ADCINT4_ISR(void) {
    gState.adc[1] = AdcResult.ADCRESULT1;
    adcHandlers[1](AdcResult.ADCRESULT1);
    ACKNOWLEDGE_ONE_MORE_INTERRUPT_FROM_GROUP(ADC_INTERRUPT_GROUP);
}

interrupt void ADCINT5_ISR(void) {
    gState.adc[2] = AdcResult.ADCRESULT2;
    adcHandlers[2](AdcResult.ADCRESULT2);
    ACKNOWLEDGE_ONE_MORE_INTERRUPT_FROM_GROUP(ADC_INTERRUPT_GROUP);
}

interrupt void ADCINT6_ISR(void) {
    gState.adc[3] = AdcResult.ADCRESULT3;
    adcHandlers[3](AdcResult.ADCRESULT3);
    ACKNOWLEDGE_ONE_MORE_INTERRUPT_FROM_GROUP(ADC_INTERRUPT_GROUP);
}

interrupt void ADCINT7_ISR(void) {
    gState.adc[4] = AdcResult.ADCRESULT4;
    adcHandlers[4](AdcResult.ADCRESULT4);
    ACKNOWLEDGE_ONE_MORE_INTERRUPT_FROM_GROUP(ADC_INTERRUPT_GROUP);
}

static void adcInterruptInit() {
    EALLOW; // Below registers are "protected", allow access.

    // Enable continuous mode for ADCINT3 and ADCINT4
    AdcRegs.INTSEL3N4.bit.INT3CONT = 1;
    AdcRegs.INTSEL3N4.bit.INT4CONT = 1;
    // Enable continuous mode for ADCINT5 and ADCINT6
    AdcRegs.INTSEL5N6.bit.INT5CONT = 1;
    AdcRegs.INTSEL5N6.bit.INT6CONT = 1;
    // Enable continuous mode for ADCINT7
    AdcRegs.INTSEL7N8.bit.INT7CONT = 1;

    AdcRegs.INTSEL3N4.bit.INT3E = 1;
    AdcRegs.INTSEL3N4.bit.INT4E = 1;
    AdcRegs.INTSEL5N6.bit.INT5E = 1;
    AdcRegs.INTSEL5N6.bit.INT6E = 1;
    AdcRegs.INTSEL7N8.bit.INT7E = 1;

    AdcRegs.INTSEL3N4.bit.INT3SEL  = 0; // EOC0 is trigger for ADCINT3
    AdcRegs.INTSEL3N4.bit.INT4SEL  = 1; // EOC1 is trigger for ADCINT4
    AdcRegs.INTSEL5N6.bit.INT5SEL  = 2; // EOC2 is trigger for ADCINT5
    AdcRegs.INTSEL5N6.bit.INT6SEL  = 3; // EOC3 is trigger for ADCINT6
    AdcRegs.INTSEL7N8.bit.INT7SEL  = 4; // EOC4 is trigger for ADCINT7

    // Enable PIE for ADCINT3..ADCINT7 in interrupt group 10
    PieCtrlRegs.PIEIER10.bit.INTx3 = 1;
    PieCtrlRegs.PIEIER10.bit.INTx4 = 1;
    PieCtrlRegs.PIEIER10.bit.INTx5 = 1;
    PieCtrlRegs.PIEIER10.bit.INTx6 = 1;
    PieCtrlRegs.PIEIER10.bit.INTx7 = 1;

    PieVectTable.ADCINT3 = &ADCINT3_ISR;
    PieVectTable.ADCINT4 = &ADCINT4_ISR;
    PieVectTable.ADCINT5 = &ADCINT5_ISR;
    PieVectTable.ADCINT6 = &ADCINT6_ISR;
    PieVectTable.ADCINT7 = &ADCINT7_ISR;

    IER |= M_INT10; // Enable interrupt level 10 (group 10)

    EDIS; // Disable register access
}

void adcInit() {
    adcCalibrate();
    socSetUp();
    adcInterruptInit();
    powerUpAdc();
}

void setAdcChanelHandler(uint_fast8_t ch, TSharedAdcHandler handler) {
    if (ch < NUM_ACTIVE_ADC_CHANELS) {
        adcHandlers[ch] = handler;
    }
#ifdef DEBUG
    else {
        int t = 0;
        while (1) {
            ++t;
        }
    }
#endif // DEBUG
}

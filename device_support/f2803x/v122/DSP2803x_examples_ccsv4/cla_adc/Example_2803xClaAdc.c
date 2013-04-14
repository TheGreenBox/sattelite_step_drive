// TI File $Revision: /main/6 $
// Checkin $Date: June 29, 2010   09:54:28 $
//###########################################################################
//
// FILE:   Example_2803xClaAdc.c
//
// TITLE:  DSP2803x CLA Reads ADC Result Registers Example Program.
//
// ASSUMPTIONS:
//
//   This program requires the DSP2803x header files.
//
//   Make sure the CPU clock speed is properly defined in
//   DSP2803x_Examples.h before compiling this example.
//
//   Connect signals to be converted to A2 and A3.
//
//    $Boot_Table:
//
//    While an emulator is connected to your device, the TRSTn pin = 1,
//    which sets the device into EMU_BOOT boot mode. In this mode, the
//    peripheral boot modes are as follows:
//
//      Boot Mode:       EMU_KEY        EMU_BMODE
//                       (0xD00)	     (0xD01)
//      ---------------------------------------
//      Wait             !=0x55AA        X
//      I/O              0x55AA	         0x0000
//      SCI              0x55AA	         0x0001
//      Wait             0x55AA	         0x0002
//      Get_Mode         0x55AA	         0x0003
//      SPI              0x55AA	         0x0004
//      I2C              0x55AA	         0x0005
//      OTP              0x55AA	         0x0006
//      eCANA            0x55AA	         0x0007
//      SARAM            0x55AA	         0x000A	  <-- "Boot to SARAM"
//      Flash            0x55AA	         0x000B
//      Wait             0x55AA          Other
//
//   Write EMU_KEY to 0xD00 and EMU_BMODE to 0xD01 via the debugger
//   according to the Boot Mode Table above. Build/Load project,
//   Reset the device, and Run example
//
//   $End_Boot_Table
//
//
// Description:
//
//   This example sets up the PLL in x12/2 mode.
//
//   For 60 MHz devices (default)
//   (assuming a 10Mhz input clock).
//
//   Interrupts are enabled and the ePWM1 is setup to generate a periodic
//   ADC SOC. One channel is converted: ADCINA2. When the ADC begins 
//   conversion, it will assert ADCINT2 which will start CLA task 2.
//
//   Cla Task2 logs 10 ADCRESULT1 values in a circular buffer.
//
//   When Task2 completes an interrupt to the CPU clears the ADCINT2 flag.
//
//   Watch Variables:
//
//         VoltageCLA[10]   Last 10 ADCRESULT1 values
//         ConversionCount  Current result number 
//         LoopCount        Idle loop counter
//
//
//###########################################################################
// $TI Release: 2803x C/C++ Header Files V1.22 $
// $Release Date: June 10, 2010 $
//###########################################################################

#include "DSP28x_Project.h"     // Device Headerfile and Examples Include File
#include "CLAShared.h"

// Prototype statements for functions found within this file.
interrupt void cla1_isr2(void);

// Global variables used in this example:
#pragma DATA_SECTION(ConversionCount, "Cla1ToCpuMsgRAM");
#pragma DATA_SECTION(VoltageCLA,      "Cla1ToCpuMsgRAM");

Uint16 ConversionCount;
Uint16 LoopCount;
Uint16 VoltageCLA[NUM_DATA_POINTS];

// These are defined by the linker file
extern Uint16 Cla1funcsLoadStart;
extern Uint16 Cla1funcsLoadEnd;
extern Uint16 Cla1funcsRunStart;

main()
{

// Step 1. Initialize System Control:
// PLL, WatchDog, enable Peripheral Clocks
// This example function is found in the DSP2803x_SysCtrl.c file.
   InitSysCtrl();

// Step 2. Initialize GPIO:
// This example function is found in the DSP2803x_Gpio.c file and
// illustrates how to set the GPIO to it's default state.
// InitGpio();  // Skipped for this example

// Step 3. Clear all interrupts and initialize PIE vector table:
// Disable CPU interrupts
   DINT;

// Initialize the PIE control registers to their default state.
// The default state is all PIE interrupts disabled and flags
// are cleared.
// This function is found in the DSP2803x_PieCtrl.c file.
   InitPieCtrl();

// Disable CPU interrupts and clear all CPU interrupt flags:
   IER = 0x0000;
   IFR = 0x0000;

// Initialize the PIE vector table with pointers to the shell Interrupt
// Service Routines (ISR).
// This will populate the entire table, even if the interrupt
// is not used in this example.  This is useful for debug purposes.
// The shell ISR routines are found in DSP2803x_DefaultIsr.c.
// This function is found in DSP2803x_PieVect.c.
   InitPieVectTable();

// Interrupts that are used in this example are re-mapped to
// ISR functions found within this file.
   EALLOW;  // This is needed to write to EALLOW protected register
   PieVectTable.CLA1_INT2 = &cla1_isr2;   
   EDIS;    // This is needed to disable write to EALLOW protected registers

// Step 4. Initialize all the Device Peripherals:
// This function is found in DSP2803x_InitPeripherals.c
// InitPeripherals(); // Not required for this example
   InitAdc();         // For this example, init the ADC

// Step 5. User specific code, enable interrupts:

// Enable ADCINT1 in PIE
   PieCtrlRegs.PIEIER11.bit.INTx2 = 1;      // Enable INT 11.2 in the PIE (CLA Task2)
   IER |= M_INT11;                          // Enable CPU Interrupt 11
   EINT;          						    // Enable Global interrupt INTM
   ERTM;          						    // Enable Global realtime interrupt DBGM

// Copy CLA code from its load address to CLA program RAM
//
// Note: during debug the load and run addresses can be 
// the same as Code Composer Studio can load the CLA program
// RAM directly. 
// 
// The ClafuncsLoadStart, ClafuncsLoadEnd, and ClafuncsRunStart
// symbols are created by the linker. 
   MemCopy(&Cla1funcsLoadStart, &Cla1funcsLoadEnd, &Cla1funcsRunStart);    

// Initialize the CLA registers
   EALLOW;
   Cla1Regs.MVECT2 = (Uint16) (&Cla1Task2 - &Cla1Prog_Start)*sizeof(Uint32);
   Cla1Regs.MVECT8 = (Uint16) (&Cla1Task8 - &Cla1Prog_Start)*sizeof(Uint32);
   Cla1Regs.MPISRCSEL1.bit.PERINT2SEL = CLA_INT2_ADCINT2; // ADCINT2 starts Task 2
   Cla1Regs.MMEMCFG.bit.PROGE = 1;          // Map CLA program memory to the CLA
   Cla1Regs.MCTL.bit.IACKE = 1;             // Enable IACK to start tasks via software
   Cla1Regs.MIER.all = (M_INT8 | M_INT2);   // Enable Task 8 and Task 2
   Cla1ForceTask8andWait();                 // Force CLA task 8.  
                                            // This will initialize ConversionCount to zero

   AdcRegs.ADCCTL1.bit.INTPULSEPOS = 0;	    // ADCINT trips before AdcResults latch
   AdcRegs.INTSEL1N2.bit.INT2E     = 1;	    // Enable ADCINT2
   AdcRegs.INTSEL1N2.bit.INT2CONT  = 0;	    // Disable ADCINT1 Continuous mode
   AdcRegs.INTSEL1N2.bit.INT2SEL   = 1;	    // setup EOC1 to trigger ADCINT2 to fire
   AdcRegs.ADCSOC1CTL.bit.CHSEL    = 2;	    // set SOC1 channel select to ADCINA2
   AdcRegs.ADCSOC1CTL.bit.TRIGSEL  = 5;     // set SOC1 start trigger on EPWM1A
   AdcRegs.ADCSOC1CTL.bit.ACQPS    = 6;	    // set SOC1 S/H Window to 7 ADC Clock Cycles, (6 ACQPS plus 1)
   EDIS;

// Assumes ePWM1 clock is already enabled in InitSysCtrl();
   EALLOW;
   SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 0;
   EDIS;
   EPwm1Regs.ETSEL.bit.SOCAEN	= 1;		// Enable SOC on A group
   EPwm1Regs.ETSEL.bit.SOCASEL	= 4;		// Select SOC from from CPMA on upcount
   EPwm1Regs.ETPS.bit.SOCAPRD 	= 1;		// Generate pulse on 1st event
   EPwm1Regs.CMPA.half.CMPA 	= 0x0080;	// Set compare A value
   EPwm1Regs.TBPRD 				= 0xFFFF;	// Set period for ePWM1
   EPwm1Regs.TBCTL.bit.CTRMODE 	= 0;		// count up and start
   EALLOW;
   SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 1;
   EDIS;
   
   
// Wait for ADC interrupt
   for(;;)
   {
      LoopCount++;
   }

}

// This interrupt occurs when CLA Task 2 completes
interrupt void cla1_isr2()
{
    AdcRegs.ADCINTFLGCLR.bit.ADCINT2 = 1;    // Clear ADCINT2 flag reinitialize for next SOC
    PieCtrlRegs.PIEACK.all = 0xFFFF;
}


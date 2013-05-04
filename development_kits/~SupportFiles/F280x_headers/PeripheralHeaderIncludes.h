//============================================================================
//============================================================================
//
// FILE:   			PeripheralHeaderIncludes.h (280x version)
// 
// DESCRIPTION:		Contains F280x device specific definitions and includes
//
// VERSION:			04 Apr 2008 - (BRL)
//============================================================================
//============================================================================
#ifndef DSP280x_DEVICE_H
#define DSP280x_DEVICE_H 1

#ifdef __cplusplus
extern "C" {
#endif

//---------------------------------------------------------------------------
// CPU Timer Definitions:
// Timer definitions based on 100MHz System Clock
// 	if not using a 100MHz clock define a different set of constants elsewhere
#define		mSec0_5		50000		// 0.5 mS
#define		mSec1		100000		// 1.0 mS
#define		mSec2		200000		// 2.0 mS
#define		mSec5		500000		// 5.0 mS
#define		mSec7_5		750000		// 7.5 mS
#define		mSec10		1000000		// 10 mS
#define		mSec20		2000000		// 20 mS
#define		mSec50		5000000		// 50 mS
#define		mSec100		10000000	// 100 mS
#define		mSec500		50000000	// 500 mS
#define		mSec1000	100000000	// 1000 mS
#define		mSec5000	500000000	// 5000 mS

//---------------------------------------------------------------------------
// Common CPU Definitions:
//
extern cregister volatile unsigned int IFR;
extern cregister volatile unsigned int IER;

#define  EINT   asm(" clrc INTM")
#define  DINT   asm(" setc INTM")
#define  ERTM   asm(" clrc DBGM")
#define  DRTM   asm(" setc DBGM")
#define  EALLOW asm(" EALLOW")
#define  EDIS   asm(" EDIS")
#define  ESTOP0 asm(" ESTOP0")

#define M_INT1  0x0001
#define M_INT2  0x0002
#define M_INT3  0x0004
#define M_INT4  0x0008
#define M_INT5  0x0010
#define M_INT6  0x0020
#define M_INT7  0x0040
#define M_INT8  0x0080
#define M_INT9  0x0100
#define M_INT10 0x0200
#define M_INT11 0x0400
#define M_INT12 0x0800
#define M_INT13 0x1000
#define M_INT14 0x2000
#define M_DLOG  0x4000
#define M_RTOS  0x8000

#define BIT0    0x0001
#define BIT1    0x0002
#define BIT2    0x0004
#define BIT3    0x0008
#define BIT4    0x0010
#define BIT5    0x0020
#define BIT6    0x0040
#define BIT7    0x0080
#define BIT8    0x0100
#define BIT9    0x0200
#define BIT10   0x0400
#define BIT11   0x0800
#define BIT12   0x1000
#define BIT13   0x2000
#define BIT14   0x4000
#define BIT15   0x8000


//---------------------------------------------------------------------------
// For Portability, User Is Recommended To Use Following Data Type Size
// Definitions For 16-bit and 32-Bit Signed/Unsigned Integers:
//
#ifndef DSP28_DATA_TYPES
#define DSP28_DATA_TYPES
typedef int             int16;
typedef long            int32;
typedef unsigned int    Uint16;
typedef unsigned long   Uint32;
typedef float           float32;
typedef long double     float64;
#endif


//---------------------------------------------------------------------------
// Include All Peripheral Header Files:
//
#include "DSP280x_Adc.h"                // ADC Registers
#include "DSP280x_DevEmu.h"             // Device Emulation Registers
#include "DSP280x_CpuTimers.h"          // 32-bit CPU Timers
#include "DSP280x_ECan.h"               // Enhanced eCAN Registers
#include "DSP280x_ECap.h"               // Enhanced Capture
#include "DSP280x_EPwm.h"               // Enhanced PWM 
#include "DSP280x_EQep.h"               // Enhanced QEP
#include "DSP280x_Gpio.h"               // General Purpose I/O Registers
#include "DSP280x_I2c.h"                // I2C Registers
#include "DSP280x_PieCtrl.h"            // PIE Control Registers
#include "DSP280x_PieVect.h"            // PIE Vector Table
#include "DSP280x_Spi.h"                // SPI Registers
#include "DSP280x_Sci.h"                // SCI Registers
#include "DSP280x_SysCtrl.h"            // System Control/Power Modes
#include "DSP280x_XIntrupt.h"           // External Interrupts

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif  // end of DSP280x_DEVICE_H definition

//===========================================================================
// End of file.
//===========================================================================

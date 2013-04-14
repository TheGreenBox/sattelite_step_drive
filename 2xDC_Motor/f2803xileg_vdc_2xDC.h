/* ==================================================================================
File name:       F2803XILEG_VDC_2xDC.H
                    
Originator:	Digital Control Systems Group
			Texas Instruments

Description: This header file contains macro definition for ADC initilization 
(In this project ADC is used for leg current measurement and DC-bus measurement)

This drv file is specific to "DRV8412" kit

Target: TMS320F2803x family
              
=====================================================================================
History:
-------------------------------------------------------------------------------------
 07-28-2010	Version 1.0 
------------------------------------------------------------------------------------*/

#ifndef __F280XILEG_VDC_H__
#define __F280XILEG_VDC_H__

#include "f2803xbmsk.h"

/*------------------------------------------------------------------------------
 ADC Initialization Macro Definition 
------------------------------------------------------------------------------*/


#define CPU_CLOCK_SPEED      6.000L   // 10.000L for a 100MHz CPU clock speed
#define ADC_usDELAY 10000L
#define DELAY_US(A)  DSP28x_usDelay(((((long double) A * 1000.0L) / (long double)CPU_CLOCK_SPEED) - 9.0L) / 5.0L)

extern void DSP28x_usDelay(unsigned long Count);


#define ADC_MACRO_INIT()																				\
																								\
 DELAY_US(ADC_usDELAY);																			\
    AdcRegs.ADCCTL1.all=ADC_RESET_FLAG;															\
	asm(" NOP ");																				\
	asm(" NOP ");    																			\
																								\
	EALLOW;																						\
	 AdcRegs.ADCCTL1.bit.ADCBGPWD	= 1;	/* Power up band gap */								\
																								\
	DELAY_US(ADC_usDELAY);					/* Delay before powering up rest of ADC */			\
																								\
	AdcRegs.ADCCTL1.bit.ADCREFSEL	= 0;														\
   	AdcRegs.ADCCTL1.bit.ADCREFPWD	= 1;	/* Power up reference */							\
   	AdcRegs.ADCCTL1.bit.ADCPWDN 	= 1;	/* Power up rest of ADC */							\
	AdcRegs.ADCCTL1.bit.ADCENABLE	= 1;	/* Enable ADC */									\
																								\
	asm(" RPT#100 || NOP");																		\
																								\
	AdcRegs.ADCCTL1.bit.INTPULSEPOS=1;															\
	AdcRegs.ADCCTL1.bit.TEMPCONV=0;																\
																								\
	DELAY_US(ADC_usDELAY);																		\
																								\
	/******* CHANNEL SELECT *******/															\
																								\
																								\
	AdcRegs.ADCSOC0CTL.bit.CHSEL 	= 0;   	/* ChSelect: ADC A0-> Motor1 Phase A*/ 				\
	AdcRegs.ADCSOC0CTL.bit.TRIGSEL 	= 5;	/* Set SOC0 start trigger on EPWM1A, due to round-robin SOC0 converts first then SOC1*/	\
	AdcRegs.ADCSOC0CTL.bit.ACQPS 	= 6;	/* Set SOC0 S/H Window to 7 ADC Clock Cycles, (6 ACQPS plus 1)*/						\
																								\
	AdcRegs.ADCSOC1CTL.bit.CHSEL 	= 1;	/* ChSelect: ADC A1-> Motor1 Phase B*/				\
	AdcRegs.ADCSOC1CTL.bit.TRIGSEL  = 5;														\
	AdcRegs.ADCSOC1CTL.bit.ACQPS 	= 6;														\
																								\
	AdcRegs.ADCSOC2CTL.bit.CHSEL 	= 4;	/* ChSelect: ADC A4-> DC Bus Voltage*/ 				\
	AdcRegs.ADCSOC2CTL.bit.TRIGSEL  = 5;														\
	AdcRegs.ADCSOC2CTL.bit.ACQPS 	= 6;														\
																								\
	AdcRegs.ADCSOC3CTL.bit.CHSEL 	= 2;    /* ChSelect: ADC A2-> Motor2 Phase A*/				\
	AdcRegs.ADCSOC3CTL.bit.TRIGSEL 	= 5;														\
	AdcRegs.ADCSOC3CTL.bit.ACQPS 	= 6;														\
																								\
	AdcRegs.ADCSOC4CTL.bit.CHSEL 	= 3;	/* ChSelect: ADC A3-> Motor2 Phase B*/				\
	AdcRegs.ADCSOC4CTL.bit.TRIGSEL  = 5;														\
	AdcRegs.ADCSOC4CTL.bit.ACQPS 	= 6; 														\
	           																					\
	EDIS;																						\
																								\
																								\
    /* Set up Event Trigger with CNT_zero enable for Time-base of EPWM1 */						\
    EPwm1Regs.ETSEL.bit.SOCAEN = 1;     /* Enable SOCA */										\
    EPwm1Regs.ETSEL.bit.SOCASEL = 1;    /* Enable CNT_zero event for SOCA */					\
    EPwm1Regs.ETPS.bit.SOCAPRD = 1;     /* Generate SOCA on the 1st event */					\
	EPwm1Regs.ETCLR.bit.SOCA = 1;       /* Clear SOCA flag */									\
																								\



#endif // __F280XILEG_VDC_H__

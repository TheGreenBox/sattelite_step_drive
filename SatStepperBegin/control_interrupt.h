/* ========================================================
 * Organization: The Green Boxa
 * 
 * Project name: Satellite stepper drive
 * File name:  control_interrupt.h
 * Description: header for control_interrupt.c
 * Author: SNikitin
 * ========================================================
 */ 

#ifndef INTERRUPT_CONTROL_INCLUDED
#define INTERRUPT_CONTROL_INCLUDED

extern unsigned short pwm_period;

interrupt void motorISR(void);

#endif              //INTERRUPT_CONTROL_INCLUDED

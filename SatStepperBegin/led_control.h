/* ========================================================
 * Organization: The Green Box
 * 
 * Project name: Satellite stepper drive
 * File name:  led_control.h
 * Description: header for led_control.c
 * Author: SNikitin
 * ========================================================
 */ 

#ifndef LED_CONTROL_INCLUDED
#define LED_CONTROL_INCLUDED

void setGreenStatusLed (int);
void setRedLed2 (int);
void setRedLed3 (int);

void toggleGreenStatusLed ();
void toggleRedLed2 ();
void toggleRedLed3 ();


#endif              //LED_CONTROL_INCLUDED

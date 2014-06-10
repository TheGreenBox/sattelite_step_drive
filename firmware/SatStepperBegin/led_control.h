/**
 * Organization:    The Green Box
 * Project name:    Satellite stepper drive
 *
 * @file            led_control.h
 * @brief           Header of STATUS LED, LED2, LED3 control module
 *
 */

#ifndef LED_CONTROL_INCLUDED
#define LED_CONTROL_INCLUDED

void setGreenStatusLed(int);
void setRedLed2(int);
void setRedLed3(int);

void toggleGreenStatusLed();
void toggleRedLed2();
void toggleRedLed3();


#endif // LED_CONTROL_INCLUDED

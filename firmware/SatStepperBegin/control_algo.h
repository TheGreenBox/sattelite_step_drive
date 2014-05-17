/* ========================================================
 * Organization: The green box
 *
 * Project name: Satellite stepper drive
 * File name: control_algo.h
 * Description: head of control_algo module
 * ========================================================
 */

#ifndef _CONTROL_ALGO_INCLUDED_
#define _CONTROL_ALGO_INCLUDED_

#include <stdint.h>
void step(int_fast8_t dist);

void nextStep();
void prevStep();

#endif //_CONTROL_ALGO_INCLUDED_

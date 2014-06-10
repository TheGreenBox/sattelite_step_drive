/**
 * Organization:    The Green Box
 * Project name:    Satellite stepper drive
 *
 * @file            control_algo.h
 * @brief           Header of module for setting phase switch algo
 *                  type and step in positive or negative
 *                  direction
 *
 */

#ifndef _CONTROL_ALGO_INCLUDED_
#define _CONTROL_ALGO_INCLUDED_

#include <stdint.h>

void setAlgoType(uint_fast8_t algoType);
uint_fast8_t getEngineStepMultiplier();

void stop();
void step(int_fast8_t dist);

void nextStep();
void prevStep();

#endif //_CONTROL_ALGO_INCLUDED_

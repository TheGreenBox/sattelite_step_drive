/* ========================================================
 * Organization: The green box
 *
 * Project name: Satellite stepper drive
 * File name: control_algo.h
 * Description: head of control_algo module
 * Author: SNikitin
 * ========================================================
 */

#ifndef _CONTROL_ALGO_INCLUDED_
#define _CONTROL_ALGO_INCLUDED_


#define ONE_TWO_PHASE_STEPS_NUMBER  4
#define HALF_PHASE_STEPS_NUMBER     8
#define NUMBER_OF_ALGOS             3

#define INVALID                     0
#define ONE_PHASE_CODE              1
#define TWO_PHASE_CODE              2
#define HALF_PHASE_CODE             3

int setAlgoType(unsigned short);
int getNextStep(int*, int*);

#endif //_CONTROL_ALGO_INCLUDED_

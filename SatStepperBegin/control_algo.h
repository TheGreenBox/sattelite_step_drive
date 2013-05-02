/* ========================================================
 * Organization: The green box
 *
 * Project name: Satellite stepper drive
 * File name: control_algo.h
 * Description: head of control_algo module
 * ========================================================
 */

#ifndef CONTROL_ALGO_INCLUDED
#define CONTROL_ALGO_INCLUDED


#define ONE_TWO_PHASE_STEPS_NUMBER  4
#define HALF_PHASE_STEPS_NUMBER     8
#define NUMBER_OF_ALGOS             3
#define INVALID                     0
#define ONE_PHASE_CODE              1
#define TWO_PHASE_CODE              2
#define HALF_PHASE_CODE             3

int setAlgoType();
int getNextStep(int*, int*);

#endif //CONTROL_ALGO_INCLUDED

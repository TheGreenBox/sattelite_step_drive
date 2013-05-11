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


#define ONE_PHASE_STEPS_NUMBER      4
#define ONE_PHASE_PWM_STEPS_NUMBER  1

#define TWO_PHASE_STEPS_NUMBER      4
#define TWO_PHASE_PWM_STEPS_NUMBER  1

#define HALF_PHASE_STEPS_NUMBER     8
#define HALF_PHASE_PWM_STEPS_NUMBER 2

#define NUMBER_OF_ALGOS             3
#define CTRL_ALGO_INVALID       0
#define CTRL_ALGO_ONE_PHASE     1
#define CTRL_ALGO_TWO_PHASE     2
#define CTRL_ALGO_HALF_PHASE    3

int setAlgoType(unsigned short);

int getPhasePulseByStep(long long step, int* phaseA, int* phaseB);
 
int getPwmDutyByStep(long long step, unsigned currentPwmDuty, unsigned* pwmDuty);

#endif //_CONTROL_ALGO_INCLUDED_

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

#define ONE_PHASE_ALGO_STEPS        4
#define ONE_PHASE_ALGO_PWM_STEPS    1

#define TWO_PHASE_ALGO_STEPS        4
#define TWO_PHASE_ALGO_PWM_STEPS    1

#define HALF_PHASE_ALGO_STEPS       8
#define HALF_PHASE_ALGO_PWM_STEPS   2

#define NUMBER_OF_ALGOS             3
#define INVALID_CTRL_ALGO           0
#define ONE_PHASE_CTRL_ALGO         1
#define TWO_PHASE_CTRL_ALGO         2
#define HALF_PHASE_CTRL_ALGO        3

#define FEEDBACK_DISABLED           0
#define FEEDBACK_ENABLED            1

typedef struct _PhaseSigns {
    int A;
    int B;
} PhaseSigns;

void setAlgoType(uint_fast8_t algoType);
void setFeedbackFlagTo(uint_fast8_t state);

PhaseSigns getNextPhaseSigns();

// TODO: this mustn't be here, it will be done in current feedback module
uint16_t getPwmDutyByStep();

#endif //_CONTROL_ALGO_INCLUDED_

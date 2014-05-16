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

enum ControlAlgos {
    ONE_PHASE_CTRL_ALGO     = 1,
    TWO_PHASE_CTRL_ALGO     = 2,
    HALF_PHASE_CTRL_ALGO    = 3
};

enum ControlAlgoPhaseSteps {
    ONE_PHASE_ALGO_STEPS    = 4,
    TWO_PHASE_ALGO_STEPS    = 4,
    HALF_PHASE_ALGO_STEPS   = 8
};

enum ControlAlgoPwmSteps {
    ONE_PHASE_ALGO_PWM_STEPS    = 1,
    TWO_PHASE_ALGO_PWM_STEPS    = 1,
    HALF_PHASE_ALGO_PWM_STEPS   = 2
};

enum controlAlgoFlagBits {
    SENSOR_FEEDBACK = 1
};

typedef struct _controlAlgoFlags {
    uint_fast8_t feedbackActive : 1;
    uint_fast8_t reserved       : 7;
} controlAlgoFlags;

extern controlAlgoFlags ctrlFlags;

typedef struct _PhaseSigns {
    int_fast8_t A;
    int_fast8_t B;
} PhaseSigns;

void setAlgoType(uint_fast8_t algoType);
PhaseSigns getNextPhaseSigns();

// TODO: this mustn't be here, it will be done in current feedback module
uint16_t getPwmDutyByStep();

#endif //_CONTROL_ALGO_INCLUDED_

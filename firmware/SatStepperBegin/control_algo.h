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

typedef struct _controlAlgoFlags {
    uint_fast8_t feedbackActive : 1;
    uint_fast8_t reserved       : 7;
} controlAlgoFlags;

extern controlAlgoFlags     ctrlFlags;

typedef struct _PhaseSigns {
    int_fast8_t A;
    int_fast8_t B;
} PhaseSigns;

PhaseSigns getNextPhaseSigns();

// TODO: this mustn't be here, it will be done in current feedback module
uint16_t getPwmDutyByStep();

#endif //_CONTROL_ALGO_INCLUDED_

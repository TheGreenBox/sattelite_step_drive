/* ========================================================
 * Organization: The Green Box
 *
 * Project name: Satellite stepper drive
 * File name:  SatStepperBegin/state.c
 * Description:
 * ========================================================
 */

#include <stdio.h>
#include "state.h"
#include "control_algo.h"

volatile GlobalState gState;

const GlobalConfig gConfig = {
    MAX_PWM_DUTY,
    HALF_PHASE_ALGO
};

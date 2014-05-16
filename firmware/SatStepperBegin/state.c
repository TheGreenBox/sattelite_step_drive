/* ========================================================
 * Organization: The Green Box
 *
 * Project name: Satellite stepper drive
 * File name:  SatStepperBegin/state.c
 * Description:
 * ========================================================
 */

#include "state.h"
#include "control_algo.h"
#include "connection_types.h"

volatile GlobalState gState;

const GlobalConfig gConfig = {
    MAX_PWM_DUTY,
    HALF_PHASE_CONNECTION
};

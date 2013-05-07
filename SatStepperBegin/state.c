/* ========================================================
 * Organization: The Green Box
 * 
 * Project name: Satellite stepper drive
 * File name:  SatStepperBegin/state.c
 * Description:
 * Author: akindyakov, snikitin
 * ========================================================
 */

#include "state.h"
#include "control_algo.h"

volatile GlobalState gState;

const GlobalConfig gConfig = {
					            1000,
                                CTRL_ALGO_ONE_PHASE              
					         };

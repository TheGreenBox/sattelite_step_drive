/**
 * Organization:    The Green Box
 * Project name:    Satellite stepper drive
 *
 * @file            state.c
 * @brief           Global state module
 *
 */

#include <stdio.h>
#include "state.h"
#include "algo_types.h"
#include "control_algo.h"

volatile GlobalState gState;

const GlobalConfig gConfig = {
    ONE_PHASE_ALGO,
    25000,
    1,
    200
};

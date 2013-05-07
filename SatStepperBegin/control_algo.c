/* ========================================================
 * Organization: The green box
 *
 * Project name: Satellite stepper drive
 * File name: control_algo.c
 * Description: module for setting algo type and sending
 * A and B phase states for next step
 * Author: SNikitin
 * ========================================================
 */

#include <stdio.h>
#include "control_algo.h"

//arrays of step by step phase states for different algorythms
static int onePhaseAlgoA[ONE_TWO_PHASE_STEPS_NUMBER]  = { 1 , 0 , -1 ,  0 };
static int onePhaseAlgoB[ONE_TWO_PHASE_STEPS_NUMBER]  = { 0 , 1 ,  0 , -1 };

static int twoPhaseAlgoA[ONE_TWO_PHASE_STEPS_NUMBER]  = { 1 , -1 , -1 ,  1 };
static int twoPhaseAlgoB[ONE_TWO_PHASE_STEPS_NUMBER]  = { 1 ,  1 , -1 , -1 };

static int halfPhaseAlgoA[HALF_PHASE_STEPS_NUMBER] = { 1 , 1 , 0 , -1 , -1 , -1,   0 ,  1 };
static int halfPhaseAlgoB[HALF_PHASE_STEPS_NUMBER] = { 0 , 1 , 1 ,  1 ,  0 , -1 , -1 , -1 };

struct AlgoType
{
    int* phaseA;
    int* phaseB;
    
    int algoStepsNumber;
};

//const structure variables init
static struct AlgoType 
onePhaseParametrs  = {   
                        onePhaseAlgoA ,
                        onePhaseAlgoB ,
                        ONE_TWO_PHASE_STEPS_NUMBER 
                     },

twoPhaseParametrs  = {
                        twoPhaseAlgoA ,
                        twoPhaseAlgoB ,
                        ONE_TWO_PHASE_STEPS_NUMBER 
                     },

halfPhaseParametrs = {    
                        halfPhaseAlgoA ,
                        halfPhaseAlgoB ,
                        HALF_PHASE_STEPS_NUMBER  
                     };

static struct AlgoType* pCurrentAlgoStruct = NULL;
static int nextStep = 0;

// sets control algorythm type that will be used
int setAlgoType(unsigned short algoTypeCode)
{
    nextStep = 0;
    switch (algoTypeCode)
    {
        case CTRL_ALGO_ONE_PHASE:
            pCurrentAlgoStruct = &onePhaseParametrs;
            break;
        case CTRL_ALGO_TWO_PHASE:
            pCurrentAlgoStruct = &twoPhaseParametrs;
            break;
        case CTRL_ALGO_HALF_PHASE:
            pCurrentAlgoStruct = &halfPhaseParametrs;
            break;
        default:
            return 1;
    }
    return 0;
}

// writes phase states for next step to PWM registers
int getNextStep(int* phaseA, int* phaseB)
{
    // if setAlgoType wasn't used
    if (pCurrentAlgoStruct == NULL)
    {
        return 1;
    }
    *phaseA = pCurrentAlgoStruct->phaseA[nextStep];
    *phaseB = pCurrentAlgoStruct->phaseB[nextStep];
    if (++nextStep >= pCurrentAlgoStruct->algoStepsNumber)
    {
        nextStep = 0;
    }
    return 0;
}


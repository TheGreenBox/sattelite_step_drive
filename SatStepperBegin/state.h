/* ========================================================
 * Organization: The Green Box
 * 
 * Project name: Satellite stepper drive
 * File name:  SatStepperBegin/state.h
 * Description:
 * Author: akindyakov, snikitin
 * ========================================================
 */

#ifndef _GLOBAL_STATE_H_
#define _GLOBAL_STATE_H_

typedef struct _GlobalState
{
    long long systemTimer;
    
    long long rotationTicker;
    
} GlobalState;

volatile extern GlobalState gState; 

#endif //_GLOBAL_STATE_H_

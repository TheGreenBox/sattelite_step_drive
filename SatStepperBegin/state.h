/* ========================================================
 * Organization: The Green Box
 * 
 * Project name: Satellite stepper drive
 * File name:  SatStepperBegin/state.h
 * Description:
 * Author: akindyakov, snikitin
 * ========================================================
 */

typedef struct _GlobalState
{
    long long systemTimer;
    
    long long rotationTicker;
    
} GlobalState;

volatile extern GlobalState gState; 

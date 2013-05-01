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
    Uint32_t systemTimer;
    
    Uint32_t rotationTicker;
    
} GlobalState;

volatile extern GlobalState gState; 

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

typedef struct _MotorControl
{
    unsigned int pwmLevelA;
    unsigned int pwmLevelB;
    unsigned int stepTimeout;
} MotorControl;

typedef struct _GlobalState
{
    long long systemTimer;
    long long rotationTicker;
    MotorControl motorControl;
} GlobalState;

extern volatile GlobalState gState;

typedef struct _GlobalConfig
{
    unsigned short pwmPeriod;
} GlobalConfig;

extern const GlobalConfig gConfig;

#endif //_GLOBAL_STATE_H_

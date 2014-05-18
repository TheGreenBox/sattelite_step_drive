/* ========================================================
 * Organization: The Green Box
 *
 * Project name: Satellite stepper drive
 * File name:  SatStepperBegin/state.h
 * Description:
 * ========================================================
 */

#ifndef _GLOBAL_STATE_H_
#define _GLOBAL_STATE_H_

#include <stdint.h>
#include "algo_types.h"
#include "control_algo.h"

typedef struct _MotorControl {
    uint32_t    pwmDutyCycle;
    uint32_t    stepTimeoutUsec;
    int_fast8_t rotationDirection;  // 1 or -1 or 0
} MotorControl;

typedef struct _EncoderCounts {
    int32_t     raw;
    int32_t     precise;
    int_fast8_t direction;
    uint16_t    invSpeed;
#ifdef DEBUG
    uint32_t    errors;
#endif // DEBUG
} EncoderCounts;

typedef struct _SetPoint {
    uint32_t position;
    uint16_t speed;
} SetPoint;

typedef struct _GlobalState {
    uint64_t        stepTicker;
    uint16_t        currentSpeed;
    uint_fast16_t   adc[5];
    uint_fast16_t   currentCommAngle;
    SetPoint        setPoint;
    MotorControl    motorControl;
    EncoderCounts   encoder;
} GlobalState;

extern volatile GlobalState gState;

typedef struct _GlobalConfig {
    uint16_t   algoType;
    uint16_t   encoderRange;
    uint16_t   motorReduction;
    uint16_t   oneRevolEngineSteps;
} GlobalConfig;

extern const GlobalConfig gConfig;

#endif //_GLOBAL_STATE_H_

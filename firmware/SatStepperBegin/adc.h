/**
 * Organization: The Green Box
 * Project name: Satellite stepper drive
 *
 * @file adc.h
 * @brief ADC initialization and interrupts
 *  [github issue #44](https://github.com/TheGreenBox/sattelite_step_drive/issues/44),
 *  [github issue #47](https://github.com/TheGreenBox/sattelite_step_drive/issues/47)
 */

#pragma once

#include <stdint.h>

typedef uint16_t TAdcCounts;
typedef void (* TSharedAdcHandler)(uint16_t);

#define NUM_ACTIVE_ADC_CHANELS 5
#define ADC_BITNESS 12

void adcInit();
void setAdcChanelHandler(uint_fast8_t ch, TSharedAdcHandler);


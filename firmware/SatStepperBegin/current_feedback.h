/**
 * Organization: The green box
 * Project name: Satellite stepper drive
 *
 * @file    current_feedback.h
 * @brief   Header for current feedback logic module
 *  [issue](https://github.com/TheGreenBox/sattelite_step_drive/issues/44)
 */

#pragma once

typedef enum {
    ECurrentChA = 0,
    ECurrentChB = 1,
    ECurrentChC = 2,
    ECurrentChD = 3,
    ECurrentChVCC = 4,
    ECurrentChLast
} ECurrentChannel;

void correctPwmByAdc(ECurrentChannel ch, uint16_t adc);


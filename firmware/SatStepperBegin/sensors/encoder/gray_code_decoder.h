/**
 * Organization: The Green Box
 * Project name:    Satellite stepper drive
 *
 * @file    gray_code_encoder.h
 * @brief   Parsing 2lines binary gray code for relative incremental sensors
 *  [wiki](https://github.com/TheGreenBox/sattelite_step_drive/wiki/sensor_encoder)
 */

#pragma once

extern int gray_code_encoder_masks[16];
void debugRecorder(int a, int b);

#define GREY_CODE_STEP_DECODER(oldA, oldB, newA, newB)  \
    gray_code_encoder_masks[0 | (newB<<3) | (newA<<2) | (oldB<<1) | oldA]


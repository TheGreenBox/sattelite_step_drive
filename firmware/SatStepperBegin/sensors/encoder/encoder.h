/**
 * Organization: The Green Box
 * Project name:    Satellite stepper drive
 *
 * @file    encoder.c
 * @brief
 *  [wiki](https://github.com/TheGreenBox/sattelite_step_drive/wiki/sensor_encoder)
 */

#pragma once
typedef void (* _sharedEncoderHandler)(void);

void encoderInit();
void installSharedEncoderHandler(_sharedEncoderHandler handler);
void disableSharedEncoderHandler();

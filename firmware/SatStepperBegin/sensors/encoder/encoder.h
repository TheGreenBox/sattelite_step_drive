/**
 * Organization:    The Green Box
 * Project name:    Satellite stepper drive
 *
 * @file            encoder.h
 * @brief           Header of encoder interrupt logic module
 *
 * [wiki](https://github.com/TheGreenBox/sattelite_step_drive/wiki/sensor_encoder)
 *
 */

#pragma once
typedef void (* _sharedEncoderHandler)(void);

void encoderInit();
void setSharedEncoderHandler(_sharedEncoderHandler handler);
void clearSharedEncoderHandler();

/**
 * Organization: The green box
 * Project name: Satellite stepper drive
 *
 * @file    elementary_motions.c
 * @brief   Header for pretty little simple algos for elemetnaty motions
 *  github issue: [#54](https://github.com/TheGreenBox/sattelite_step_drive/issues/54)
 */

#pragma once

/**
 *  @brief Move sensor shaft to index bit
 *      no more of one complete revolution
 *      [github issue #54](https://github.com/TheGreenBox/sattelite_step_drive/issues/54)
 */
void encoderCalibration();

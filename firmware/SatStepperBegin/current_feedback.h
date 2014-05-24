/**
 * Organization: The green box
 * Project name: Satellite stepper drive
 *
 * @file    current_feedback.h
 * @brief   Header for current feedback logic module
 *  [github issue #44](https://github.com/TheGreenBox/sattelite_step_drive/issues/44)
 */

#pragma once

/** \addtogroup Curent_feedback
 *  @{
 */

/**
 *  @ingroup coefficients
 *  @{
 */
#define CURENT_COEFF_RANK 10
#define CURENT_COEFF_DIVIDER (1 << PWM_COEFF_RANK)
/** @}*/

/**
 *  @brief init current feedback cicle
 */
void currentFeedbackInit();

/**
 *  @brief set value for current feedback sheme
 *  @param current in Amperes in fixed point with rank CURENT_COEFF_RANK
 *      @see CURENT_COEFF_RANK
 *      @see CURENT_COEFF_DIVIDER
 */
void setCurrent(uint16_t current);

/** @}*/

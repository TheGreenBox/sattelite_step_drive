/* ========================================================
 * Organization: The Green Box
 *
 * Project name:    Satellite stepper drive
 * File name:       encoder.h
 * Description:
 * Author:          AKindyakov
 * ========================================================
 */

#pragma once

extern int gray_code_encoder_masks[16];

#define GREY_CODE_STEP_DECODER(oldA, oldB, newA, newB)  \
    gray_code_encoder_masks[0 | oldA | (oldB>>1) | (newA>>2) | (newB>>3)]


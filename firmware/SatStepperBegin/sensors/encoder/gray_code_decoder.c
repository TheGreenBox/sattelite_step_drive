/**
 * Organization: The Green Box
 * Project name:    Satellite stepper drive
 *
 * @file    gray_code_encoder.c
 * @brief   Parsing 2lines binary gray code for relative incremental sensors
 *  [wiki](https://github.com/TheGreenBox/sattelite_step_drive/wiki/sensor_encoder)
 */

#include "gray_code_decoder.h"

int gray_code_encoder_masks[16] = {0, 1, -1, 0, -1, 0, 0, 1, 1, 0, 0, -1, 0, -1, 1, 0};

/**
 positive
 [1 -> 1] [1 -> 0] [0 -> 0] [0 -> 1]
 [0 -> 1] [1 -> 1] [1 -> 0] [0 -> 0]
 0b00001101 = 0x0d ( 13 )
 0b00001011 = 0x0b ( 11 )
 0b00000010 = 0x02 ( 2  )
 0b00000100 = 0x04 ( 4  )
**

 negative
 [1 -> 0] [0 -> 0] [0 -> 1] [1 -> 1]
 [0 -> 0] [0 -> 1] [1 -> 1] [1 -> 0]
 0b00000001 = 0x01 ( 1  )
 0b00001000 = 0x08 ( 8  )
 0b00001110 = 0x0e ( 14 )
 0b00000111 = 0x07 ( 7  )
**

 invalid
 [0 -> 0] [1 -> 1] [1 -> 1] [0 -> 0]
 [0 -> 0] [1 -> 1] [0 -> 0] [1 -> 1]
 0b00000000 = 0x00 ( 0  )
 0b00001111 = 0x0f ( 15 )
 0b00000101 = 0x05 ( 5  )
 0b00001010 = 0x0a ( 10 )
**

 invalid
 [0 -> 1] [1 -> 0] [0 -> 1] [1 -> 0]
 [0 -> 1] [1 -> 0] [1 -> 0] [0 -> 1]
 0b00001100 = 0x0c ( 12 )
 0b00000011 = 0x03 ( 3  )
 0b00000110 = 0x06 ( 6  )
 0b00001001 = 0x09 ( 9  )
*/

/*
*
* typedef union {
*     struct {
*         unsigned char oldA  : 1; //!< old state a channel
*         unsigned char oldB  : 1; //!< old state b channel
*         unsigned char newA  : 1; //!< new state a channel
*         unsigned char newB  : 1; //!< new state b channel
*         unsigned char empty : 4; //!< reserved sace
*     } step;
*     unsigned char bin;
* } EncoderKey;
*
* int greyCodeStepDecoder(unsigned char oldA, unsigned char oldB, unsigned char newA, unsigned char newB) {
*     EncoderKey key;
*     key.bin = 0;
*     key.step.oldA = oldA;
*     key.step.oldB = oldB;
*     key.step.newA = newA;
*     key.step.newB = newB;
*     return gray_code_encoder_masks[key.bin];
* }
*
*/


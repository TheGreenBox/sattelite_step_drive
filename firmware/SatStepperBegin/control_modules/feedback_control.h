/**
 * Organization:    The Green Box
 * Project name:    Satellite stepper drive
 *
 * @file            feedback_control.h
 * @brief           Header of position feedback module
 *
 */

#ifndef _FEEDBACK_CONTROL__H_
#define _FEEDBACK_CONTROL__H_

#define COMM_ANGLE_RANK     10
#define COMM_ANGLE_DIVIDER  (1 << COMM_ANGLE_RANK)

void switchPhasesIfNecessary();

void enableFeedbackControl();
void disableFeedbackControl();

int32_t getAlgoStepSizeInEncTicks();
void recomputeAlgoConsts();

#endif //_FEEDBACK_CONTROL__H_

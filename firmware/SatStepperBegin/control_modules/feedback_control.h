#ifndef _FEEDBACK_CONTROL__H_
#define _FEEDBACK_CONTROL__H_

#define COMM_ANGLE_RANK     10
#define COMM_ANGLE_DIVIDER  (1 << COMM_ANGLE_RANK)

void switchPhasesOnce();
void switchPhasesIfNecessary();

void enableFeedbackControl();
void disableFeedbackControl();

#endif //_FEEDBACK_CONTROL__H_

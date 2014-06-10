/**
 * Organization:    The Green Box
 * Project name:    Satellite stepper drive
 *
 * @file            current_feedback.c
 * @brief           Header of sensorless movement algorithm module
 *
 */

#pragma once

void syncControlInterruptHandler(void);

void enableSyncControl();
void disableSyncControl();

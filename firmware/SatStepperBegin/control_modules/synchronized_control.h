/* ========================================================
 * Organization: The Green Box
 *
 * Project name: Satellite stepper drive
 * File name:    synchronized_control.h
 * Description:  header for control_interrupt.c
 * Author: SNikitin
 * ========================================================
 */

#pragma once

void syncControlInterruptHandler(void);

void enableSyncControl();
void disableSyncControl();

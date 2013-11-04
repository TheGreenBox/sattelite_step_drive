/* ==============================================================================
System Name:  	Stepper

File Name:		Stepper.h

Description:	Primary system header file for the Real Implementation of Stepper
                Motor

Originator:		Digital control systems Group - Texas Instruments

Note: In this software, the default inverter is supposed to be DRV8412 kit.
=====================================================================================
 History:
-------------------------------------------------------------------------------------
 07-28-2010	Version 1.0
=================================================================================  */

/*-------------------------------------------------------------------------------
Next, Include project specific include files.
-------------------------------------------------------------------------------*/

#include "pid_reg3.h"       	// Include header for the PIDREG3 object
#include "rampgen.h"        	// Include header for the RAMPGEN object
#include "rmp_cntl.h"       	// Include header for the RMPCNTL object
#include "speed_fr.h"			// Include header for the SPEED_MEAS_QEP object
#include "sin_cos_table.h"

#if (DSP2803x_DEVICE_H==1)
#include "f2803xileg_vdc_Stepper.h" 	// Include header for the ILEG2DCBUSMEAS object
#include "f2803xpwm_Stepper.h"        	// Include header for the PWMGEN object
#include "f2803xpwmdac_Stepper.h"      // Include header for the PWMGEN object
#include "f2803xqep_Stepper.h"        	// Include header for the QEP object
#endif

#include "dlog4ch-Stepper.h" // Include header for the DLOG_4CH object

//===========================================================================
// No more.
//===========================================================================

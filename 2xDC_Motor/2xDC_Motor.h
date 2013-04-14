/* ==============================================================================
System Name:  	2xDC_Motor

File Name:		2xDC_Motor.h

Description:	Primary system header file for the Real Implementation of Brushed  
          		Permanent-Magnet DC Motor(s) (DCMOTOR) 

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

#if (DSP2803x_DEVICE_H==1)
#include "f2803xileg_vdc_2xDC.h" 	// Include header for the ILEG2DCBUSMEAS object 
#include "f2803xpwm_2xDC.h"        	// Include header for the PWMGEN object
#include "f2803xpwmdac_2xDC.h"      // Include header for the PWMGEN object
#include "f2803xqep_2xDC.h"        	// Include header for the QEP object
#endif

#include "dlog4ch-2xDC_Motor.h" // Include header for the DLOG_4CH object

//===========================================================================
// No more.
//===========================================================================

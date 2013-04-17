/* ==============================================================================
System Name:   2xDC_Motor

File Name:     2xDC_Motor.C

Description:   Primary system file for the Real Implementation of Brushed
               Permanent-Magnet DC Motor(s) (DCMOTOR)

Originator:    Digital control systems Group - Texas Instruments

Note: In this software, the default inverter is supposed to be DRV8412 kit.
=====================================================================================
 History: 07-28-2010 Version 1.0: Initial Release
=================================================================================  */

// Include header files used in the main function

#include "PeripheralHeaderIncludes.h"
#include "IQmathLib.h"
#include "2xDC_Motor.h"
#include "2xDC_Motor-Settings.h"
#include <math.h>


// Prototype statements for functions found within this file.
interrupt void MainISR(void);
void DeviceInit();
void MemCopy();
void InitFlash();
// State Machine function prototypes
//------------------------------------
// Alpha states
void A0(void); //state A0
void B0(void); //state B0
void C0(void); //state C0

// A branch states
void A1(void); //state A1
void A2(void); //state A2
void A3(void); //state A3

// B branch states
void B1(void); //state B1
void B2(void); //state B2
void B3(void); //state B3

// C branch states
void C1(void); //state C1
void C2(void); //state C2
void C3(void); //state C3

// Variable declarations
void (*Alpha_State_Ptr)(void);   // Base States pointer
void (*A_Task_Ptr)(void);     // State pointer A branch
void (*B_Task_Ptr)(void);     // State pointer B branch
void (*C_Task_Ptr)(void);     // State pointer C branch

// Used for running BackGround in flash, and ISR in RAM
extern Uint16 *RamfuncsLoadStart, *RamfuncsLoadEnd, *RamfuncsRunStart;


int16 VTimer0[4];       // Virtual Timers slaved off CPU Timer 0 (A events)
int16 VTimer1[4];       // Virtual Timers slaved off CPU Timer 1 (B events)
int16 VTimer2[4];       // Virtual Timers slaved off CPU Timer 2 (C events)
int16 SerialCommsTimer;

// Global variables used in this system

_iq VRef1 = _IQ(0.0);            // Motor 1 voltge reference (pu)
_iq IRef1 = _IQ(0.0);            // Motor 1 current reference (pu)
_iq IFdbk1;                      // Motor 1 current feedback (pu)
_iq IFdbk1a;                     // Phase 1 current feedback (pu)
_iq IFdbk1b;                     // Phase 1 current feedback (pu)
//not used for this project.  Save for future use
//_iq SpeedRef1 = _IQ(0.25);     // Motor 1 Speed reference (pu)
Uint16 Rotation1 = 1;            // Motor 1 PWM direction

_iq VRef2 = _IQ(0.0);            // Motor 2 voltge reference (pu)
_iq IRef2 = _IQ(0.0);            // Motor 2 current reference (pu)
_iq IFdbk2;                      // Motor 2 current feedback (pu)
_iq IFdbk2c;                     // Phase 2 current feedback (pu)
_iq IFdbk2d;                     // Phase 2 current feedback (pu)
//not used for this project.  Save for future use
//_iq SpeedRef2 = _IQ(0.25);     // Motor 2 Speed reference (pu)
Uint16 Rotation2 = 1;            // Motor 2 PWM direction

float32 T = 0.001/ISR_FREQUENCY; // Samping period (sec), see parameter.h

Uint32 IsrTicker = 0;
Uint16 BackTicker = 0;

int16 PwmDacCh1=0;
int16 PwmDacCh2=0;

int16 DlogCh1 = 0;
int16 DlogCh2 = 0;
int16 DlogCh3 = 0;
int16 DlogCh4 = 0;

#if (BUILDLEVEL==LEVEL2)
Uint16 DRV_RESET = 1;
#else
Uint16 DRV_RESET = 0;
#endif

volatile Uint16 EnableFlag = FALSE;
Uint16 RunMotor = FALSE;

// Instance PID regulators to regulate the current, and speed
PIDREG3 pid1_i = PIDREG3_DEFAULTS;
//not used for this project.  Save for future use
//PIDREG3 pid1_spd = PIDREG3_DEFAULTS;

PIDREG3 pid2_i = PIDREG3_DEFAULTS;

// Instance a PWM driver instance
PWMGEN pwm1 = PWMGEN_DEFAULTS;
PWMGEN pwm2 = PWMGEN_DEFAULTS;

// Instance a PWM DAC driver instance
PWMDAC pwmdac1 = PWMDAC_DEFAULTS;
PWMDAC pwmdac2 = PWMDAC_DEFAULTS;

// Instance a ramp controller to smoothly ramp the frequency
RMPCNTL rc1 = RMPCNTL_DEFAULTS;
RMPCNTL rc2 = RMPCNTL_DEFAULTS;

// Create an instance of DATALOG Module
DLOG_4CH dlog = DLOG_4CH_DEFAULTS;




void main(void)
{

    DeviceInit(); // Device Life support & GPIO

// Only used if running from FLASH
// Note that the variable FLASH is defined by the compiler

#ifdef FLASH
// Copy time critical code and Flash setup code to RAM
// The  RamfuncsLoadStart, RamfuncsLoadEnd, and RamfuncsRunStart
// symbols are created by the linker. Refer to the linker files.
    MemCopy(&RamfuncsLoadStart, &RamfuncsLoadEnd, &RamfuncsRunStart);

// Call Flash Initialization to setup flash waitstates
// This function must reside in RAM
    InitFlash();  // Call the flash wrapper init function
#endif //(FLASH)

    // Waiting for enable flag set
    while (EnableFlag==FALSE)
    {
        BackTicker++;
    }

// Timing sync for slow background tasks
// Timer period definitions found in device specific PeripheralHeaderIncludes.h
    CpuTimer0Regs.PRD.all =  mSec1;    // A tasks
    CpuTimer1Regs.PRD.all =  mSec5;    // B tasks
    CpuTimer2Regs.PRD.all =  mSec50;   // C tasks

// Tasks State-machine init
    Alpha_State_Ptr = &A0;
    A_Task_Ptr = &A1;
    B_Task_Ptr = &B1;
    C_Task_Ptr = &C1;

// Initialize PWM module
    pwm1.PeriodMax = SYSTEM_FREQUENCY*1000000*T/2;  // Prescaler X1 (T1), ISR period = T x 1
    PWM_INIT_MACRO(pwm1)

    pwm2.PeriodMax = SYSTEM_FREQUENCY*1000000*T/2;  // Prescaler X1 (T1), ISR period = T x 1
    PWM_INIT_MACRO(pwm2)

// Initialize PWMDAC module
    pwmdac1.PeriodMax = 500;   // @60Mhz: 1500->20kHz, 1000-> 30kHz, 500->60kHz
    pwmdac1.PwmDacInPointer0 = &PwmDacCh1;
    pwmdac1.PwmDacInPointer1 = &PwmDacCh2;

    PWMDAC_INIT_MACRO(pwmdac1)

// Initialize DATALOG module
    dlog.iptr1 = &DlogCh1;
    dlog.iptr2 = &DlogCh2;
    dlog.iptr3 = &DlogCh3;
    dlog.iptr4 = &DlogCh4;
    dlog.trig_value = 0x1;
    dlog.size = 0x00c8;
    dlog.prescalar = 5;
    dlog.init(&dlog);

// Initialize ADC module
    ADC_MACRO_INIT()

// Initialize the PID_REG3 module for I
    pid1_i.Kp = _IQ(0.318);      //for 24V DC bus
    pid1_i.Ki = _IQ(T/0.0005);
    pid1_i.Kd = _IQ(0/T);
    pid1_i.Kc = _IQ(0.2);
    pid1_i.OutMax = _IQ(0.95);
    pid1_i.OutMin = _IQ(-0.95);

    pid2_i.Kp = _IQ(0.318);      //for 24V DC bus
    pid2_i.Ki = _IQ(T/0.0005);
    pid2_i.Kd = _IQ(0/T);
    pid2_i.Kc = _IQ(0.2);
    pid2_i.OutMax = _IQ(0.95);
    pid2_i.OutMin = _IQ(-0.95);

// Reassign ISRs.

    EALLOW; // This is needed to write to EALLOW protected registers
    PieVectTable.EPWM1_INT = &MainISR;
    EDIS;

// Enable PIE group 3 interrupt 1 for EPWM1_INT
    PieCtrlRegs.PIEIER3.bit.INTx1 = 1;

// Enable CNT_zero interrupt using EPWM1 Time-base
    EPwm1Regs.ETSEL.bit.INTEN = 1;   // Enable EPWM1INT generation
    EPwm1Regs.ETSEL.bit.INTSEL = 1;  // Enable interrupt CNT_zero event
    EPwm1Regs.ETPS.bit.INTPRD = 1;   // Generate interrupt on the 1st event
    EPwm1Regs.ETCLR.bit.INT = 1;     // Enable more interrupts

// Enable CPU INT3 for EPWM1_INT:
    IER |= M_INT3;
// Enable global Interrupts and higher priority real-time debug events:
    EINT;   // Enable Global interrupt INTM
    ERTM;   // Enable Global realtime interrupt DBGM

// IDLE loop. Just sit and loop forever:
    for(;;)  //infinite loop
    {
        // State machine entry & exit point
        //===========================================================
        (*Alpha_State_Ptr)(); // jump to an Alpha state (A0,B0,...)
        //===========================================================

        //Put the DRV chip in RESET if we want the power stage inactive
        if(DRV_RESET)
        {
            GpioDataRegs.GPACLEAR.bit.GPIO19 = 1;
            GpioDataRegs.GPBCLEAR.bit.GPIO32 = 1;
        }
        else
        {
            GpioDataRegs.GPASET.bit.GPIO19 = 1;
            GpioDataRegs.GPBSET.bit.GPIO32 = 1;
        }

    }
} //END MAIN CODE



//=================================================================================
// STATE-MACHINE SEQUENCING AND SYNCRONIZATION FOR SLOW BACKGROUND TASKS
//=================================================================================

//--------------------------------- FRAMEWORK -------------------------------------
void A0(void)
{
    // loop rate synchronizer for A-tasks
    if(CpuTimer0Regs.TCR.bit.TIF == 1)
    {
        CpuTimer0Regs.TCR.bit.TIF = 1; // clear flag

        //-----------------------------------------------------------
        (*A_Task_Ptr)();      // jump to an A Task (A1,A2,A3,...)
        //-----------------------------------------------------------

        VTimer0[0]++;         // virtual timer 0, instance 0 (spare)
        SerialCommsTimer++;
    }

    Alpha_State_Ptr = &B0;    // Comment out to allow only A tasks
}

void B0(void)
{
    // loop rate synchronizer for B-tasks
    if(CpuTimer1Regs.TCR.bit.TIF == 1)
    {
        CpuTimer1Regs.TCR.bit.TIF = 1;          // clear flag

        //-----------------------------------------------------------
        (*B_Task_Ptr)();      // jump to a B Task (B1,B2,B3,...)
        //-----------------------------------------------------------
        VTimer1[0]++;         // virtual timer 1, instance 0 (spare)
    }

    Alpha_State_Ptr = &C0;    // Allow C state tasks
}

void C0(void)
{
    // loop rate synchronizer for C-tasks
    if(CpuTimer2Regs.TCR.bit.TIF == 1)
    {
        CpuTimer2Regs.TCR.bit.TIF = 1;          // clear flag

        //-----------------------------------------------------------
        (*C_Task_Ptr)();      // jump to a C Task (C1,C2,C3,...)
        //-----------------------------------------------------------
        VTimer2[0]++;         //virtual timer 2, instance 0 (spare)
    }

    Alpha_State_Ptr = &A0; // Back to State A0
}


//=================================================================================
// A - TASKS (executed in every 1 msec)
//=================================================================================
//--------------------------------------------------------
void A1(void) // SPARE (not used)
//--------------------------------------------------------
{
    if (EnableFlag == FALSE)
    {
        RunMotor = FALSE;

        EALLOW;
        EPwm1Regs.TZFRC.bit.OST=1;
        EPwm2Regs.TZFRC.bit.OST=1;
        EDIS;
    }
    else if((EnableFlag == TRUE) && (RunMotor == FALSE))
    {
        rc1.TargetValue=0;
        rc1.SetpointValue=0;
        rc2.TargetValue=0;
        rc2.SetpointValue=0;

        pid1_i.Err=0;
        pid1_i.Fdb=0;
        pid1_i.Out=0;
        pid1_i.Ud=0;
        pid1_i.Up=0;
        pid1_i.Ui=0;
        pid1_i.Up1=0;

        pid2_i.Err=0;
        pid2_i.Fdb=0;
        pid2_i.Out=0;
        pid2_i.Ud=0;
        pid2_i.Up=0;
        pid2_i.Ui=0;
        pid2_i.Up1=0;

        RunMotor = TRUE;

        EALLOW;
        EPwm1Regs.TZCLR.bit.OST=1;
        EPwm2Regs.TZCLR.bit.OST=1;
        EDIS;


    }

    //-------------------
    //the next time CpuTimer0 'counter' reaches Period value go to A2
    A_Task_Ptr = &A2;
    //-------------------
}

//-----------------------------------------------------------------
void A2(void) // SPARE (not used)
//-----------------------------------------------------------------
{

    //-------------------
    //the next time CpuTimer0 'counter' reaches Period value go to A3
    A_Task_Ptr = &A3;
    //-------------------
}

//-----------------------------------------
void A3(void) // SPARE (not used)
//-----------------------------------------
{

    //-----------------
    //the next time CpuTimer0 'counter' reaches Period value go to A1
    A_Task_Ptr = &A1;
    //-----------------
}



//=================================================================================
// B - TASKS (executed in every 5 msec)
//=================================================================================

//----------------------------------- USER ----------------------------------------

//----------------------------------------
void B1(void) // Toggle GPIO-00
//----------------------------------------
{

    //-----------------
    //the next time CpuTimer1 'counter' reaches Period value go to B2
    B_Task_Ptr = &B2;
    //-----------------
}

//----------------------------------------
void B2(void) //  SPARE
//----------------------------------------
{

    //-----------------
    //the next time CpuTimer1 'counter' reaches Period value go to B3
    B_Task_Ptr = &B3;
    //-----------------
}

//----------------------------------------
void B3(void) //  SPARE
//----------------------------------------
{

    //-----------------
    //the next time CpuTimer1 'counter' reaches Period value go to B1
    B_Task_Ptr = &B1;
    //-----------------
}


//=================================================================================
// C - TASKS (executed in every 50 msec)
//=================================================================================

//--------------------------------- USER ------------------------------------------

//----------------------------------------
void C1(void)  // Toggle GPIO-34
//----------------------------------------
{

    GpioDataRegs.GPBTOGGLE.bit.GPIO34 = 1;   // Blink LED
    //-----------------
    //the next time CpuTimer2 'counter' reaches Period value go to C2
    C_Task_Ptr = &C2;
    //-----------------

}

//----------------------------------------
void C2(void) //  SPARE
//----------------------------------------
{

    //-----------------
    //the next time CpuTimer2 'counter' reaches Period value go to C3
    C_Task_Ptr = &C3;
    //-----------------
}


//-----------------------------------------
void C3(void) //  SPARE
//-----------------------------------------
{

    //-----------------
    //the next time CpuTimer2 'counter' reaches Period value go to C1
    C_Task_Ptr = &C1;
    //-----------------
}




// MainISR
interrupt void MainISR(void)
{

// Verifying the ISR
    IsrTicker++;

    if(RunMotor)
    {
// =============================== LEVEL 1 ======================================
//   Checks target independent modules, duty cycle waveforms and PWM update
//   Keep the motors disconnected at this level
// ==============================================================================

#if (BUILDLEVEL==LEVEL1)

// ------------------------------------------------------------------------------
//  Connect inputs of the RMP module and call the ramp control macro
// ------------------------------------------------------------------------------
        rc1.TargetValue = VRef1;
        RC_MACRO(rc1)

// ------------------------------------------------------------------------------
//  Connect inputs of the PWM_DRV module and call the PWM signal generation macro
// ------------------------------------------------------------------------------
        pwm1.MfuncC1 = (int16)_IQtoIQ15(_IQabs(rc1.SetpointValue)); // MfuncC1 is in Q15
        PWM_MACRO(pwm1)                            // Calculate the new PWM compare values

        if(rc1.SetpointValue < 0)
        {
            Rotation1 = 0;
        }
        else
        {
            Rotation1 = 1;
        }

        if(Motor==1)
        {
            if(Rotation1==0)
            {
                EPwm1Regs.AQCSFRC.bit.CSFB = 0;    //Forcing Disabled on EPWM1B
                EPwm1Regs.AQCSFRC.bit.CSFA = 1;    //EPWM1A forced low
            }
            else if(Rotation1 == 1)
            {
                EPwm1Regs.AQCSFRC.bit.CSFA = 0;    //Forcing Disabled on EPWM1A
                EPwm1Regs.AQCSFRC.bit.CSFB = 1;    //EPWM1B forced low
            }
            else
            {
                EPwm1Regs.AQCSFRC.bit.CSFA = 1;    //EPWM1A forced low
                EPwm1Regs.AQCSFRC.bit.CSFB = 1;    //EPWM1B forced low
            }
            EPwm1Regs.CMPA.half.CMPA=pwm1.PWM1out;
        }
        else if (Motor==2)
        {
            if(Rotation1==0)
            {
                EPwm2Regs.AQCSFRC.bit.CSFB = 0;    //Forcing Disabled on EPWM2B
                EPwm2Regs.AQCSFRC.bit.CSFA = 1;    //EPWM2A forced low
            }
            else if(Rotation1 == 1)
            {
                EPwm2Regs.AQCSFRC.bit.CSFA = 0;    //Forcing Disabled on EPWM2A
                EPwm2Regs.AQCSFRC.bit.CSFB = 1;    //EPWM2B forced low
            }
            else
            {
                EPwm2Regs.AQCSFRC.bit.CSFA = 1;    //EPWM2A forced low
                EPwm2Regs.AQCSFRC.bit.CSFB = 1;    //EPWM2B forced low
            }
            EPwm2Regs.CMPA.half.CMPA=pwm1.PWM1out;
        }

// ------------------------------------------------------------------------------
//    Connect inputs of the PWMDAC module
// ------------------------------------------------------------------------------
        PwmDacCh1 = (int16)_IQtoIQ15(VRef1);
        PwmDacCh2 = (int16)_IQtoIQ15(rc1.SetpointValue);

// ------------------------------------------------------------------------------
//    Connect inputs of the DATALOG module
// ------------------------------------------------------------------------------
        DlogCh1 = (int16)_IQtoIQ15(VRef1);
        DlogCh2 = (int16)_IQtoIQ15(rc1.SetpointValue);
        DlogCh3 = (int16)_IQtoIQ15(VRef1);
        DlogCh4 = (int16)_IQtoIQ15(rc1.SetpointValue);

#endif // (BUILDLEVEL==LEVEL1)

// =============================== LEVEL 2 ======================================
//   Level 2 verifies the analog-to-digital conversion, offset compensation
// ==============================================================================

#if (BUILDLEVEL==LEVEL2)

// ------------------------------------------------------------------------------
//  Connect inputs of the RMP module and call the ramp control macro
// ------------------------------------------------------------------------------
        rc1.TargetValue = VRef1;
        RC_MACRO(rc1)

// ------------------------------------------------------------------------------
//  Measure phase currents, subtract the offset and normalize from (-0.5,+0.5) to (-1,+1).
// ------------------------------------------------------------------------------
        if(Motor==1)
        {
            IFdbk1b=_IQ15toIQ((AdcResult.ADCRESULT1<<3)-_IQ15(0.5))<<1;
            IFdbk1a=_IQ15toIQ((AdcResult.ADCRESULT0<<3)-_IQ15(0.5))<<1;
            IFdbk1 = (IFdbk1a - IFdbk1b) >> 1;
        }
        else if(Motor==2)
        {
            IFdbk1b=_IQ15toIQ((AdcResult.ADCRESULT4<<3)-_IQ15(0.5))<<1;
            IFdbk1a=_IQ15toIQ((AdcResult.ADCRESULT3<<3)-_IQ15(0.5))<<1;
            IFdbk1 = (IFdbk1a - IFdbk1b) >> 1;
        }

// ------------------------------------------------------------------------------
//  Connect inputs of the PWM_DRV module and call the PWM signal generation macro
// ------------------------------------------------------------------------------
        pwm1.MfuncC1 = (int16)_IQtoIQ15(_IQabs(rc1.SetpointValue)); // MfuncC1 is in Q15
        PWM_MACRO(pwm1)                            // Calculate the new PWM compare values

        if(rc1.SetpointValue < 0)
        {
            Rotation1 = 0;
        }
        else
        {
            Rotation1 = 1;
        }

        if(Motor==1)
        {
            if(Rotation1==0)
            {
                EPwm1Regs.AQCSFRC.bit.CSFB = 0;    //Forcing Disabled on EPWM1B
                EPwm1Regs.AQCSFRC.bit.CSFA = 1;    //EPWM1A forced low
            }
            else if(Rotation1 == 1)
            {
                EPwm1Regs.AQCSFRC.bit.CSFA = 0;    //Forcing Disabled on EPWM1A
                EPwm1Regs.AQCSFRC.bit.CSFB = 1;    //EPWM1B forced low
            }
            else
            {
                EPwm1Regs.AQCSFRC.bit.CSFA = 1;    //EPWM1A forced low
                EPwm1Regs.AQCSFRC.bit.CSFB = 1;    //EPWM1B forced low
            }
            EPwm1Regs.CMPA.half.CMPA=pwm1.PWM1out;
        }
        else if (Motor==2)
        {
            if(Rotation1==0)
            {
                EPwm2Regs.AQCSFRC.bit.CSFB = 0;    //Forcing Disabled on EPWM2B
                EPwm2Regs.AQCSFRC.bit.CSFA = 1;    //EPWM2A forced low
            }
            else if(Rotation1 == 1)
            {
                EPwm2Regs.AQCSFRC.bit.CSFA = 0;    //Forcing Disabled on EPWM2A
                EPwm2Regs.AQCSFRC.bit.CSFB = 1;    //EPWM2B forced low
            }
            else
            {
                EPwm2Regs.AQCSFRC.bit.CSFA = 1;    //EPWM2A forced low
                EPwm2Regs.AQCSFRC.bit.CSFB = 1;    //EPWM2B forced low
            }
            EPwm2Regs.CMPA.half.CMPA=pwm1.PWM1out;
        }

// ------------------------------------------------------------------------------
//    Connect inputs of the PWMDAC module
// ------------------------------------------------------------------------------
        PwmDacCh1 = (int16)_IQtoIQ15(rc1.SetpointValue);
        PwmDacCh2 = (int16)_IQtoIQ15(IFdbk1);

// ------------------------------------------------------------------------------
//    Connect inputs of the DATALOG module
// ------------------------------------------------------------------------------
        DlogCh1 = (int16)_IQtoIQ15(IFdbk1);
        DlogCh2 = (int16)_IQtoIQ15(VRef1);
        DlogCh3 = (int16)_IQtoIQ15(rc1.SetpointValue);
        DlogCh4 = (int16)_IQtoIQ15(rc1.SetpointValue);

#endif // (BUILDLEVEL==LEVEL2)

// =============================== LEVEL 3 ======================================
// Level 3 verifies the current regulation performed by PID
// ==============================================================================

#if (BUILDLEVEL==LEVEL3)

// ------------------------------------------------------------------------------
//  Connect inputs of the RMP module and call the ramp control macro
// ------------------------------------------------------------------------------
        rc1.TargetValue = IRef1;
        RC_MACRO(rc1)

// ------------------------------------------------------------------------------
//  Measure phase currents, subtract the offset and normalize from (-0.5,+0.5) to (-1,+1).
// ------------------------------------------------------------------------------
        if(Motor==1)
        {
            IFdbk1b=_IQ15toIQ((AdcResult.ADCRESULT1<<3)-_IQ15(0.5))<<1;
            IFdbk1a=_IQ15toIQ((AdcResult.ADCRESULT0<<3)-_IQ15(0.5))<<1;
            IFdbk1 = (IFdbk1a - IFdbk1b) >> 1;
        }
        else if(Motor==2)
        {
            IFdbk1b=_IQ15toIQ((AdcResult.ADCRESULT4<<3)-_IQ15(0.5))<<1;
            IFdbk1a=_IQ15toIQ((AdcResult.ADCRESULT3<<3)-_IQ15(0.5))<<1;
            IFdbk1 = (IFdbk1a - IFdbk1b) >> 1;
        }

// ------------------------------------------------------------------------------
//  Connect inputs of the PID_REG3 module and call the PID controller macro
// ------------------------------------------------------------------------------
        pid1_i.Ref = rc1.SetpointValue;
        pid1_i.Fdb = IFdbk1;
        PID_MACRO(pid1_i)

// ------------------------------------------------------------------------------
//  Connect inputs of the PWM_DRV module and call the PWM signal generation macro
// ------------------------------------------------------------------------------
        pwm1.MfuncC1 = (int16)_IQtoIQ15(_IQabs(pid1_i.Out)); // MfuncC1 is in Q15
        PWM_MACRO(pwm1)                            // Calculate the new PWM compare values

        if(pid1_i.Out < 0)
        {
            Rotation1 = 0;
        }
        else
        {
            Rotation1 = 1;
        }

        if(Motor==1)
        {
            if(Rotation1==0)
            {
                EPwm1Regs.AQCSFRC.bit.CSFB = 0;    //Forcing Disabled on EPWM1B
                EPwm1Regs.AQCSFRC.bit.CSFA = 1;    //EPWM1A forced low
            }
            else if(Rotation1 == 1)
            {
                EPwm1Regs.AQCSFRC.bit.CSFA = 0;    //Forcing Disabled on EPWM1A
                EPwm1Regs.AQCSFRC.bit.CSFB = 1;    //EPWM1B forced low
            }
            else
            {
                EPwm1Regs.AQCSFRC.bit.CSFA = 1;    //EPWM1A forced low
                EPwm1Regs.AQCSFRC.bit.CSFB = 1;    //EPWM1B forced low
            }
            EPwm1Regs.CMPA.half.CMPA=pwm1.PWM1out;
        }
        else if (Motor==2)
        {
            if(Rotation1==0)
            {
                EPwm2Regs.AQCSFRC.bit.CSFB = 0;    //Forcing Disabled on EPWM2B
                EPwm2Regs.AQCSFRC.bit.CSFA = 1;    //EPWM2A forced low
            }
            else if(Rotation1 == 1)
            {
                EPwm2Regs.AQCSFRC.bit.CSFA = 0;    //Forcing Disabled on EPWM2A
                EPwm2Regs.AQCSFRC.bit.CSFB = 1;    //EPWM2B forced low
            }
            else
            {
                EPwm2Regs.AQCSFRC.bit.CSFA = 1;    //EPWM2A forced low
                EPwm2Regs.AQCSFRC.bit.CSFB = 1;    //EPWM2B forced low
            }
            EPwm2Regs.CMPA.half.CMPA=pwm1.PWM1out;
        }

// ------------------------------------------------------------------------------
//    Connect inputs of the PWMDAC module
// ------------------------------------------------------------------------------
        PwmDacCh1 = (int16)_IQtoIQ15(rc1.SetpointValue);
        PwmDacCh2 = (int16)_IQtoIQ15(IFdbk1);

// ------------------------------------------------------------------------------
//    Connect inputs of the DATALOG module
// ------------------------------------------------------------------------------
        DlogCh1 = (int16)_IQtoIQ15(IFdbk1);
        DlogCh2 = (int16)_IQtoIQ15(VRef1);
        DlogCh3 = (int16)_IQtoIQ15(rc1.SetpointValue);
        DlogCh4 = (int16)_IQtoIQ15(rc1.SetpointValue);

#endif // (BUILDLEVEL==LEVEL3)


// =============================== LEVEL 4 ======================================
//   Level 4 runs two independent axes with closed loop current control
// ==============================================================================
#if (BUILDLEVEL==LEVEL4)

// ------------------------------------------------------------------------------
//  Connect inputs of the RMP module and call the ramp control macro
// ------------------------------------------------------------------------------
        rc1.TargetValue = IRef1;
        RC_MACRO(rc1)

        rc2.TargetValue = IRef2;
        RC_MACRO(rc2)

// ------------------------------------------------------------------------------
//  Measure phase currents, subtract the offset and normalize from (-0.5,+0.5) to (-1,+1).
// ------------------------------------------------------------------------------
        IFdbk1b=_IQ15toIQ((AdcResult.ADCRESULT1<<3)-_IQ15(0.5))<<1;
        IFdbk1a=_IQ15toIQ((AdcResult.ADCRESULT0<<3)-_IQ15(0.5))<<1;
        IFdbk1 = (IFdbk1a - IFdbk1b) >> 1;

        IFdbk2d=_IQ15toIQ((AdcResult.ADCRESULT4<<3)-_IQ15(0.5))<<1;
        IFdbk2c=_IQ15toIQ((AdcResult.ADCRESULT3<<3)-_IQ15(0.5))<<1;
        IFdbk2 = (IFdbk2c - IFdbk2d) >> 1;

// ------------------------------------------------------------------------------
//  Connect inputs of the PID_REG3 module and call the PID controller macro
// ------------------------------------------------------------------------------
        pid1_i.Ref = rc1.SetpointValue;
        pid1_i.Fdb = IFdbk1;
        PID_MACRO(pid1_i)

        pid2_i.Ref = rc2.SetpointValue;
        pid2_i.Fdb = IFdbk2;
        PID_MACRO(pid2_i)

// ------------------------------------------------------------------------------
//  Connect inputs of the PWM_DRV module and call the PWM signal generation macro
// ------------------------------------------------------------------------------
//update PWM for Motor 1
        pwm1.MfuncC1 = (int16)_IQtoIQ15(_IQabs(pid1_i.Out));   // MfuncC1 is in Q15
        PWM_MACRO(pwm1)                                     // Calculate the new PWM compare values

        if(pid1_i.Out < 0)
        {
            Rotation1 = 0;
        }
        else
        {
            Rotation1 = 1;
        }

        if(Rotation1==0)
        {
            EPwm1Regs.AQCSFRC.bit.CSFB = 0;     //Forcing Disabled on EPWM1B
            EPwm1Regs.AQCSFRC.bit.CSFA = 1;     //EPWM1A forced low
        }
        else if(Rotation1 == 1)
        {
            EPwm1Regs.AQCSFRC.bit.CSFA = 0;     //Forcing Disabled on EPWM1A
            EPwm1Regs.AQCSFRC.bit.CSFB = 1;     //EPWM1B forced low
        }
        else
        {
            EPwm1Regs.AQCSFRC.bit.CSFA = 1;     //EPWM1A forced low
            EPwm1Regs.AQCSFRC.bit.CSFB = 1;     //EPWM1B forced low
        }
        EPwm1Regs.CMPA.half.CMPA=pwm1.PWM1out;

//update pwm for Motor 2
        pwm2.MfuncC1 = (int16)_IQtoIQ15(_IQabs(pid2_i.Out));   // MfuncC1 is in Q15
        PWM_MACRO(pwm2)                                     // Calculate the new PWM compare values

        if(pid2_i.Out < 0)
        {
            Rotation2 = 0;
        }
        else
        {
            Rotation2 = 1;
        }

        if(Rotation2==0)
        {
            EPwm2Regs.AQCSFRC.bit.CSFB = 0;     //Forcing Disabled on EPWM2B
            EPwm2Regs.AQCSFRC.bit.CSFA = 1;     //EPWM2A forced low
        }
        else if(Rotation2 == 1)
        {
            EPwm2Regs.AQCSFRC.bit.CSFA = 0;     //Forcing Disabled on EPWM2A
            EPwm2Regs.AQCSFRC.bit.CSFB = 1;     //EPWM2B forced low
        }
        else
        {
            EPwm2Regs.AQCSFRC.bit.CSFA = 1;     //EPWM2A forced low
            EPwm2Regs.AQCSFRC.bit.CSFB = 1;     //EPWM2B forced low
        }
        EPwm2Regs.CMPA.half.CMPA=pwm2.PWM1out;

// ------------------------------------------------------------------------------
//    Connect inputs of the PWMDAC module
// ------------------------------------------------------------------------------
        PwmDacCh1 = (int16)_IQtoIQ15(IFdbk1);
        PwmDacCh2 = (int16)_IQtoIQ15(IFdbk2);

// ------------------------------------------------------------------------------
//    Connect inputs of the DATALOG module
// ------------------------------------------------------------------------------
        DlogCh1 = (int16)_IQtoIQ15(IFdbk1);
        DlogCh2 = (int16)_IQtoIQ15(IRef1);
        DlogCh3 = (int16)_IQtoIQ15(IFdbk2);
        DlogCh4 = (int16)_IQtoIQ15(IRef2);

#endif // (BUILDLEVEL==LEVEL4)
    }//end if(RunMotor)
// ------------------------------------------------------------------------------
//    Call the PWMDAC update macro.
// ------------------------------------------------------------------------------
    PWMDAC_MACRO(pwmdac1)

// ------------------------------------------------------------------------------
//    Call the DATALOG update function.
// ------------------------------------------------------------------------------
    dlog.update(&dlog);


#if (DSP2803x_DEVICE_H==1)||(DSP280x_DEVICE_H==1)
// Enable more interrupts from this timer
    EPwm1Regs.ETCLR.bit.INT = 1;

// Acknowledge interrupt to recieve more interrupts from PIE group 3
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;
#endif

}

//===========================================================================
// No more.
//===========================================================================

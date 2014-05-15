/* ========================================================
 * Organization: The green box
 *
 * Project name: Satellite stepper drive
 * File name: init.c
 * Description: pwm control
 * ========================================================
 */
#include <PeripheralHeaderIncludes.h>
#include <f2803xbmsk.h>
#include <DSP2803x_EPwm.h>
#include <DSP2803x_EPwm_defines.h>

#include "pwm_wrap_module.h"

static volatile struct EPWM_REGS* pwm_control_regs[2] = {
    &EPwm1Regs,
    &EPwm2Regs
};

static inline void initPWMChannel(volatile struct EPWM_REGS* pwmRegs, short int prescaler) {
    pwmRegs->TBCTL.bit.SYNCOSEL = 0;   // Pass through

    // Init Timer-Base Period Register for EPWM1-EPWM3
    pwmRegs->TBPRD = prescaler;

    // Init Compare Register for EPWM1-EPWM3
    pwmRegs->CMPA.half.CMPA = prescaler;

    // Init Timer-Base Phase Register for EPWM1-EPWM3
    pwmRegs->TBPHS.half.TBPHS = 0;

    // Allow each timer to be sync'ed
    pwmRegs->TBCTL.bit.PHSEN = TB_ENABLE;

    // Init Timer-Base Control Register for EPWM1-EPWM3
    // page 106 ref guide pwm
    pwmRegs->TBCTL.bit.PHSDIR    = TB_UP;
    pwmRegs->TBCTL.bit.SYNCOSEL  = TB_SYNC_IN;
    pwmRegs->TBCTL.bit.PRDLD     = TB_IMMEDIATE;    // Set immediate load
    pwmRegs->TBCTL.bit.CTRMODE   = TB_COUNT_UPDOWN; // Symmetrical mode
    pwmRegs->TBCTL.bit.HSPCLKDIV = TB_DIV1;         // PRESCALE_X_1
    pwmRegs->TBCTL.bit.CLKDIV    = TB_DIV1;         // PRESCALE_X_1
    pwmRegs->TBCTL.bit.FREE_SOFT = 2;               // FREE RUN;

    // Init Compare Control Register for EPWM1-EPWM3
    pwmRegs->CMPCTL.bit.LOADAMODE = CC_CTR_ZERO; // 0:1 Active compare A
    pwmRegs->CMPCTL.bit.LOADBMODE = CC_CTR_ZERO; // 3:2 Active compare B
    pwmRegs->CMPCTL.bit.SHDWAMODE = CC_SHADOW;   // 4   Compare A block operating mode
    pwmRegs->CMPCTL.bit.SHDWBMODE = CC_SHADOW;   // 6   Compare B block operating mode
    pwmRegs->CMPCTL.bit.SHDWAFULL = CC_SHADOW;   // 8   Compare A Shadow registers full Status
    pwmRegs->CMPCTL.bit.SHDWBFULL = CC_SHADOW;   // 9   Compare B Shadow registers full Status

    // Init Action Qualifier Output A Register for EPWM1-EPWM3
    pwmRegs->AQCTLA.all = CAU_SET + CAD_CLEAR;

    // Init Action Qualifier Output A Register for EPWM1-EPWM3
    pwmRegs->AQCTLB.all = CAU_SET + CAD_CLEAR;

    // Init Action Qualifier S/W Force Register for EPWM1-EPWM2
    pwmRegs->AQSFRC.all = RLDCSF_PRD;

    // Init Dead-Band Generator Control Register for EPWM1-EPWM3
    pwmRegs->DBCTL.bit.OUT_MODE  = DB_DISABLE; // 1:0    Dead Band Output Mode Control
    pwmRegs->DBCTL.bit.POLSEL    = DB_ACTV_HI; // 3:2    Polarity Select Control
    pwmRegs->DBCTL.bit.IN_MODE   = DBA_ALL;    // 5:4    Dead Band Input Select Mode Control
    pwmRegs->DBCTL.bit.HALFCYCLE = 1;          // 15     Half Cycle Clocking Enable
    // Init PWM Chopper Control Register for EPWM1-EPWM3
    pwmRegs->PCCTL.all = CHPEN_DISABLE;

    // Enable EALLOW
    EALLOW;

    // Init Trip Zone Select Register
    pwmRegs->TZSEL.all = ENABLE_TZ2_OST + ENABLE_TZ3_OST;

    // Init Trip Zone Control Register
    pwmRegs->TZCTL.bit.TZA = TZ_FORCE_LO;     // 1:0    TZ1 to TZ6 Trip Action On EPWMxA
    pwmRegs->TZCTL.bit.TZB = TZ_FORCE_LO;     // 3:2    TZ1 to TZ6 Trip Action On EPWMxB
    pwmRegs->TZCTL.bit.DCAEVT1 = TZ_FORCE_HI; // 5:4    EPWMxA action on DCAEVT1
    pwmRegs->TZCTL.bit.DCAEVT2 = TZ_FORCE_HI; // 7:6    EPWMxA action on DCAEVT2
    pwmRegs->TZCTL.bit.DCBEVT1 = TZ_FORCE_HI; // 9:8    EPWMxB action on DCBEVT1
    pwmRegs->TZCTL.bit.DCBEVT2 = TZ_FORCE_HI; // 11:10  EPWMxB action on DCBEVT2
    // Disable EALLOW
    EDIS;
}

void initPwm(short int prescaler) {
    initPWMChannel(pwm_control_regs[0], prescaler);
    initPWMChannel(pwm_control_regs[1], prescaler);
}

void setPwm(unsigned pwmDutyCycle) {
    EPwm1Regs.CMPA.half.CMPA = pwmDutyCycle;
    EPwm2Regs.CMPA.half.CMPA = pwmDutyCycle;
}

void setADirection(int direct) {
    if (direct == 0) {
        EPwm1Regs.AQCSFRC.bit.CSFA = 1;
        EPwm1Regs.AQCSFRC.bit.CSFB = 1;
    }
    else {
        if (direct > 0) {
            EPwm1Regs.AQCSFRC.bit.CSFA = 0;
            EPwm1Regs.AQCSFRC.bit.CSFB = 1;
        }
        else {
            EPwm1Regs.AQCSFRC.bit.CSFA = 1;
            EPwm1Regs.AQCSFRC.bit.CSFB = 0;
        }
    }
}

void setBDirection(int direct)
{
    if (direct == 0) {
        EPwm2Regs.AQCSFRC.bit.CSFA = 1;
        EPwm2Regs.AQCSFRC.bit.CSFB = 1;
    }
    else {
        if (direct > 0) {
            EPwm2Regs.AQCSFRC.bit.CSFA = 1;
            EPwm2Regs.AQCSFRC.bit.CSFB = 0;
        }
        else {
            EPwm2Regs.AQCSFRC.bit.CSFA = 0;
            EPwm2Regs.AQCSFRC.bit.CSFB = 1;
        }
    }
}

void deactivate_pwm_driver() {
    GpioDataRegs.GPACLEAR.bit.GPIO19 = 1;
    GpioDataRegs.GPBCLEAR.bit.GPIO32 = 1;
}

void activate_pwm_driver() {
    GpioDataRegs.GPASET.bit.GPIO19 = 1;
    GpioDataRegs.GPBSET.bit.GPIO32 = 1;
}

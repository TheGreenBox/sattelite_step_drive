#!/bin/env python
#-*- utf-8 -*-

import sys
import math

from pylab import *

PHASE_L_H   = 1.65E-3
PHASE_R_OHM = 0.77
PWM_P = 12.0
PWM_N = 0.0

PWM_PERIOD = 16.0/6.0E7

PHASE_T_CONST = PHASE_L_H / PHASE_R_OHM

print(PHASE_L_H / PHASE_R_OHM)

SIGMA = PWM_PERIOD/PHASE_T_CONST

def getActive(t, U, I_0):
    I_m = (U/PHASE_R_OHM)
    i_n =   I_m - math.exp(-t/PHASE_T_CONST) * (I_m - I_0) 
    return i_n

pNn = 163 

T_gr = 163*PWM_PERIOD
   
subStepN = 10
fillCoef = 0.1
absc = []
curr = []
curr2 = []
rcurr = []
ccurr = 0

U = PWM_P
pwm_step_I_0 = 0

max_time = 1E-4
step = 1E-10
oldStep = 0
for t in arange(0, max_time, step ):
    absc.append(t)
    eps = divmod(t,PWM_PERIOD)
    if oldStep = 0
    if eps[1] <= fillCoef*PWM_PERIOD:
        if U < PWM_P/2:
            U = PWM_P
            pwm_step_I_0 = ccurr
            
    else:
        if U > PWM_P/2:
            U = 0
            pwm_step_I_0 = ccurr
    
    ccurr = getActive(eps[1], U, pwm_step_I_0)
    curr.append( ccurr )
    i_n = getActive(t, PWM_P, 0)
    rcurr.append( i_n )

U = PWM_P
pwm_step_I_0 = 0
fillCoef = 1
for t in arange(0, max_time, step ):
    eps = divmod(t,PWM_PERIOD)[1]
    if eps <= fillCoef*PWM_PERIOD:
        if U < PWM_P/2:
            U = PWM_P
            pwm_step_I_0 = ccurr
            
    else:
        if U > PWM_P/2:
            U = 0
            pwm_step_I_0 = ccurr
    
    ccurr = getActive(eps, U, pwm_step_I_0)
    curr2.append( ccurr )

plot(absc, curr, 'b')
plot(absc, curr2, 'b')
plot(absc, rcurr, 'r')
plot([T_gr, T_gr], [0, 1], 'g')

xlabel('time (s)')
ylabel('current')
title('Real current in phase')
grid(True)

#savefig("test.png")
show()


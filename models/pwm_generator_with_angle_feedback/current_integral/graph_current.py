#!/bin/env python
#-*- utf-8 -*-

import sys
import math

from pylab import *

PHASE_L_H   = 1.65E-3
PHASE_R_OHM = 0.77
PWM_P = 12.0
PWM_N = 0.0
PWM_PERIOD = 4.0/6.0E7

def getActive(step, varepsilon, fillCoeff):
    #print ( str(varepsilon)+' '+str(math.exp( -getActive.sigma * varepsilon )/ getActive.A2) )
    i_n = getActive.A1                                                                \
            * ( 1.0                                                                   \
                - ( math.exp( -getActive.sigma * varepsilon )/ getActive.A2 )         \
                    * ( 1.0                                                           \
                        - math.exp(-step*getActive.sigma)                             \
                        - math.exp( -(1-fillCoeff) * getActive.sigma )                \
                            * (1.0 - math.exp( (1-step)*getActive.sigma ))            \
                      )                                                               \
              )                                                                       \
          - getActive.A3                                                              \
                * ( math.exp(-getActive.sigma) / getActive.A2 )                       \
                * ( 1.0 - math.exp( (1-step)*getActive.sigma ) )                      \
                * ( 1.0 - math.exp( getActive.sigma * (fillCoeff-1) ) )
    
    return i_n
    
getActive.T = PHASE_L_H / PHASE_R_OHM
getActive.sigma = PWM_PERIOD/getActive.T
getActive.A1 = PWM_P / PHASE_R_OHM
getActive.A2 = 1.0 - math.exp(-getActive.sigma)
getActive.A3 = PWM_N / PHASE_R_OHM 


def getPassive(step, varepsilon, fillCoeff):
    #T = PHASE_L_H / PHASE_R_OHM
    #sigma = T/PWM_PERIOD
    #sigma = 1.0/sigma
    #A1 = ( PWM_P + PWM_N ) / PHASE_R_OHM
    #A2 = math.exp(-sigma)
    #A3 = ( PWM_N / PHASE_R_OHM )
    
#    print( str(varepsilon) \
#           + ' ' + str( math.exp( getPassive.sigma*(fillCoeff-varepsilon) ) ) \
#           + ' ' + str( 1.0 - math.exp(-getPassive.sigma * fillCoeff))                        \
#           + ' ' + str( (1.0 - math.exp(-getPassive.sigma * step)) / getPassive.A2  ) )
            
    i_n = getPassive.A1                                                                         \
            * math.exp( getPassive.sigma*(fillCoeff-varepsilon) )                               \
            * ((1.0 - math.exp(-getPassive.sigma * fillCoeff))                                   \
            * (1.0 - math.exp(-getPassive.sigma * step)) / getPassive.A2 )                     \
          - getPassive.A3                                                                       \
            * ( 1.0 - math.exp( -( step - 1.0 + varepsilon - fillCoeff ) * getPassive.sigma ) )
    
    return i_n

getPassive.T = PHASE_L_H / PHASE_R_OHM
getPassive.sigma = PWM_PERIOD/getPassive.T
getPassive.A1 = ( PWM_P + PWM_N ) / PHASE_R_OHM
getPassive.A2 = 1.0 - math.exp(-getPassive.sigma)
getPassive.A3 = ( PWM_N / PHASE_R_OHM )

#print( getPassive.A2 )
#print( getActive.A2 )

subStepN = 10
fillCoef = 0.15
absc = []
curr = []

for n in range(0, int(3E5), 1):
    for sn in range( subStepN):
        eps = sn/float(subStepN)
        absc.append(n+eps)
        
        if eps <= fillCoef:
            curr.append( getActive(  float(n), eps, fillCoef ) )
        else:
            curr.append( getPassive( float(n), eps, fillCoef ) )

plot(absc, curr)

xlabel('time (s)')
ylabel('current')
title('Real current in phase')
grid(True)

#savefig("test.png")
show()


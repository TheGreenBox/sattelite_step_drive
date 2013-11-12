
import sys

PHASE_L_H   = 1.65 * pow(10, -3)
PHASE_R_OHM = 0.77
PWM_P = 12
PWM_N = 0
PWM_PERIOD = 4./(6.*pow(10,7)

def getActiveCurrent(step, varepsilon, fillCoeff):
    T = PHASE_L_H / PHASE_R_OHM
    sigma = T/PWM_PERIOD
    
    i_n = ( PWM_P / PHASE_R_OHM )                                               \
            * ( 1 - ( math.exp( -sigma * varepsilon )/( 1 - math.exp(-sigma)) ) \
                    * ( (1 - math.exp(-step*sigma) )                            \
                              - math.exp( -(1 - fillCoeff) * sigma )            \
                                    * ( 1 - math.exp(-step*sigma + sigma) )     \
              )       )                                                         \
        - ( PWM_N / PHASE_R_OHM )                                               \
            * ( math.exp(-sigma) )( 1 - math.exp(-sigma) )                      \
            * ( 1 - math.exp( -step * sigma + sigma ) )                         \
            * ( 1 - math.exp( -sigma + sigma * fillCoeff ) )                    \
    
    return i_n

def getPassiveCurrent(step, varepsilon, fillCoeff):
    T = PHASE_L_H / PHASE_R_OHM
    sigma = T/PWM_PERIOD
    
    i_n = ( PWM_P + PWM_N / PHASE_R_OHM )                                       \
            * 1 / ( 1 - math.exp(-sigma) )                                      \
            * (1 - math.exp(-sigma*fillCoeff))                                  \
            * (1 - math.exp(-step*sigma))                                       \
            * math.exp(-sigma*varepsilon + sigma * fillCoeff)                   \
        - ( PWM_N / PHASE_R_OHM )                                               \
            * ( 1 - math.exp( -( step - 1 + varepsilon - fillCoeff ) sigma ) )  \
    
    return i_n
print ( getActiveCurrent( 0, 0.3, fillCoeff=0.5) )
print ( getPassiveCurrent(0, 0.6, fillCoeff=0.5) )

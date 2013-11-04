
import math

_comutationalAngle = 1.5
_stepDeg = 1.8
_stepRad = math.radians(_stepDeg)
_K_T = 2 * 10^(-3)
_N_r = 100

CPU_Freq = 60000000

PWM_freqPrescale = 4  # ?
PWM_Freq = CPU_Freq / PWM_freqPrescale
PWM_Time = 1 / PWM_Freq 

PhaseResistance = 0.77 # Ohms per phase
PhaseInductance = 1.65 * 10^(-3) # Ohms per phase
PhaseElectricalTimeConst = PhaseInductance \ PhaseResistance
RotorInertia = 2.8 * 10^(-5)
LoadInertia   = RotorInertia*2 # fix it
CommonInertia = RotorInertia + LoadInertia 

def getConstPwmByCurrent(curr):
    sigma    = PhaseElectricalTimeConst / PWM_Const
    pwm = 0
    return pwm

def getTorque( dt, dotphi1, dotphi2 ):
    return (dotphi2-dotphi1)*CommonInertia/dt 

def getCurrentByTorque( torq ):
    ###
    # M = K_T * I_m * N_r * (Phi_com - delta/2)
    # M = K_T * I_m * N_r * delta * (Rel_com - 0.5)
    ##
    I_m = torq/( _K_T * _N_r * _stepRad * (_comutationalAngle-0.5) )
    return 0

def pwm_trajectory_generator( dt, phi1, dotphi1, phi2, dotphi2 ):
    torque = getMoment( dt, dotphi1, dotphi2 )
    
    realDt = dt
    pwm = 0.1 # what is index ?
    
    return pwm, realDt


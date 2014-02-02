
import math

_stepDeg = 1.8
_stepRad = math.radians(_stepDeg)
_max_hold_torq = 1.274 # N m
_N_r = 200
_I_max_per_phase = 3.0 # A per phase

##
# Torq = K_t * I * N * (theta2 - theta2)
##
_K_T = _max_hold_torq / (_stepRad * _N_r * _I_max_per_phase)
print( "K_t= "+str(_K_T))

def getCurrentByTorque( torq, comAng ):
    ###
    # M = K_T * I_m * N_r * (Phi_com - delta/2) <=>
    # M = K_T * I_m * N_r * delta * (Rel_com - 0.5)
    ##
    return torq/( _K_T * _N_r * _stepRad * ( comAng-0.5) )

print( getCurrentByTorque( 1.274, 1.5 ) )

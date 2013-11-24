#!/bin/env python
#-*- utf-8 -*-

import sys
import math

from mpl_toolkits.mplot3d import Axes3D
import matplotlib.pyplot as plt
import numpy as np

PHASE_L_H   = 1.65E-3
PHASE_R_OHM = 0.77
PWM_P = 12.0
PWM_N = 0.0
PWM_PERIOD = 4.0/6.0E7
_T = PHASE_L_H / PHASE_R_OHM
sigma = PWM_PERIOD/_T

def yyy(sg, zt):
    return ( math.exp(-sg) * ( (1 - math.exp(-2*sg*zt) ) / (1 - math.exp(-1*sg*zt)) ))

fig = plt.figure()
ax = fig.gca(projection='3d')

#sigma = np.linspace(0., 1., 100)
#zeta  = np.linspace(0., 1., 100)
#h     = np.linspace(0., 1., 100)

sigma = [1, 2, 3]
zeta  = [1, 3, 1]
h     = [3, 2, 2]

ax.plot(sigma, zeta, h);

plt.show()

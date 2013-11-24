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
ax = fig.add_subplot(111, projection='3d')

sigma = np.arange( 40., 45., 0.1 )
zeta  = np.arange( 0.01, 1.,  0.01 )

x, y = np.meshgrid(sigma, zeta) 

zs = np.array( [ yyy(xi,yi) for xi,yi in zip(np.ravel(x), np.ravel(y))] )
z = zs.reshape(x.shape)

#ax.plot_surface( x,y,z, rstride=4, cstride=4 )
ax.plot_wireframe( x,y,z, rstride=4, cstride=4 )

ax.set_xlabel(r'$\sigma$')
ax.set_ylabel(r'$\zeta$')
ax.legend([r"$ e^{-\sigma} \frac{1 - e^{-2 \sigma \zeta}}{1 - e^{ -\sigma \zeta}}$"])
plt.show()


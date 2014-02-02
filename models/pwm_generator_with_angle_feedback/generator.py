#!/bin/env python
#-*- utf-8 -*-

import os
import sys
import pwm_trajectory as pwm

cmdList = ['help', 'test']
cmdHelp = {'help':"Print help", 
           'test':"simple dev test" }

def printHelp():
    print('help me')
    return 0

for arg in sys.argv:
    print (arg)
    
    if arg == 'help' or arg == '--help':
        printHelp()

    elif arg == 'test':
        print(pwm.pwm_trajectory_generator( 1, 1, 1, 2, 2 ))
        
        



#!/bin/bash

if [ -f "$1" ] ; then
    echo "file " "$1" " already exist"
    
else
    touch  "$1"

    
    echo "/* ========================================================"  >> "$1"
    echo " * Organization: The Green Box"                               >> "$1"
    echo " * "                                                          >> "$1"             
    echo " * Project name: Satellite stepper drive"                     >> "$1"            
    echo " * File name: " "$1"                                          >> "$1"
    echo " * Description:"                                              >> "$1"
    echo " * Author: "                                                  >> "$1"
        
    git config --global user.name >> "$1"
    
    echo " * ========================================================"  >> "$1"
    echo " */" >> "$1"
fi 

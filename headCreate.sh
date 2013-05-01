#!/bin/bash

if [ -f "$1" ] ; then
    echo "file " "$1" " already exist"
else
   touch  "$1"
fi 

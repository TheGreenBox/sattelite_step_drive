#!/bin/bash

userName=$(git config --global user.name)

header=$(echo "/* ========================================================\n"\
" * Organization: The Green Box\n"\
" * \n"\
" * Project name: Satellite stepper drive\n"\
" * File name: " "$1" "\n"\
" * Description:\n"\
" * Author: " "$userName" "\n"\
" * ========================================================\n"\
" */\n")

if [ -f "$1" ] ; then
    echo "file " "$1" " already exist"
    
    rez=$(grep -c "Organization: The Green Box" "$1")
    
    if [ $rez != 0 ]; then
        echo "find correct header -- > exit"
    else
        echo "not find correct header -- > add.."
        touch ".tempFile"
        mv "$1" ".tempFile"
        echo "$header" >> "$1"
        cat ".tempFile" >> "$1"
        rm ".tempFile"
    fi 
else
    touch  "$1"
    echo "$header" >> "$1"
fi 


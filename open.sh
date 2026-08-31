#!/bin/bash

# PCANNON OPEN.SH v1.0S - FROM PCANNON PROJECT STANDARDS
# STANDARD: 20251212
# FROM STD: 20250608
# https://github.com/pcannon09/pcannonProjectStandards

defaultEdit="$1" # Set the default editor in parameter $1 (such as: code, vim, nvim, ...)

if [ "$1" == "" ]; then
	defaultEdit="nvim"
fi

$defaultEdit src/main.cpp $(find src/ inc/ -type f) CMakeLists.txt


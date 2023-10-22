#!/bin/bash

# set -xe

if [ -z "$1" ]; then
    echo "No filename provided! How could you do that?"
elif [ -f "$1.c" ]; then
    # fl prefix is usef for quickly launching it in the command line
    # You may change it if you want. I don't have control over you
    echo "- [INFO]: building '$1.c' file into 'fl_$1.out'."
    clang -Wall -Wextra -pedantic -std=c99 -o "fl_$1.out" "$1.c" -lm -lc
else
    echo "[ERROR]: File '$1.c' doesn't exist. Dude go make it."
fi
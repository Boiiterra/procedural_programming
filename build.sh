#!/bin/bash

# set -xe

if [ -z "$1" ]; then
    echo "- [ERROR]: No filename provided! How could you do that?"
elif [ -f "$1" ]; then
    # fl prefix is usef for quickly launching it in the command line
    # You may change it if you want. I don't have control over you
    echo "  - [INFO]: building '$1' file into 'fl_exec.out'."
    clang -Wall -Wextra -pedantic -std=c99 -O3 -o "fl_exec.out" "$1" -lm -lc
else
    echo "- [ERROR]: File '$1' doesn't exist. Dude go make it."
fi

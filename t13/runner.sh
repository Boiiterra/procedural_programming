#!/bin/bash

set -e

i="- [INFO]:"

if [ -f "./sorted.txt" ]; then
    echo "$i Removing previous results of sorting."
    rm ./sorted.txt
fi

echo "$i Building C file."
./build th
echo "$i Build successful."

if [ -z "$1" ]; then
    echo "$i Generating file to sort with Python script."
    python ./gen.py
else
    if [ "$1" == "old" ]; then
        echo "$i No new file is going to be generated. Sorting old file again."
    else
        echo "$i Generating file to sort with Python script."
        python ./gen.py
        echo "$i If you want to sort old file use: $0 old"
    fi

fi

echo "$i Preparations done."
echo "$i Running main executable."
# time ./fl_exec.out
./fl_exec.out

echo "$i Running Python check script to check if file was sorted correctly."
python ./see.py

if [ $# -eq 0 ]; then
    echo "$i No extra arguments supplied running normally."
else
    if [ $# -eq 2 ]; then
        if [ "$2" == "bonus" ]; then
            echo "$i bonus found."
            python ./see.py 10m
        else
            echo "$i Extra argument is supplied. If you want to see bonus do: $0 $1 bonus"
        fi
    else
        if [ "$1" == "bonus" ]; then
            echo "$i bonus found."
            python ./see.py 10m
        elif [ "$1" == "old" ]; then
            echo "$i Extra argument is supplied. If you want to see bonus do: $0 $1 bonus"
        else
            echo "$i Extra argument is supplied. If you want to see bonus do: $0 bonus"
        fi
    fi
fi

echo "$i Status success. All jobs finished!"

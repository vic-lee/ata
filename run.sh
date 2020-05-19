#!/bin/bash

doc="                                                                       
Usage: ./run.sh <dir> <exec-name>                       

Where:                                                                      
    <dir> is:           a relative or absolute path to your program
    <exec-name> is:     optional argument specifying your executable name.
                        Default to 'main' if not specified.

The script expects a program directory following the structure below:
    <dir>
    ├── <exec-name>
    └── tests
        ├── 1
        │   ├── input
        │   └── output
        ├── 2
        │   ├── input
        │   └── output
        └── ...

Sample usage:
    $ ./run.sh hw/hw1/1_add
    $ ./run.sh hw/hw1/1_add Add
"

if [[ ! -e "$1" ]]; then
    echo "$doc" 1>&2
    exit 1
fi

if [[ ! $2 -eq 0 ]]; then
    exec=$2
else
    exec="main"
    if [[ ! -e $1/main ]]; then # attempt to compile if main.cpp is not compiled
        echo "Compiling $1/main.cpp..."
        g++ -std=c++17 $1/main.cpp -o $1/main
    fi
fi

if [[ ! -e $1/$exec ]]; then
    echo "executable '$exec' does not exist in $1. Exiting..." 1>&2
    exit 1
fi

echo "Using binary '$exec' to run tests in $1/tests"

for d in $1/tests/*; do
    diff <($1/$exec <"$d/input") "$d/output" &&
        echo -e "$d \\tpassed" ||
        echo -e "!!! $d \\tfailed !!!\n"
done

#!/bin/bash

# Declare arguments as variables
DIRECTORY=$1
TESTCASE=$2

make clean
make bin/c_compiler

mkdir -p test_output
mkdir -p test_output/source
mkdir -p test_output/object
mkdir -p test_output/exe

# Check if a directory was passed
if [ -z "$1" ]
then
    # Run every testcase
    DIRECTORIES="compiler_tests/*"
    for d in $DIRECTORIES ; do
        if [ -d "$d" ]
        then
            # Get all testcases in directory
            TESTCASES=$d"/*_driver.c"
            d=${d#"compiler_tests/"}
            # Extract each test name and run each test
            for i in ${TESTCASES} ; do
                TESTNAME=${i%"_driver.c"}
                TESTNAME=${TESTNAME#"compiler_tests/$d/"}
                ./run_single_testcase.sh $d $TESTNAME
            done
        fi
    done
else
    # Check if a testcase was passed
    if [ -z "$2" ]
    then
        # Get all testcases in directory
        TESTCASES="compiler_tests/"$DIRECTORY"/*_driver.c"
        # Extract each test name and run each test
        for i in ${TESTCASES} ; do
            PREFIX="compiler_tests/$DIRECTORY/"
            SUFFIX="_driver.c"
            TESTNAME=${i%$SUFFIX}
            TESTNAME=${TESTNAME#$PREFIX}
            ./run_single_testcase.sh $DIRECTORY $TESTNAME
        done
    else
        # Run testcase (dispatched to single script)
        ./run_single_testcase.sh $DIRECTORY $TESTCASE
    fi
fi

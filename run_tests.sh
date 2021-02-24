#!/bin/bash

# Declare arguments as variables
DIRECTORY = $1
TESTCASE = $2

make bin/c_compiler

# Check if a directory was passed
if [ -z "$DIRECTORY"]
then
    # Check if a testcase was passed
    if [ -z "$TESTCASE"]
    then
        # Run testcase (dispatched to single script)
        ./run_single_testcase "$DIRECTORY" "$TESTCASE"
    else
        # Get all testcases in directory
        TESTCASES = "compiler_tests/"$DIRECTORY"/*_driver.c"
        # Extract each test name and run each test
        for i in ${TESTCASES} ; do
            TESTNAME = ${"$i"%"_driver.c"}
            ./run_single_testcase "$DIRECTORY" "$TESTNAME"
        done
    fi
else
    # Run every testcase
    DIRECTORIES="compiler_tests/*"
    for d in $DIRECTORIES ; do
        if [-d "$d"]
        then
            # Get all testcases in directory
            TESTCASES = "compiler_tests/"$d"/*_driver.c"
            # Extract each test name and run each test
            for i in ${TESTCASES} ; do
                TESTNAME = ${"$i"%"_driver.c"}
                ./run_single_testcase "$d" "$TESTNAME"
            done
        fi
    done
fi
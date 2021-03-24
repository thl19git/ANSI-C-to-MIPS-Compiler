#!/bin/bash

make clean

make bin/c_compiler

mkdir -p custom_test_output
mkdir -p custom_test_output/source
mkdir -p custom_test_output/object
mkdir -p custom_test_output/exe

TESTS="simple_tests/*_driver.c"

for test in ${TESTS} ; do
    PREFIX="simple_tests/"
    SUFFIX="_driver.c"
    TESTNAME=${test%$SUFFIX}
    TESTNAME=${TESTNAME#$PREFIX}

    ./run_custom_testcase.sh $TESTNAME

done
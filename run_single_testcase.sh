#!/bin/bash

# Declare arguments as variables
DIRECTORY=$1
TESTCASE=$2

set +e

bin/c_compiler -S compiler_tests/$DIRECTORY/$TESTCASE".c" -o test_output/source/$TESTCASE.s

RESULT=$?
set -e

if [[ "${RESULT}" -ne 0 ]] ; then
   echo "compiler_tests/$DIRECTORY/$TESTCASE, unable to compile"
   exit
fi

set +e

mips-linux-gnu-gcc -mfp32 -o test_output/object/$TESTCASE.o -c test_output/source/$TESTCASE.s

RESULT=$?
set -e

if [[ "${RESULT}" -ne 0 ]] ; then
   echo "${TESTCASE}, unable to assemble"
   exit
fi

set +e 

mips-linux-gnu-gcc -mfp32 -static -o test_output/exe/$TESTCASE test_output/object/$TESTCASE.o compiler_tests/$DIRECTORY/$TESTCASE"_driver".c

RESULT=$?
set -e

if [[ "${RESULT}" -ne 0 ]] ; then
   echo "${TESTCASE}, unable to link to driver program"
   exit
fi

set +e

qemu-mips test_output/exe/$TESTCASE

RESULT=$?
set -e

if [[ "${RESULT}" -ne 0 ]] ; then
   echo "${TESTCASE}, Fail"
   exit
else
    echo "$TESTCASE, Pass"
fi
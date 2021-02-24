#!/bin/bash

# Declare arguments as variables
DIRECTORY = $1
TESTCASE = $2

set +e

bin/c_compiler -S "$TESTCASE.c" -o "$TESTCASE.s"

RESULT=$?
set -e

if [[ "${RESULT}" -ne 0 ]] ; then
   echo "${TESTCASE}, unable to compile"
   exit
fi

set +e

mips-linux-gnu-gcc -mfp32 -o "$TESTCASE.o" -c "$TESTCASE.s"

RESULT=$?
set -e

if [[ "${RESULT}" -ne 0 ]] ; then
   echo "${TESTCASE}, unable to assemble"
   exit
fi

set +e 

mips-linux-gnu-gcc -mfp32 -static -o "$TESTCASE" "$TESTCASE.o" ""$TESTCASE"_driver.c"

RESULT=$?
set -e

if [[ "${RESULT}" -ne 0 ]] ; then
   echo "${TESTCASE}, unable to link to driver program"
   exit
fi

set +e

qemu-mips "$TESTCASE"

RESULT=$?
set -e

if [[ "${RESULT}" -ne 0 ]] ; then
   echo "${TESTCASE}, Fail"
   exit
else
    echo "$TESTCASE, Pass"
fi
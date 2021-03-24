TESTCASE=$1

set +e

bin/c_compiler -S simple_tests/$TESTCASE".c" -o custom_test_output/source/$TESTCASE.s

RESULT=$?
set -e

if [[ "${RESULT}" -ne 0 ]] ; then
   echo "simple_tests/$TESTCASE.c, unable to compile"
   exit
fi

set +e

mips-linux-gnu-gcc -mfp32 -o custom_test_output/object/$TESTCASE.o -c custom_test_output/source/$TESTCASE.s

RESULT=$?
set -e

if [[ "${RESULT}" -ne 0 ]] ; then
   echo "${TESTCASE}, unable to assemble"
   exit
fi

set +e 

mips-linux-gnu-gcc -mfp32 -static -o custom_test_output/exe/$TESTCASE custom_test_output/object/$TESTCASE.o simple_tests/$TESTCASE"_driver".c

RESULT=$?
set -e

if [[ "${RESULT}" -ne 0 ]] ; then
   echo "${TESTCASE}, unable to link to driver program"
   exit
fi

set +e

qemu-mips custom_test_output/exe/$TESTCASE

RESULT=$?
set -e

if [[ "${RESULT}" -ne 0 ]] ; then
   echo "${TESTCASE}, Fail"
   exit
else
    echo "$TESTCASE, Pass"
fi
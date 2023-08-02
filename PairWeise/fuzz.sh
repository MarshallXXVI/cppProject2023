#!/bin/bash

FUZZER=./crippled-fuzzer
SOLVER=./solverMain
# CHECKER=./russian-roulette-checker
CHECKER=./checkerMain

if [ -x $FUZZER ];
then
    echo "found fuzzer"
else
    echo "the fuzzer was not found"
    exit 1
fi


if [ -x $SOLVER ];
then
    echo "found solver"
else
    echo "the solver was not found"
    exit 1
fi



if [ -x $CHECKER ];
then
    echo "found checker"
else
    echo "the checker was not found"
    exit 1
fi

echo "starting the tests"

i=0
while [ true ];
do
    echo "*******************************************"
    echo "************* TEST $i    ******************"
    i=$((i+1))
    $FUZZER fuzzer-test.{options,constraints}
    $SOLVER fuzzer-test.{options,constraints,models}
    $CHECKER fuzzer-test.{options,constraints,models}
    status=$?
    echo "$status"
    if [ "$status" -ne 40 -a "$status" -ne 0 ];
    then
	echo "the checking failed on fuzzer-test.{options,constraints,models}"
	exit -1;
    fi;
done
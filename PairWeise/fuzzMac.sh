#!/bin/bash

FUZZER=./crippled-fuzzerMac
SOLVER=./solverMain
CHECKER=./russian-roulette-checkerMac

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
    status=$?
    if [ "$status" -ne 0 ];
    then
    echo "the fuzzer failed on"
    exit -1;
    fi;

    $SOLVER fuzzer-test.{options,constraints,models}
    status=$?
    if [ "$status" -ne 0 ];
    then
    echo "the solver failed on fuzzer-test.{options,constraints,models}"
    exit -1;
    fi;

    $CHECKER fuzzer-test.{options,constraints,models}
    status=$?
    if [ "$status" -ne 40 -a "$status" -ne 0 ];
    then
    echo "the checker failed on fuzzer-test.{options,constraints,models}"
    exit -1;
    fi;
done
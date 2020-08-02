#!/bin/bash

core_count=8
buildScript=build.sh
currentDir=$PWD
export ASAN_OPTIONS=detect_container_overflow=0

function echoColor
{
    echo -e "\033[1;$1m$2\033[0m"
}

function checkReturn()
{
    returnCode=$?
    if [ ! $returnCode -eq 0 ]
    then
        echoColor 31 "Check failed. Return code: $returnCode"
        exit 1
    fi
}

function build()
{
    echoColor 32 "Building $1."
    ./$buildScript $1 $currentDir/build-$1 $core_count
    checkReturn
    cd $currentDir
    echo ""
}

function runTests()
{
    echoColor 32 "Running tests in build-$1."
    cd build-$1
    ./SCCompilerApp
    checkReturn
    ./SCCompilerTestApp
    checkReturn
    cd $currentDir
    echo ""
}

# Build all binaries
build debug
build release
build asan
build tsan

# Run tests
runTests debug
runTests release
runTests asan
runTests tsan

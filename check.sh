#!/bin/bash

buildScript=build.sh
currentDir=$PWD
export ASAN_OPTIONS=detect_container_overflow=0

# Define osType
unameOut="$(uname -s)"
case "${unameOut}" in
    Linux*)     os_type=Linux;;
    Darwin*)    os_type=Mac;;
    CYGWIN*)    os_type=Win;;
    MINGW*)     os_type=Win;;
    *)          os_type="UNKNOWN:${unameOut}"
esac

if [ $os_type == "Mac" ]; then
    logical_core_count=`sysctl -n hw.ncpu`
else
    logical_core_count=`nproc --all`
fi


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
    echoColor 32 "Building $1 in build-$1 folder."
    ./$buildScript $1 build-$1 $currentDir/build-$1-product $logical_core_count      ;checkReturn
    cd $currentDir
    echo ""
}

function runTests()
{
    echoColor 32 "Running tests in build-$1-product."
    cd build-$1-product
    ./SCCompilerApp       ;checkReturn
    ./SCCompilerTestApp   ;checkReturn
    cd $currentDir
    echo ""
}

function reportCodeCoverage()
{
    echoColor 32 "Running code coverage in build-$1-product."
    cd build-$1-product
    rm -rf *.profraw
    rm -rf *.prodata
    # TODO: Linux and Windows needs to be supported.
    LLVM_PROFDATA_EXEC=`xcrun -find llvm-profdata`                      ;checkReturn
    LLVM_COV_EXEC=`xcrun -find llvm-cov`                                ;checkReturn
    LLVM_PROFILE_FILE="$2.profraw" ./$2                                 ;checkReturn
    $LLVM_PROFDATA_EXEC merge -sparse $2.profraw -o default.profdata    ;checkReturn
    $LLVM_COV_EXEC show ./$2 -instr-profile=default.profdata -ignore-filename-regex=Externals/* -format=html -tab-size=4 >> DetailedCodeCoverageReport.html ;checkReturn
    $LLVM_COV_EXEC report ./$2 -instr-profile=default.profdata -ignore-filename-regex=Externals/*  ;checkReturn
    cd $currentDir
    echo ""
}

# Build all binaries
build debug
build release
build asan
build tsan
build ccov

# Run tests
runTests debug
runTests release
runTests asan
runTests tsan

# Report test code coverage
reportCodeCoverage ccov SCCompilerTestApp

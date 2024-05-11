#!/bin/bash
#
#  Copyright © 2018-Present, Arkin Terli. All rights reserved.
#

# The following line requires for macOS, otherwise configure application fails to find grep.
export GREP_OPTIONS="--color=auto"

function showHelp()
{
    echo ""
    echo "Usage:"
    echo "    ./build.sh <build_type> <build_dir> <install_dir> <cpu_cores> [<build_options>...]"
    echo ""
    echo "Example:"
    echo "    ./build.sh release build-rel \$(pwd)/product-rel 8"
    echo ""
    echo "Options:"
    echo "    build_type       Valid build types: release, debug, ccov, asan, tsan"
    echo "    build_dir        CMake build directory."
    echo "    install_dir      Product installation full directory path."
    echo "    cpu_cores        Number of CPU cores to use."
    echo "    build_options    CMake build options. Can be multiple. i.e. -DLOG_ENABLE=1"
    echo ""
}

function checkBuildType()
{
    arr=("release" "debug" "ccov" "asan" "tsan")
    build_type="$(tr [A-Z] [a-z] <<< "$1")"   # to lower-case.
    # if build type is not valid then exit.
    if [[ ! " ${arr[*]} " == *" ${build_type} "* ]]; then
        echo "Error: Invalid build type: ${type}"
        exit 1
    fi
}

function main()
{
    checkBuildType $1
    pushd .
    rm -rf $2 $3
    mkdir $2
    cd $2

    cmake .. -DCMAKE_BUILD_TYPE=$1 -DSCCOMPILER_BUILD_TESTS=ON -DSCCOMPILER_BUILD_EXAMPLES=ON  \
             -DCMAKE_INSTALL_PREFIX=$3 $5 $6 $7 $8 $9 ${10} ${11} ${12} ${13} ${14} ${15}
    cmake --build . --target all -- -j $4
    cmake --build . --target install -- -j $4

    popd
}

if [ "$#" -ge 4 ]; then
    main "$@"  # Pass all parameters
else
    showHelp
fi

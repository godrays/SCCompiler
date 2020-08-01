#!/bin/bash

# The following line requires for macOS, otherwise configure application fails to find grep.
export GREP_OPTIONS="--color=auto"

function showHelp()
{
    echo ""
    echo "Usage:"
    echo "    ./build.sh <build_type> <install_dir> <cpu_cores> [<build_options>...]"
    echo ""
    echo "Example:"
    echo "    ./build.sh release \$(pwd)/build-release 8"
    echo ""
    echo "Options:"
    echo "    build_type       Valid build types: release, debug, ccov, asan, tsan"
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
    rm -rf build
    mkdir build
    cd build

    cmake .. -DCMAKE_BUILD_TYPE=$1 -DCMAKE_INSTALL_PREFIX=$2 $4 $5 $6 $7 $8 $9 ${10} ${11} ${12} ${13} ${14} ${15}
    cmake --build . --target all -- -j $3
    cmake --build . --target install -- -j $3

    popd
}

if [ "$#" -ge 3 ]; then
    main "$@"  # Pass all parameters
else
    showHelp
fi

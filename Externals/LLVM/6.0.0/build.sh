#!/bin/bash

# The following line requires for macOS, otherwise configure application fails to find grep.
export GREP_OPTIONS="--color=auto"

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

pushd .
rm -rf build
mkdir build
cd build

# Supported build types Debug, Release, RelWithDebInfo, and MinSizeRel
cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=../installed
cmake --build . --target install -- -j $logical_core_count

popd

rm -rf build

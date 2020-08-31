#!/bin/bash

# The following line requires for macOS, otherwise configure application fails to find grep.
export GREP_OPTIONS="--color=auto"

pushd .
rm -rf build
mkdir build
cd build

# Supported build types Debug, Release, RelWithDebInfo, and MinSizeRel
cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=../installed
cmake --build . --target install -- -j 8

popd

rm -rf build

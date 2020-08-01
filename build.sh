#!/bin/bash

# The following line requires for macOS, otherwise configure application fails to find grep.
export GREP_OPTIONS="--color=auto"

rm -rf build
mkdir build
cd build

cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=Deployed
cmake --build . --target all -- -j 8

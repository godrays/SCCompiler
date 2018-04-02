#!/bin/bash

# The following line requires for macOS, otherwise configure application fails to find grep.
export GREP_OPTIONS="--color=auto"

rm -rf $PWD/build/xcode
make clean
./configure --prefix=$PWD/build/xcode --disable-shared
make
make install

# Clean intermediate build files.
make clean

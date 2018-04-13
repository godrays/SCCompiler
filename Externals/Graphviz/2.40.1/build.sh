#!/bin/bash

# The following line requires for macOS, otherwise configure application fails to find grep.
export GREP_OPTIONS="--color=auto"

rm -rf $PWD/build
make clean
./configure --prefix=$PWD/build --disable-shared --enable-static
make -j 8
cd cmd/dot
make dot
make install

# Clean intermediate build files.
make clean


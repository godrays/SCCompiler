#!/bin/bash

# The following line requires for macOS, otherwise configure application fails to find grep.
export GREP_OPTIONS="--color=auto"

rm -rf $PWD/installed
./configure --prefix=$PWD/installed --disable-shared --enable-static
make -j 8

make install

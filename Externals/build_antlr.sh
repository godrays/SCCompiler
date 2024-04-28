#!/bin/bash

#
#  Copyright (c) 2024-Present, Arkin Terli. All rights reserved.
#

lib_name=antlr
lib_version=4.7.1
lib_url=https://github.com/antlr/antlr4.git
logical_core_count=$(nproc 2>/dev/null || sysctl -n hw.logicalcpu)

pushd .

rm -rf $lib_name/$lib_version

git clone --recurse-submodules -b $lib_version $lib_url ./$lib_name/$lib_version
cd $lib_name/$lib_version/runtime/Cpp

rm -rf build
mkdir build
cd build

cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=../installed
cmake --build . --target install -- -j $logical_core_count

cd ..
rm -rf build

# Rename the static file to force linker to select the static lib file.
mv installed/lib/libantlr4-runtime.a installed/lib/libantlr4-runtime_s.a

popd

mkdir -p $lib_name/$lib_version/bin
curl https://www.antlr.org/download/antlr-$lib_version-complete.jar -o $lib_name/$lib_version/bin/antlr-$lib_version-complete.jar

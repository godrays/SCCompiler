#!/bin/bash

#
#  Copyright (c) 2023-Present, Arkin Terli. All rights reserved.
#

lib_name=catch2
lib_version=2.12.4
lib_url=https://github.com/catchorg/Catch2.git
logical_core_count=$(if [[ $(uname) == "Darwin" ]]; then sysctl -n hw.ncpu; else nproc --all; fi)

pushd .

rm -rf $lib_name

git clone --recurse-submodules -b v$lib_version $lib_url ./$lib_name/$lib_version
cd $lib_name/$lib_version

rm -rf build
mkdir build
cd build


cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=../installed -DCATCH_BUILD_TESTING=OFF
cmake --build . --target install -- -j $logical_core_count
echo $num_cores
cd ..
rm -rf .git .gitattributes .github .gitignore build

popd

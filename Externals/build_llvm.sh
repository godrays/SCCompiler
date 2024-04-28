#!/bin/bash

#
#  Copyright (c) 2024-Present, Arkin Terli. All rights reserved.
#

lib_name=llvm
lib_version=12.0.1
lib_file=llvm-project-$lib_version.src.tar.xz
lib_url=https://github.com/llvm/llvm-project/releases/download/llvmorg-$lib_version/$lib_file
logical_core_count=$(nproc 2>/dev/null || sysctl -n hw.logicalcpu)

pushd .

# If the directory is NOT exist then download and build it.
if [ ! -d "$lib_name/$lib_version/llvm" ]; then
    mkdir -p $lib_name/$lib_version
    cd $lib_name/$lib_version
    curl -L $lib_url --output $lib_file
    tar -xf $lib_file --strip-components=1
    rm -rf $lib_file
else
    cd $lib_name/$lib_version
fi

cd llvm

pushd .

rm -rf build
mkdir build
cd build

cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=../installed -DLLVM_TARGETS_TO_BUILD="AArch64;ARM;X86" -DLLVM_DEFAULT_TARGET_TRIPLE="host" -DLLVM_INCLUDE_TESTS=OFF -DLLVM_INCLUDE_BENCHMARKS=OFF -DLLVM_ENABLE_ZSTD=OFF
cmake --build . --target install -- -j $logical_core_count

popd

rm -rf .git .gitattributes .github .gitignore build

popd

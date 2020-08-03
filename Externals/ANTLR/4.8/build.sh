#!/bin/bash

mkdir -p tool
curl https://www.antlr.org/download/antlr-4.8-complete.jar -o tool/antlr-4.8-complete.jar

pushd .
rm -rf build installed dist
mkdir build
cd build

cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=../installed
cmake --build . --target all -- -j 8
cmake --build . --target install -- -j 8

popd

rm -rf dist
rm -rf build

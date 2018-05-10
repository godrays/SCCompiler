#!/bin/bash

rm -rf ./build

mkdir build
cd build
cmake ..
cmake --build .
cmake -DCMAKE_INSTALL_PREFIX=../installed -P cmake_install.cmake
cd ..


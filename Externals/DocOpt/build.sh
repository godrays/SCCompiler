#!/bin/bash

rm -rf ./build
rm -rf ./CMakeFiles

rm CMakeCache.txt
rm CPackConfig.cmake
rm CPackSourceConfig.cmake
rm Makefile
rm cmake_install.cmake

cmake CMakeLists.txt
make
rm -rf ./CMakeFiles
mkdir build
mv libdocopt*.* build

rm CMakeCache.txt
rm CPackConfig.cmake
rm CPackSourceConfig.cmake
rm Makefile
rm cmake_install.cmake

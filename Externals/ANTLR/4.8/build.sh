#!/bin/bash

# Define osType
unameOut="$(uname -s)"
case "${unameOut}" in
    Linux*)     os_type=Linux;;
    Darwin*)    os_type=Mac;;
    CYGWIN*)    os_type=Win;;
    MINGW*)     os_type=Win;;
    *)          os_type="UNKNOWN:${unameOut}"
esac

if [ $os_type == "Mac" ]; then
    logical_core_count=`sysctl -n hw.ncpu`
else
    logical_core_count=`nproc --all`
fi


mkdir -p tool
curl https://www.antlr.org/download/antlr-4.8-complete.jar -o tool/antlr-4.8-complete.jar

pushd .
rm -rf build installed dist
mkdir build
cd build

cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=../installed
cmake --build . --target all -- -j $logical_core_count
cmake --build . --target install -- -j $logical_core_count

popd

rm -rf dist
rm -rf build

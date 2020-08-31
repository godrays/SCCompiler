#!/bin/bash

# Enters a specific library folder and runs build.sh file.
function BuildExternalLib()
{
    pushd .
    cd $1
    ./build.sh
    popd
}

BuildExternalLib "ANTLR/4.8"
BuildExternalLib "LLVM/6.0.0"

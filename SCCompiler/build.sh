#!/bin/bash

# Build Debug binaries.
xcodebuild -configuration Debug -alltargets -parallelizeTargets || exit $?

# Build Release binaries.
xcodebuild -configuration Release -alltargets -parallelizeTargets || exit $?


#
#  Copyright © 2018-Present, Arkin Terli. All rights reserved.
#

cmake_minimum_required(VERSION 3.24)

project(SCCompiler)

# Set default build options

option(SCCOMPILER_BUILD_TESTS    "Build SCCompiler test application"     OFF)
option(SCCOMPILER_BUILD_EXAMPLES "Build SCCompiler example applications" OFF)
option(SCCOMPILER_BUILD_STATIC   "Build static SCCompilerLib library"    OFF)

# Set compiler configurations.

set(CMAKE_CONFIGURATION_TYPES "Debug;Release;CCov;ASan;TSan" CACHE STRING "" FORCE)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_INSTALL_RPATH .)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic-errors -Wall -Wextra -Wno-unused-parameter -Wno-unused-but-set-variable -Wno-integer-overflow")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-deprecated-declarations -Wno-bitwise-instead-of-logical -Wno-return-type")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")
set(CMAKE_CXX_FLAGS_CCOV "${CMAKE_CXX_FLAGS} -fprofile-instr-generate -fcoverage-mapping")
set(CMAKE_CXX_FLAGS_ASAN "${CMAKE_CXX_FLAGS} -g -O1 -fsanitize=address -fno-omit-frame-pointer")
set(CMAKE_CXX_FLAGS_TSAN "${CMAKE_CXX_FLAGS} -g -O2 -fsanitize=thread -fPIE")

# Set external lib versions.
set(EXTERNAL_ANTLR4_VERSION 4.13.1)
set(EXTERNAL_CATCH2_VERSION v2.12.4)
set(EXTERNAL_LLVM_VERSION   llvmorg-12.0.1)
include(Externals/Externals.cmake)

# Add include folders.
include_directories(Targets/SCCompilerLib)

# Add targets to build and install.
add_subdirectory(Targets/SCCompilerLib)

if (SCCOMPILER_BUILD_TESTS)
    add_subdirectory(Targets/SCCompilerTests)
endif ()

if (SCCOMPILER_BUILD_EXAMPLES)
    add_subdirectory(Targets/SCCompilerExamples/SCCompilerApp)
endif ()

if (NOT SCCOMPILER_BUILD_STATIC AND (SCCOMPILER_BUILD_TESTS OR SCCOMPILER_BUILD_EXAMPLES))
    install(TARGETS SCCompilerLib DESTINATION ${CMAKE_INSTALL_PREFIX})
endif ()

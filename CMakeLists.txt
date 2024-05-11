cmake_minimum_required(VERSION 3.24)

project(SCCompiler)

# Set default build options

option(SCCOMPILER_BUILD_TESTS    "Build SCCompiler test application"     OFF)
option(SCCOMPILER_BUILD_EXAMPLES "Build SCCompiler example applications" OFF)

# Set compiler configurations

set(CMAKE_CONFIGURATION_TYPES "Debug;Release;CCov;ASan;TSan" CACHE STRING "" FORCE)
set(CMAKE_CXX_STANDARD 20)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic-errors -Wall -Wextra -Wno-unused-parameter -Wno-unused-but-set-variable")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-deprecated-declarations -Wno-bitwise-instead-of-logical -Wno-return-type")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")
set(CMAKE_CXX_FLAGS_CCOV "${CMAKE_CXX_FLAGS} -fprofile-instr-generate -fcoverage-mapping")
set(CMAKE_CXX_FLAGS_ASAN "${CMAKE_CXX_FLAGS} -g -O1 -fsanitize=address -fno-omit-frame-pointer")
set(CMAKE_CXX_FLAGS_TSAN "${CMAKE_CXX_FLAGS} -g -O2 -fsanitize=thread -fPIE")

# Set include and lib directories

set(CATCH2_VERSION 2.12.4)
set(ANTLR_VERSION 4.13.1)
set(LLVM_VERSION 12.0.1)

include_directories(Targets/SCCompilerLib)
include_directories(Externals/catch2/${CATCH2_VERSION}/single_include)
include_directories(Externals/antlr/${ANTLR_VERSION}/runtime/Cpp/installed/include/antlr4-runtime)
include_directories(Externals/llvm/${LLVM_VERSION}/llvm/installed/include)

link_directories(Externals/antlr/${ANTLR_VERSION}/runtime/Cpp/installed/lib)
link_directories(Externals/llvm/${LLVM_VERSION}/llvm/installed/lib)

# Add targets to build and install

add_subdirectory(Targets/SCCompilerLib)

if (SCCOMPILER_BUILD_TESTS)
    add_subdirectory(Targets/SCCompilerTests)
endif ()

if (SCCOMPILER_BUILD_EXAMPLES)
    add_subdirectory(Targets/SCCompilerExamples/SCCompilerApp)
endif ()

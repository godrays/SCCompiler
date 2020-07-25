cmake_minimum_required(VERSION 3.10)

project(SCCompiler)

# Set default duild type as Release
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -pedantic-errors -flto -Wall -Wextra")

include_directories(Targets/SCCompilerLib)
include_directories(Externals/catch2/single_include/catch2)
include_directories(Externals/ANTLR/4.7.1/Runtime/antlr4-runtime)
include_directories(Externals/LLVM/6.0.0/installed/include)

link_directories(Externals/ANTLR/4.7.1/Runtime/lib)
link_directories(Externals/LLVM/6.0.0/installed/lib)

add_subdirectory(Targets/SCCompilerLib)
add_subdirectory(Targets/SCCompilerApp)
add_subdirectory(Targets/SCCompilerTestApp)

cmake_minimum_required(VERSION 3.24)

project(SCCompiler)

set(CMAKE_CONFIGURATION_TYPES "Debug;Release;CCov;ASan;TSan" CACHE STRING "" FORCE)

set(CMAKE_CXX_STANDARD 20)

# Set default build type as Release
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

set(CATCH2_VERSION 2.12.4)
set(ANTLR_VERSION 4.13.1)
set(LLVM_VERSION 12.0.1)

include_directories(Targets/SCCompilerLib)
include_directories(Externals/catch2/${CATCH2_VERSION}/single_include)
include_directories(Externals/antlr/${ANTLR_VERSION}/runtime/Cpp/installed/include/antlr4-runtime)
include_directories(Externals/llvm/${LLVM_VERSION}/llvm/installed/include)

link_directories(Externals/antlr/${ANTLR_VERSION}/runtime/Cpp/installed/lib)
link_directories(Externals/llvm/${LLVM_VERSION}/llvm/installed/lib)

add_subdirectory(Targets/SCCompilerLib)
add_subdirectory(Targets/SCCompilerTests)
add_subdirectory(Targets/SCCompilerExamples/SCCompilerApp)

install(TARGETS SCCompilerApp SCCompilerTests DESTINATION ${CMAKE_INSTALL_PREFIX})
install(FILES Targets/SCCompilerExamples/SCCompilerApp/SCCompilerTestCode.src DESTINATION ${CMAKE_INSTALL_PREFIX})

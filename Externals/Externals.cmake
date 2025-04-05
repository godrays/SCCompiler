#
#  Copyright © 2024-Present, Arkin Terli. All rights reserved.
#
#  NOTICE:  All information contained herein is, and remains the property of Arkin Terli.
#  The intellectual and technical concepts contained herein are proprietary to Arkin Terli
#  and may be covered by U.S. and Foreign Patents, patents in process, and are protected by
#  trade secret or copyright law. Dissemination of this information or reproduction of this
#  material is strictly forbidden unless prior written permission is obtained from Arkin Terli.

include(ExternalProject)

# ---------------------------------------------------------------------------------
# HELPER FUNCTIONS
# ---------------------------------------------------------------------------------

# Builds and installs external git projects.
function(add_external_git_project)
    set(options)
    set(oneValueArgs NAME URL GIT_REPOSITORY GIT_TAG GIT_SHALLOW SOURCE_SUBDIR EXTERNALS_BIN_DIR BUILD_TYPE)
    set(multiValueArgs CMAKE_ARGS)
    cmake_parse_arguments(ARG "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    message(STATUS "Configuring External Project: ${ARG_NAME}")
    set(lib_dir "${ARG_EXTERNALS_BIN_DIR}/${ARG_NAME}")

    # By default, GIT_SHALLOW is ON.
    if ("${ARG_GIT_SHALLOW}" STREQUAL "")
        set(ARG_GIT_SHALLOW ON)
    endif()

    ExternalProject_Add(
            ${ARG_NAME}
            URL             ${ARG_URL}
            GIT_REPOSITORY  ${ARG_GIT_REPOSITORY}
            GIT_TAG         ${ARG_GIT_TAG}
            GIT_SHALLOW     ${ARG_GIT_SHALLOW}
            PREFIX          "${lib_dir}/prefix"
            SOURCE_DIR      "${lib_dir}/src"
            STAMP_DIR       "${lib_dir}/stamp"
            BINARY_DIR      "${lib_dir}/build"
            INSTALL_DIR     "${lib_dir}/install"
            DOWNLOAD_DIR    "${lib_dir}/download"
            LOG_DIR         "${lib_dir}/log"
            CMAKE_ARGS      -DCMAKE_BUILD_TYPE=${ARG_BUILD_TYPE}
                            -DCMAKE_INSTALL_PREFIX=<INSTALL_DIR>
                            ${ARG_CMAKE_ARGS}
            SOURCE_SUBDIR   ${ARG_SOURCE_SUBDIR}
            LOG_DOWNLOAD ON
            LOG_CONFIGURE ON
            LOG_BUILD ON
            LOG_INSTALL ON
            LOG_UPDATE ON
            LOG_PATCH ON
            LOG_TEST ON
            LOG_MERGED_STDOUTERR ON
            LOG_OUTPUT_ON_FAILURE ON
            GIT_SUBMODULES_RECURSE ON
            GIT_PROGRESS OFF
            BUILD_ALWAYS OFF
            UPDATE_COMMAND ""
    )

    # Make include and lib folders available to prevent linker warnings.
    file(MAKE_DIRECTORY "${lib_dir}/install/include" "${lib_dir}/install/lib")

    include_directories(${lib_dir}/install/include)
    link_directories(${lib_dir}/install/lib)
endfunction()

# Download an external file.
function(download_external_file)
    set(options)
    set(oneValueArgs NAME URL DOWNLOAD_NAME EXTERNALS_BIN_DIR)
    set(multiValueArgs)
    cmake_parse_arguments(ARG "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    message(STATUS "Configuring External File: ${ARG_NAME}")
    set(file_dir "${ARG_EXTERNALS_BIN_DIR}/${ARG_NAME}")

    ExternalProject_Add(
            ${ARG_NAME}
            URL             ${ARG_URL}
            DOWNLOAD_NAME   ${ARG_DOWNLOAD_NAME}
            PREFIX          "${file_dir}/prefix"
            SOURCE_DIR      "${file_dir}/src"
            STAMP_DIR       "${file_dir}/stamp"
            DOWNLOAD_DIR    "${file_dir}/download"
            LOG_DIR         "${file_dir}/log"
            CONFIGURE_COMMAND ""
            BUILD_COMMAND     ""
            INSTALL_COMMAND   ""
            UPDATE_COMMAND    ""
            LOG_DOWNLOAD ON
            DOWNLOAD_NO_EXTRACT ON
    )
endfunction()

# ---------------------------------------------------------------------------------
# COMMON SETTINGS
# ---------------------------------------------------------------------------------

# Externals build and install folder.
set(EXTERNALS_BINARY_DIR "${CMAKE_BINARY_DIR}/Externals")

# Common cmake project settings for the external projects.
set(EXTERNAL_COMMON_CMAKE_ARGS
        -DCMAKE_C_COMPILER=${CMAKE_C_COMPILER}
        -DCMAKE_CXX_COMPILER=${CMAKE_CXX_COMPILER}
        -DCMAKE_MAKE_PROGRAM=${CMAKE_MAKE_PROGRAM}
        -DCMAKE_POSITION_INDEPENDENT_CODE=${CMAKE_POSITION_INDEPENDENT_CODE}
        -DCMAKE_BUILD_WITH_INSTALL_RPATH=${CMAKE_BUILD_WITH_INSTALL_RPATH}
        -DCMAKE_INSTALL_RPATH=${CMAKE_INSTALL_RPATH}
        -Wno-dev
)

if(MSVC)
    if("${CMAKE_MSVC_RUNTIME_LIBRARY}" STREQUAL "MultiThreaded")
        set(EXTERNALS_MSVC_RUNTIME_LIBRARY /MT)
        set(ANTLR4_WITH_STATIC_CRT ON)
    elseif("${CMAKE_MSVC_RUNTIME_LIBRARY}" STREQUAL "MultiThreadedDLL")
        set(EXTERNALS_MSVC_RUNTIME_LIBRARY /MD)
    else()
        message(FATAL_ERROR "CMAKE_MSVC_RUNTIME_LIBRARY value: '${CMAKE_MSVC_RUNTIME_LIBRARY}' is not supported.")
    endif()

    list(APPEND EXTERNAL_COMMON_CMAKE_ARGS
            -DCMAKE_C_FLAGS_DEBUG=${EXTERNALS_MSVC_RUNTIME_LIBRARY}
            -DCMAKE_C_FLAGS_RELEASE=${EXTERNALS_MSVC_RUNTIME_LIBRARY}
            -DCMAKE_CXX_FLAGS_DEBUG=${EXTERNALS_MSVC_RUNTIME_LIBRARY}
            -DCMAKE_CXX_FLAGS_RELEASE=${EXTERNALS_MSVC_RUNTIME_LIBRARY}
            -DCMAKE_MSVC_RUNTIME_LIBRARY=${CMAKE_MSVC_RUNTIME_LIBRARY}
    )
endif()

# ---------------------------------------------------------------------------------
# CLEAN EXTERNALS TARGET (Cleans only the external projects)
# ---------------------------------------------------------------------------------

add_custom_target(clean_externals
        COMMAND ${CMAKE_COMMAND} -E remove_directory ${EXTERNALS_BINARY_DIR}
        COMMENT "Cleaning external projects."
)

# ---------------------------------------------------------------------------------
# ANTLR4 CPP
# ---------------------------------------------------------------------------------

add_external_git_project(
        NAME                antlr4_cpp
        GIT_REPOSITORY      https://github.com/antlr/antlr4.git
        # TODO: Temporarily set to dev branch until recent fixes are released for Windows.
        GIT_TAG             dev     # ${EXTERNAL_ANTLR4_VERSION} # Temporarily set to dev branch to get recent fixes for MSVC.
        CMAKE_ARGS          ${EXTERNAL_COMMON_CMAKE_ARGS}
                            -DBUILD_SHARED_LIBS=OFF
                            -DCMAKE_SHARED_LIBRARY_SUFFIX_CXX=.xxx
                            -DWITH_STATIC_CRT=${ANTLR4_WITH_STATIC_CRT}
        SOURCE_SUBDIR       runtime/Cpp
        EXTERNALS_BIN_DIR   ${EXTERNALS_BINARY_DIR}
        BUILD_TYPE          Release
)

download_external_file(
        NAME                antlr4_tool
        URL                 https://www.antlr.org/download/antlr-${EXTERNAL_ANTLR4_VERSION}-complete.jar
        DOWNLOAD_NAME       antlr4-tool.jar
        EXTERNALS_BIN_DIR   ${EXTERNALS_BINARY_DIR}
)

# Include a subdirectory of ANTLR4 which is an irregular subfolder.
include_directories(${EXTERNALS_BINARY_DIR}/antlr4_cpp/install/include/antlr4-runtime)

# ---------------------------------------------------------------------------------
# CATCH2 CPP
# ---------------------------------------------------------------------------------

add_external_git_project(
        NAME                catch2_cpp
        GIT_REPOSITORY      https://github.com/catchorg/Catch2.git
        GIT_TAG             ${EXTERNAL_CATCH2_VERSION}
        CMAKE_ARGS          ${EXTERNAL_COMMON_CMAKE_ARGS}
                            -DCATCH_BUILD_TESTING=OFF
        EXTERNALS_BIN_DIR   ${EXTERNALS_BINARY_DIR}
        BUILD_TYPE          Release
)

# ---------------------------------------------------------------------------------
# LLVM CPP
# ---------------------------------------------------------------------------------

add_external_git_project(
        NAME                llvm_cpp
        GIT_REPOSITORY      https://github.com/llvm/llvm-project.git
        GIT_TAG             ${EXTERNAL_LLVM_VERSION}
        CMAKE_ARGS          ${EXTERNAL_COMMON_CMAKE_ARGS}
                            -DBUILD_SHARED_LIBS=OFF
                            -DLLVM_TARGETS_TO_BUILD=all
                            -DLLVM_DEFAULT_TARGET_TRIPLE=host
                            -DLLVM_INCLUDE_TOOLS=OFF
                            -DLLVM_INCLUDE_UTILS=OFF
                            -DLLVM_INCLUDE_EXAMPLES=OFF
                            -DLLVM_INCLUDE_TESTS=OFF
                            -DLLVM_INCLUDE_BENCHMARKS=OFF
                            -DLLVM_INCLUDE_DOCS=OFF
                            -DLLVM_ENABLE_ZLIB=OFF
                            -DLLVM_ENABLE_TERMINFO=OFF
                            -DLLVM_ENABLE_LIBXML2=OFF
                            -DLLVM_ENABLE_LIBEDIT=OFF
                            -DLLVM_ENABLE_LIBPFM=OFF
                            -DLLVM_STATIC_CXX_STDLIB=ON
        SOURCE_SUBDIR       llvm
        EXTERNALS_BIN_DIR   ${EXTERNALS_BINARY_DIR}
        BUILD_TYPE          Release
)

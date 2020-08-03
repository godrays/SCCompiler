add_executable(SCCompilerApp
        main.cpp
        )

target_link_libraries(SCCompilerApp PRIVATE SCCompilerLib)

# Post build command to copy resources in every single build step
add_custom_command(
        TARGET SCCompilerApp POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
                ${CMAKE_CURRENT_SOURCE_DIR}/SCCompilerTestCode.src
                ${CMAKE_CURRENT_BINARY_DIR}/SCCompilerTestCode.src
        )

# Copy shared dynamic libraries to binary folder
file(COPY
        ${CMAKE_SOURCE_DIR}/Externals/ANTLR/4.8/installed/lib/libantlr4-runtime.4.8.dylib
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/
        )

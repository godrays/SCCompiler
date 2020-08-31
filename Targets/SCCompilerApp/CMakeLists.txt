#
#  Copyright © 2018-Present, Arkin Terli. All rights reserved.
#

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

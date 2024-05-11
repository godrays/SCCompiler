#
#  Copyright © 2018-Present, Arkin Terli. All rights reserved.
#

add_executable(SCCompilerApp
        main.cpp
        )

target_link_libraries(SCCompilerApp PRIVATE SCCompilerLib)

# Custom target to copy resources always if the resource is different
add_custom_target(CopyResources ALL
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_CURRENT_SOURCE_DIR}/SCCompilerTestCode.src
        ${CMAKE_CURRENT_BINARY_DIR}/SCCompilerTestCode.src
)
# Add dependency to ensure CopyResources is executed before SCCompilerApp
add_dependencies(SCCompilerApp CopyResources)

install(TARGETS SCCompilerApp DESTINATION ${CMAKE_INSTALL_PREFIX})
install(FILES SCCompilerTestCode.src DESTINATION ${CMAKE_INSTALL_PREFIX})

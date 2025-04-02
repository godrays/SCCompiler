#
#  Copyright © 2018-Present, Arkin Terli. All rights reserved.
#

set(TARGET_NAME SCCompilerApp)

add_executable(${TARGET_NAME}
        main.cpp
        )

target_link_libraries(${TARGET_NAME} PRIVATE SCCompilerLib)

install(TARGETS ${TARGET_NAME} DESTINATION ${CMAKE_INSTALL_PREFIX})

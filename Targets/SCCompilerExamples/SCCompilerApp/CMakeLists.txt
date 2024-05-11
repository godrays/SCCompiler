#
#  Copyright © 2018-Present, Arkin Terli. All rights reserved.
#

add_executable(SCCompilerApp
        main.cpp
        )

target_link_libraries(SCCompilerApp PRIVATE SCCompilerLib)

install(TARGETS SCCompilerApp DESTINATION ${CMAKE_INSTALL_PREFIX})
install(FILES SCCompilerTestCode.src DESTINATION ${CMAKE_INSTALL_PREFIX})

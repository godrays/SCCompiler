#
#  Copyright © 2018-Present, Arkin Terli. All rights reserved.
#

set(TARGET_NAME SCCompilerTests)

add_executable(${TARGET_NAME}
        main.cpp
        SyntaxTests.cpp
        SemanticTests.cpp
        CodeGenerationTests.cpp
        TestUtils.cpp
        )

add_dependencies(${TARGET_NAME} catch2_cpp)

target_link_libraries(${TARGET_NAME} PRIVATE SCCompilerLib)

install(TARGETS ${TARGET_NAME} DESTINATION ${CMAKE_INSTALL_PREFIX})

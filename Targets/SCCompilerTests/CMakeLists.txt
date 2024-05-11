#
#  Copyright © 2018-Present, Arkin Terli. All rights reserved.
#

add_executable(SCCompilerTests
        main.cpp
        SyntaxTests.cpp
        SemanticTests.cpp
        CodeGenerationTests.cpp
        TestUtils.cpp
        )

target_link_libraries(SCCompilerTests PRIVATE SCCompilerLib)

install(TARGETS SCCompilerTests DESTINATION ${CMAKE_INSTALL_PREFIX})

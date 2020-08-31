#
#  Copyright © 2018-Present, Arkin Terli. All rights reserved.
#

add_executable(SCCompilerTestApp
        main.cpp
        SyntaxTests.cpp
        SemanticTests.cpp
        CodeGenerationTests.cpp
        TestUtils.cpp
        )

target_link_libraries(SCCompilerTestApp PRIVATE SCCompilerLib)

# Copy shared dynamic libraries to binary folder
file(COPY
        ${CMAKE_SOURCE_DIR}/Externals/ANTLR/4.8/installed/lib/${ANTLR4_LIB}
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/
        )

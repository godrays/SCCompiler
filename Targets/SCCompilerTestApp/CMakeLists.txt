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

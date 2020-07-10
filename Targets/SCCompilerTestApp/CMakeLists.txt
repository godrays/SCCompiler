add_executable(SCCompilerTestApp
        main.cpp
        SyntaxTests.cpp
        SemanticTests.cpp
        CodeGenerationTests.cpp
        TestUtils.cpp
        )

target_link_libraries(SCCompilerTestApp SCCompilerLib)

# Copy shared dynamic libraries to binary folder
file(COPY
        ${CMAKE_SOURCE_DIR}/Externals/ANTLR/4.7.1/Runtime/lib/libantlr4-runtime.dylib
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/
        )

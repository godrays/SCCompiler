//
//  CodeGenerationTests.cpp
//
//  Created by Arkin Terli on 5/8/18.
//  Copyright © 2018 Arkin Terli. All rights reserved.
//

#include "Compiler.hpp"
#include "CodeGenerationTests.hpp"

using namespace SCCompiler;


// Registers the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION( CodeGenerationTests );


#pragma mark - CodeGenerationTests Tests


void CodeGenerationTests::setUp()
{
    // Common test setup goes here
}


void CodeGenerationTests::tearDown()
{
    // Common test setup cleanup goes here
}


void CodeGenerationTests::TestCode(std::string sourceCode, CompileResult expectedCompilerResult, bool acceptExpectedCompilerResult)
{
    Compiler compiler;
    
    // Assert if compiler result is not expected.
    if ((acceptExpectedCompilerResult && (compiler.CompileFromMemory(sourceCode) != expectedCompilerResult)) ||
       (!acceptExpectedCompilerResult && (compiler.CompileFromMemory(sourceCode) == expectedCompilerResult)))
    {
        std::cerr << compiler.GetErrorMessage() << std::endl;
        CPPUNIT_ASSERT(false);
    }
}

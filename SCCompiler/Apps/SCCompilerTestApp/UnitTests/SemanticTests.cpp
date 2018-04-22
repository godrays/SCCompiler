//
//  SemanticTests.cpp
//  SCCompiler
//
//  Created by Arkin Terli on 4/18/18.
//  Copyright © 2018 Arkin Terli. All rights reserved.
//

#include "Compiler.hpp"
#include "SemanticTests.hpp"

using namespace SCCompiler;


// Registers the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION( SemanticTests );


#pragma mark - Semantic Tests


void SemanticTests::setUp()
{
    // Common test setup goes here
}


void SemanticTests::tearDown()
{
    // Common test setup cleanup goes here
}


void SemanticTests::TestCode(std::string sourceCode, CompileResult expectedCompilerResult, bool acceptExpectedCompilerResult)
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


void SemanticTests::SemanticUndeclaredIdentifierTest()
{
    // Compiler must fails in use of an undeclared identifier.

    TestCode("\
    void func() { i=5; }     \n\
    ", CompileResult::rCompileResultSemanticError, true);

    TestCode("\
    void func() { f=5.0; }     \n\
    ", CompileResult::rCompileResultSemanticError, true);

    TestCode("\
    void func() { b=true; }     \n\
    ", CompileResult::rCompileResultSemanticError, true);

    TestCode("\
    void func() { func2(); }     \n\
    ", CompileResult::rCompileResultSemanticError, true);
}


void SemanticTests::SemanticTypeMismatchTest()
{
    // Compiler must fails for mismathed type use.

    TestCode("\
    int i = 5 * false;        \n\
    ", CompileResult::rCompileResultSemanticError, true);

    TestCode("\
    float f = 5.0 * true;     \n\
    ", CompileResult::rCompileResultSemanticError, true);

    TestCode("\
    int i = 5.0;              \n\
    ", CompileResult::rCompileResultSemanticError, true);

    // Parameter type does not match.
    TestCode("\
    void func(int i) { }    \n\
    void func2() { func(1.1); }    \n\
    ", CompileResult::rCompileResultSemanticError, true);

    // Function return type should match with return value type.
    TestCode("\
    float func() { return 1.0; }            \n\
    float func1() { { return 1.0; } }       \n\
    float func2() { { { return 1.0; } } }   \n\
    void  func3() { return; }               \n\
    void  func4() { { return; } }           \n\
    ", CompileResult::rCompileResultOk, true);

    TestCode("\
    void  func()  { return 1.0; }    \n\
    float func1() { return; }        \n\
    ", CompileResult::rCompileResultSemanticError, true);
};


void SemanticTests::SemanticNonSpecificTest()
{
    // Function with return type must have at least one return statement.

    TestCode("\
    float  func()  {  }    \n\
    ", CompileResult::rCompileResultSemanticError, true);
}

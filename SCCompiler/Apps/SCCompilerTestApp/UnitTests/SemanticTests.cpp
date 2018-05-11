//
//  SemanticTests.cpp
//  SCC
//
//  Created by Arkin Terli on 4/18/18.
//  Copyright © 2018 Arkin Terli. All rights reserved.
//

#include "Compiler.hpp"
#include "SemanticTests.hpp"

using namespace SCC;


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


SCModule * SemanticTests::TestCode(std::string sourceCode, SCCompileResult expectedCompileResult, bool acceptExpectedCompileResult)
{
    Compiler compiler;
    
    SCCompileResult compileResult;
    
    auto scModule = compiler.CompileFromMemory(sourceCode, compileResult);
    
    // Assert if compiler result is not expected.
    if ((acceptExpectedCompileResult && (compileResult != expectedCompileResult)) ||
       (!acceptExpectedCompileResult && (compileResult == expectedCompileResult)))
    {
        std::cerr << compiler.GetErrorMessage() << std::endl;
        CPPUNIT_ASSERT(false);
    }
    
    return scModule;
}


void SemanticTests::SemanticUndeclaredIdentifierTest()
{
    // Compiler must fails in use of an undeclared identifier.

    TestCode("\
    void func() { i=5; }     \n\
    ", SCCompileResult::rSCCompileResultSemanticError, true);

    TestCode("\
    void func() { f=5.0; }     \n\
    ", SCCompileResult::rSCCompileResultSemanticError, true);

    TestCode("\
    void func() { b=true; }     \n\
    ", SCCompileResult::rSCCompileResultSemanticError, true);

    TestCode("\
    void func() { func2(); }     \n\
    ", SCCompileResult::rSCCompileResultSemanticError, true);
}


void SemanticTests::SemanticTypeMismatchTest()
{
    // Compiler must fails for mismathed type use.

    TestCode("\
    int i = 5 * false;        \n\
    ", SCCompileResult::rSCCompileResultSemanticError, true);

    TestCode("\
    float f = 5.0 * true;     \n\
    ", SCCompileResult::rSCCompileResultSemanticError, true);

    TestCode("\
    int i = 5.0;              \n\
    ", SCCompileResult::rSCCompileResultSemanticError, true);

    // Parameter type does not match.
    TestCode("\
    void func(int i) { }    \n\
    void func2() { func(1.1); }    \n\
    ", SCCompileResult::rSCCompileResultSemanticError, true);

    // Function return type should match with return value type.
    TestCode("\
    float func() { return 1.0; }            \n\
    float func1() { { return 1.0; } }       \n\
    float func2() { { { return 1.0; } } }   \n\
    void  func3() { return; }               \n\
    void  func4() { { return; } }           \n\
    ", SCCompileResult::rSCCompileResultOk, true);

    TestCode("\
    void  func()  { return 1.0; }    \n\
    float func1() { return; }        \n\
    ", SCCompileResult::rSCCompileResultSemanticError, true);
};


void SemanticTests::SemanticNonSpecificTest()
{
    // Function with return type must have at least one return statement.

    TestCode("\
    float  func()  {  }    \n\
    ", SCCompileResult::rSCCompileResultSemanticError, true);
}

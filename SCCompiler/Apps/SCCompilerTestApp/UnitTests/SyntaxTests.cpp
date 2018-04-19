//
//  SyntaxTests.cpp
//
//  Created by Arkin Terli on 4/17/18.
//  Copyright © 2018 Arkin Terli. All rights reserved.
//

#include "Compiler.hpp"
#include "SyntaxTests.hpp"

using namespace SCCompiler;


// Registers the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION( SyntaxTests );


#pragma mark - Syntax Tests


void SyntaxTests::setUp()
{
    // Common test setup goes here
}


void SyntaxTests::tearDown()
{
    // Common test setup cleanup goes here
}


void SyntaxTests::TestCode(std::string sourceCode, CompileResult expectedCompilerResult, bool acceptExpectedCompilerResult)
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


void SyntaxTests::SyntaxAcceptanceTest()
{
    // Test syntaxt code.

    TestCode("\
    int i;                             \n\
    int i1 = 1;                        \n\
    int i2 = (4*5)+2/(2-3)*5;          \n\
    float f;                           \n\
    float f1 = 1.0;                    \n\
    float f2 = (4.2*5.1)+2.99/(2.10-3)*5;   \n\
    bool k;                            \n\
    bool k1 = true;                    \n\
    bool k2 = false;                   \n\
    /* Comment */                      \n\
    void func1() { }                   \n\
    void func2() { return; }           \n\
    void func3(int i, float f, bool b) { { int i; float f; bool b; } }    \n\
    float func4(int i, float f, bool b) { { int i=5; float f=5.0; bool b=false; } return f; }    \n\
    int   func5() { return 5; }           \n\
    float func6() { return 5.0; }         \n\
    bool  func7() { return true; }        \n\
    bool  func8() { return false; }       \n\
    int   func9() { int i=5; return i; }             \n\
    float func10() { float f=5.0; return f; }        \n\
    bool  func11()  { bool b=true; return b; }       \n\
    bool  func12()  { bool b=false; { return b; } }  \n\
    bool  func13(bool bArg)  { return bArg; }        \n\
    bool  func14(bool bArg)  { bool b = bArg; return b; }  \n\
    /* Use global variables */               \n\
    int   func15() { return i; return i1; }  \n\
    float func16() { return f; return f1; }  \n\
    bool  func17() { return k; return k1; }  \n\
    /* Call function in function */      \n\
    void  func18() { func14(false); }    \n\
    void  func19() { { func14(true); } } \n\
    int   func20() { return func9(); }   \n\
    float func21() { { return func10(); } }             \n\
    int   func22() { int i=func9(); return i; }          \n\
    float func23() { float f=func10(); return f; }      \n\
    bool  func24() { bool b=func13(true); return b; }   \n\
    float func25() { return func4((4*5)+2/(2-3)*5, (4.2*5.1)+2.99/(2.10-3)*5, false); }  \n\
    int   func26() { return (4.2*5.1)+2.99/(2.10-3)*5; }  \n\
    ", CompileResult::rCompileResultOk, true);

}

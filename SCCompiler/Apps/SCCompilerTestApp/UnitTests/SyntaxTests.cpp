//
//  SyntaxTests.cpp
//
//  Created by Arkin Terli on 4/17/18.
//  Copyright © 2018 Arkin Terli. All rights reserved.
//

#include "Compiler.hpp"
#include "SyntaxTests.hpp"

using namespace scc;


// Registers the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION( SyntaxTests );


#pragma mark - SyntaxTests Implementations

void SyntaxTests::setUp()
{
    // Common test setup goes here
}


void SyntaxTests::tearDown()
{
    // Common test setup cleanup goes here
}


void SyntaxTests::TestCode(std::string sourceCode, SCCompileResult expectedCompileResult, bool acceptExpectedCompileResult)
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

    delete scModule;
}


void SyntaxTests::SyntaxAcceptanceTest()
{
    // Test syntaxt code.

    TestCode("\
    int i;                             \n\
    int i1 = 1;                        \n\
    int i2 = (4*5)+2/(2-3)*5;          \n\
    int i3 = -4*5;                     \n\
    int i4 = -i3;                      \n\
    float f;                           \n\
    float f1 = 1.0;                    \n\
    float f2 = (4.2*5.1)+2.99/(2.10-3.0)*5.0;   \n\
    float f3 = -4.2*5.1;               \n\
    bool k;                            \n\
    bool k1 = true;                    \n\
    bool k2 = false;                   \n\
    bool k3 = 3 == 4;                  \n\
    bool k4 = 3 >= 4;                  \n\
    bool k5 = 3 <= 4;                  \n\
    bool k6 = 3 != 4;                  \n\
    bool k7 = 3 > 4;                   \n\
    bool k8 = 3 < 4;                   \n\
    bool k9 = 3.1 == 4.1;              \n\
    bool k10 = 3.1 >= 4.1;             \n\
    bool k11 = 3.1 <= 4.1;             \n\
    bool k12 = 3.1 != 4.1;             \n\
    bool k13 = 3.1 > 4.1;              \n\
    bool k14 = 3.1 < 4.1;              \n\
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
    float func25() { return func4((4*5)+2/(2-3)*5, (4.2*5.1)+2.99/(2.10-3.0)*5.0, false); }  \n\
    int   func26() { return (4*5)+2/(2-3)*5; }  \n\
    float func27() { return -func4(-5, -4.2, false); }  \n\
    int   func28(int i) { int a=i; if (i == 2) { a=11; return 4; a = 5; return 3; } else { if (i == 3) { return 10; } a = 7; } return a; }  \n\
    bool  func29(float f) { return bool(!f); }  \n\
    bool  func30(int i) { return bool(!i); }    \n\
    bool  func31(bool b) { return !b; }         \n\
    ", SCCompileResult::kSCCompileResultOk, true);
}

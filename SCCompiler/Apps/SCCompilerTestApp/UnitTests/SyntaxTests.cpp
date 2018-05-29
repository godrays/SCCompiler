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
    int i5 = ++i;                      \n\
    int i6 = --i;                      \n\
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
    bool k15 = true && false;             \n\
    bool k16 = k13 && k14 && k15;         \n\
    bool k17 = true || false;             \n\
    bool k18 = k13 || k14 || k15;         \n\
    bool k19 = k13 && k14 || k15 && k16;  \n\
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
    void  func32(int i)  { if (i <= 0) return; func32(i - 1);  }       \n\
    void  func33() { for ( ; ; ) { }  }              \n\
    void  func34() { for (int i,j,k; ; ) { }  }      \n\
    void  func35() { for (int i=0,j=i*2; ; ) { }  }  \n\
    int   func36() { int a; for (int i=0,j=i*2; i < 10; i=j+1, j=j+i) { a = j + i; }  return a; }  \n\
    int   func37() { int a; for (int i=0,j=i*2; i < 10; i=j+1, j=j+i) a = j + i;  return a; }      \n\
    int   func38() { for (int i=0; i < 10; i=i+1) continue;  return 0; }                 \n\
    int   func39() { for (int i=0; i < 10; i=i+1) { continue; i=i+1; } return 0; }       \n\
    int   func40() { for (int i=0; i < 10; i=i+1) break;  return 0; }                    \n\
    int   func41() { for (int i=0; i < 10; i=i+1) { break; i=i+1; } return 0; }          \n\
    void  func42() { int i=0; while (i < 10) { } }                                       \n\
    void  func43() { int i=0; while (i < 10) { i=i+1; } }                                \n\
    int   func44() { int i=0; while (i < 10) continue;  return 0; }                      \n\
    int   func45() { int i=0; while (i < 10) { continue; i=i+1; } return 0; }            \n\
    int   func46() { int i=0; while (i < 10) break; return 0; }                          \n\
    int   func47() { int i=0; while (i < 10) { break; i=i+1; } return 0; }               \n\
    void  func48() { int i=0; do { } while (i < 10); }                                   \n\
    void  func49() { int i=0; do { i=i+1; } while (i < 10); }                            \n\
    int   func50() { int i=0; do continue; while (i < 10); return 0; }                   \n\
    int   func51() { int i=0; do { continue; i=i+1; } while (i < 10); return 0; }        \n\
    int   func52() { int i=0; do break; while (i < 10); return 0; }                      \n\
    int   func53() { int i=0; do { break; i=i+1; } while (i < 10); return 0; }           \n\
    ", SCCompileResult::kSCCompileResultOk, true);
}

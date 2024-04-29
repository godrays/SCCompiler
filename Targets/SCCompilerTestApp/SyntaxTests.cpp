//
//  SyntaxTests.cpp
//
//  Created by Arkin Terli on 4/17/18.
//  Copyright © 2018-Present, Arkin Terli. All rights reserved.
//

#include <string>
#include <catch2/catch.hpp>
#include <Compiler.hpp>
#include "TestUtils.hpp"


using namespace scc;


TEST_CASE("SyntaxTests", "[SyntaxTests]")
{
    REQUIRE(TestCode("\
    int i;         \n\
    ", SCCompileResult::kSCCompileResultOk, true));

    REQUIRE(TestCode("\
    int i1 = 1;     \n\
    ", SCCompileResult::kSCCompileResultOk, true));

    REQUIRE(TestCode("\
    int i2 = (4*5)+2/(2-3)*5;     \n\
    ", SCCompileResult::kSCCompileResultOk, true));

    REQUIRE(TestCode("\
    int i3 = -4*5;         \n\
    ", SCCompileResult::kSCCompileResultOk, true));

    REQUIRE(TestCode("\
    int i3 = -4*5;         \n\
    int i4 = -i3;          \n\
    ", SCCompileResult::kSCCompileResultOk, true));

    REQUIRE(TestCode("\
    int i;            \n\
    int i5 = ++i;     \n\
    ", SCCompileResult::kSCCompileResultOk, true));

    REQUIRE(TestCode("\
    int i;         \n\
    int i6 = --i;  \n\
    ", SCCompileResult::kSCCompileResultOk, true));

    REQUIRE(TestCode("\
    float f;         \n\
    ", SCCompileResult::kSCCompileResultOk, true));

    REQUIRE(TestCode("\
    float f1 = 1.0;   \n\
    ", SCCompileResult::kSCCompileResultOk, true));

    REQUIRE(TestCode("\
    float f2 = (4.2*5.1)+2.99/(2.10-3.0)*5.0;         \n\
    ", SCCompileResult::kSCCompileResultOk, true));

    REQUIRE(TestCode("\
    float f3 = -4.2*5.1;         \n\
    ", SCCompileResult::kSCCompileResultOk, true));

    REQUIRE(TestCode("\
    bool k;         \n\
    ", SCCompileResult::kSCCompileResultOk, true));

    REQUIRE(TestCode("\
    bool k1 = true;         \n\
    ", SCCompileResult::kSCCompileResultOk, true));

    REQUIRE(TestCode("\
    bool k2 = false;         \n\
    ", SCCompileResult::kSCCompileResultOk, true));

    REQUIRE(TestCode("\
    bool k3 = 3 == 4;         \n\
    ", SCCompileResult::kSCCompileResultOk, true));

    REQUIRE(TestCode("\
    bool k4 = 3 >= 4;         \n\
    ", SCCompileResult::kSCCompileResultOk, true));

    REQUIRE(TestCode("\
    bool k5 = 3 <= 4;         \n\
    ", SCCompileResult::kSCCompileResultOk, true));

    REQUIRE(TestCode("\
    bool k6 = 3 != 4;         \n\
    ", SCCompileResult::kSCCompileResultOk, true));

    REQUIRE(TestCode("\
    bool k7 = 3 > 4;         \n\
    ", SCCompileResult::kSCCompileResultOk, true));

    REQUIRE(TestCode("\
    bool k8 = 3 < 4;         \n\
    ", SCCompileResult::kSCCompileResultOk, true));

    REQUIRE(TestCode("\
    bool k9 = 3.1 == 4.1;         \n\
    ", SCCompileResult::kSCCompileResultOk, true));

    REQUIRE(TestCode("\
    bool k10 = 3.1 >= 4.1;         \n\
    ", SCCompileResult::kSCCompileResultOk, true));

    REQUIRE(TestCode("\
    bool k11 = 3.1 <= 4.1;         \n\
    ", SCCompileResult::kSCCompileResultOk, true));

    REQUIRE(TestCode("\
    bool k12 = 3.1 != 4.1;         \n\
    ", SCCompileResult::kSCCompileResultOk, true));

    REQUIRE(TestCode("\
    bool k13 = 3.1 > 4.1;         \n\
    ", SCCompileResult::kSCCompileResultOk, true));

    REQUIRE(TestCode("\
    bool k14 = 3.1 < 4.1;         \n\
    ", SCCompileResult::kSCCompileResultOk, true));

    REQUIRE(TestCode("\
    bool k15 = true && false;         \n\
    ", SCCompileResult::kSCCompileResultOk, true));

    REQUIRE(TestCode("\
    bool k13 = 3.1 > 4.1;          \n\
    bool k14 = 3.1 < 4.1;          \n\
    bool k15 = true && false;      \n\
    bool k16 = k13 && k14 && k15;  \n\
    ", SCCompileResult::kSCCompileResultOk, true));

    REQUIRE(TestCode("\
    bool k17 = true || false;         \n\
    ", SCCompileResult::kSCCompileResultOk, true));

    REQUIRE(TestCode("\
    bool k13 = 3.1 > 4.1;          \n\
    bool k14 = 3.1 < 4.1;          \n\
    bool k15 = true && false;      \n\
    bool k18 = k13 || k14 || k15;  \n\
    ", SCCompileResult::kSCCompileResultOk, true));

    REQUIRE(TestCode("\
    bool k13 = 3.1 > 4.1;          \n\
    bool k14 = 3.1 < 4.1;          \n\
    bool k15 = true && false;      \n\
    bool k16 = k13 && k14 && k15;  \n\
    bool k19 = k13 && k14 || k15 && k16;         \n\
    ", SCCompileResult::kSCCompileResultOk, true));

    /* Comment */

    REQUIRE(TestCode("\
    /* Comment */            \n\
    void func1() { }         \n\
    ", SCCompileResult::kSCCompileResultOk, true));

    REQUIRE(TestCode("\
    void func2() { return; }         \n\
    ", SCCompileResult::kSCCompileResultOk, true));

    REQUIRE(TestCode("\
    void func3(int i, float f, bool b) { { int i; float f; bool b; } }         \n\
    ", SCCompileResult::kSCCompileResultOk, true));

    REQUIRE(TestCode("\
    float func4(int i, float f, bool b) { { int i=5; float f=5.0; bool b=false; } return f; }         \n\
    ", SCCompileResult::kSCCompileResultOk, true));

    REQUIRE(TestCode("\
    int   func5() { return 5; }         \n\
    ", SCCompileResult::kSCCompileResultOk, true));

    REQUIRE(TestCode("\
    float func6() { return 5.0; }         \n\
    ", SCCompileResult::kSCCompileResultOk, true));

    REQUIRE(TestCode("\
    bool  func7() { return true; }         \n\
    ", SCCompileResult::kSCCompileResultOk, true));

    REQUIRE(TestCode("\
    bool  func8() { return false; }         \n\
    ", SCCompileResult::kSCCompileResultOk, true));

    REQUIRE(TestCode("\
    int   func9() { int i=5; return i; }         \n\
    ", SCCompileResult::kSCCompileResultOk, true));

    REQUIRE(TestCode("\
    float func10() { float f=5.0; return f; }         \n\
    ", SCCompileResult::kSCCompileResultOk, true));

    REQUIRE(TestCode("\
    bool  func11()  { bool b=true; return b; }         \n\
    ", SCCompileResult::kSCCompileResultOk, true));

    REQUIRE(TestCode("\
    bool  func12()  { bool b=false; { return b; } }         \n\
    ", SCCompileResult::kSCCompileResultOk, true));

    REQUIRE(TestCode("\
    bool  func13(bool bArg)  { return bArg; }         \n\
    ", SCCompileResult::kSCCompileResultOk, true));

    REQUIRE(TestCode("\
    bool  func14(bool bArg)  { bool b = bArg; return b; }         \n\
    ", SCCompileResult::kSCCompileResultOk, true));

    /* Use global variables */

    REQUIRE(TestCode("\
    /* Use global variables */                 \n\
    int i;          \n\
    int i1 = 1;     \n\
    int   func15() { return i; return i1; }    \n\
    ", SCCompileResult::kSCCompileResultOk, true));

    REQUIRE(TestCode("\
    float f;          \n\
    float f1 = 1.0;   \n\
    float func16() { return f; return f1; }         \n\
    ", SCCompileResult::kSCCompileResultOk, true));

    REQUIRE(TestCode("\
    bool k;             \n\
    bool k1 = true;     \n\
    bool  func17() { return k; return k1; }         \n\
    ", SCCompileResult::kSCCompileResultOk, true));

    /* Call function in function */

    REQUIRE(TestCode("\
    /* Call function in function */      \n\
    bool  func14(bool bArg)  { bool b = bArg; return b; }         \n\
    void  func18() { func14(false); }         \n\
    ", SCCompileResult::kSCCompileResultOk, true));

    REQUIRE(TestCode("\
    bool  func14(bool bArg)  { bool b = bArg; return b; }         \n\
    void  func19() { { func14(true); } }         \n\
    ", SCCompileResult::kSCCompileResultOk, true));

    REQUIRE(TestCode("\
    int   func9() { int i=5; return i; }       \n\
    int   func20() { return func9(); }         \n\
    ", SCCompileResult::kSCCompileResultOk, true));

    REQUIRE(TestCode("\
    float func10() { float f=5.0; return f; }       \n\
    float func21() { { return func10(); } }         \n\
    ", SCCompileResult::kSCCompileResultOk, true));

    REQUIRE(TestCode("\
    int   func9() { int i=5; return i; }       \n\
    int   func22() { int i=func9(); return i; }         \n\
    ", SCCompileResult::kSCCompileResultOk, true));

    REQUIRE(TestCode("\
    float func10() { float f=5.0; return f; }       \n\
    float func23() { float f=func10(); return f; }         \n\
    ", SCCompileResult::kSCCompileResultOk, true));

    REQUIRE(TestCode("\
    bool  func13(bool bArg)  { return bArg; }             \n\
    bool  func24() { bool b=func13(true); return b; }     \n\
    ", SCCompileResult::kSCCompileResultOk, true));

    REQUIRE(TestCode("\
    float func4(int i, float f, bool b) { { int i=5; float f=5.0; bool b=false; } return f; }         \n\
    float func25() { return func4((4*5)+2/(2-3)*5, (4.2*5.1)+2.99/(2.10-3.0)*5.0, false); }         \n\
    ", SCCompileResult::kSCCompileResultOk, true));

    REQUIRE(TestCode("\
    int   func26() { return (4*5)+2/(2-3)*5; }         \n\
    ", SCCompileResult::kSCCompileResultOk, true));

    REQUIRE(TestCode("\
    float func4(int i, float f, bool b) { { int i=5; float f=5.0; bool b=false; } return f; }         \n\
    float func27() { return -func4(-5, -4.2, false); }         \n\
    ", SCCompileResult::kSCCompileResultOk, true));

    REQUIRE(TestCode("\
    int   func28(int i) { int a=i; if (i == 2) { a=11; return 4; a = 5; return 3; } else { if (i == 3) { return 10; } a = 7; } return a; }         \n\
    ", SCCompileResult::kSCCompileResultOk, true));

    REQUIRE(TestCode("\
    bool  func29(float f) { return bool(!f); }         \n\
    ", SCCompileResult::kSCCompileResultOk, true));

    REQUIRE(TestCode("\
    bool  func30(int i) { return bool(!i); }         \n\
    ", SCCompileResult::kSCCompileResultOk, true));

    REQUIRE(TestCode("\
    bool  func31(bool b) { return !b; }         \n\
    ", SCCompileResult::kSCCompileResultOk, true));

    REQUIRE(TestCode("\
    void  func32(int i)  { if (i <= 0) return; func32(i - 1);  }         \n\
    ", SCCompileResult::kSCCompileResultOk, true));

    REQUIRE(TestCode("\
    void  func33() { for ( ; ; ) { }  }         \n\
    ", SCCompileResult::kSCCompileResultOk, true));

    REQUIRE(TestCode("\
    void  func34() { for (int i,j,k; ; ) { }  }         \n\
    ", SCCompileResult::kSCCompileResultOk, true));

    REQUIRE(TestCode("\
    void  func35() { for (int i=0,j=i*2; ; ) { }  }         \n\
    ", SCCompileResult::kSCCompileResultOk, true));

    REQUIRE(TestCode("\
    int   func36() { int a; for (int i=0,j=i*2; i < 10; i=j+1, j=j+i) { a = j + i; }  return a; }         \n\
    ", SCCompileResult::kSCCompileResultOk, true));

    REQUIRE(TestCode("\
    int   func37() { int a; for (int i=0,j=i*2; i < 10; i=j+1, j=j+i) a = j + i;  return a; }         \n\
    ", SCCompileResult::kSCCompileResultOk, true));

    REQUIRE(TestCode("\
    int   func38() { for (int i=0; i < 10; i=i+1) continue;  return 0; }         \n\
    ", SCCompileResult::kSCCompileResultOk, true));

    REQUIRE(TestCode("\
    int   func39() { for (int i=0; i < 10; i=i+1) { continue; i=i+1; } return 0; }         \n\
    ", SCCompileResult::kSCCompileResultOk, true));

    REQUIRE(TestCode("\
    int   func40() { for (int i=0; i < 10; i=i+1) break;  return 0; }         \n\
    ", SCCompileResult::kSCCompileResultOk, true));

    REQUIRE(TestCode("\
    int   func41() { for (int i=0; i < 10; i=i+1) { break; i=i+1; } return 0; }         \n\
    ", SCCompileResult::kSCCompileResultOk, true));

    REQUIRE(TestCode("\
    void  func42() { int i=0; while (i < 10) { } }         \n\
    ", SCCompileResult::kSCCompileResultOk, true));

    REQUIRE(TestCode("\
    void  func43() { int i=0; while (i < 10) { i=i+1; } }         \n\
    ", SCCompileResult::kSCCompileResultOk, true));

    REQUIRE(TestCode("\
    int   func44() { int i=0; while (i < 10) continue;  return 0; }         \n\
    ", SCCompileResult::kSCCompileResultOk, true));

    REQUIRE(TestCode("\
    int   func45() { int i=0; while (i < 10) { continue; i=i+1; } return 0; }         \n\
    ", SCCompileResult::kSCCompileResultOk, true));

    REQUIRE(TestCode("\
    int   func46() { int i=0; while (i < 10) break; return 0; }         \n\
    ", SCCompileResult::kSCCompileResultOk, true));

    REQUIRE(TestCode("\
    int   func47() { int i=0; while (i < 10) { break; i=i+1; } return 0; }         \n\
    ", SCCompileResult::kSCCompileResultOk, true));

    REQUIRE(TestCode("\
    void  func48() { int i=0; do { } while (i < 10); }         \n\
    ", SCCompileResult::kSCCompileResultOk, true));

    REQUIRE(TestCode("\
    void  func49() { int i=0; do { i=i+1; } while (i < 10); }         \n\
    ", SCCompileResult::kSCCompileResultOk, true));

    REQUIRE(TestCode("\
    int   func50() { int i=0; do continue; while (i < 10); return 0; }         \n\
    ", SCCompileResult::kSCCompileResultOk, true));

    REQUIRE(TestCode("\
    int   func51() { int i=0; do { continue; i=i+1; } while (i < 10); return 0; }         \n\
    ", SCCompileResult::kSCCompileResultOk, true));

    REQUIRE(TestCode("\
    int   func52() { int i=0; do break; while (i < 10); return 0; }         \n\
    ", SCCompileResult::kSCCompileResultOk, true));

    REQUIRE(TestCode("\
    int   func53() { int i=0; do { break; i=i+1; } while (i < 10); return 0; }         \n\
    ", SCCompileResult::kSCCompileResultOk, true));
}

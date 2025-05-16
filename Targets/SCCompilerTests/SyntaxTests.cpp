//
//  Created by Arkin Terli on 4/17/18.
//  Copyright © 2018-Present, Arkin Terli. All rights reserved.
//

// Project includes
#include "TestUtils.hpp"
#include <Compiler.hpp>
// External includes
#include <catch2/catch.hpp>
// System includes
#include <string>


using namespace scc;


TEST_CASE("SyntaxTests", "[SyntaxTests]")
{
    REQUIRE(testCode(R"(
    int i;
    int _i;
    int i_;
    int i_12_;
    )", SCCompileResult::kOk, true));

    REQUIRE(testCode(R"(
    int i1 = 1;
    )", SCCompileResult::kOk, true));

    REQUIRE(testCode(R"(
    int i2 = (4*5)+2/(2-3)*5;
    )", SCCompileResult::kOk, true));

    REQUIRE(testCode(R"(
    int i3 = -4*5;
    )", SCCompileResult::kOk, true));

    REQUIRE(testCode(R"(
    int i3 = -4*5;
    int i4 = -i3;
    )", SCCompileResult::kOk, true));

    REQUIRE(testCode(R"(
    int i;
    int i5 = ++i;
    )", SCCompileResult::kOk, true));

    REQUIRE(testCode(R"(
    int i;
    int i6 = --i;
    )", SCCompileResult::kOk, true));

    REQUIRE(testCode(R"(
    float f;
    )", SCCompileResult::kOk, true));

    REQUIRE(testCode(R"(
    float f1 = 1.0;
    )", SCCompileResult::kOk, true));

    REQUIRE(testCode(R"(
    float f2 = (4.2*5.1)+2.99/(2.10-3.0)*5.0;
    )", SCCompileResult::kOk, true));

    REQUIRE(testCode(R"(
    float f3 = -4.2*5.1;
    )", SCCompileResult::kOk, true));

    REQUIRE(testCode(R"(
    bool k;
    )", SCCompileResult::kOk, true));

    REQUIRE(testCode(R"(
    bool k1 = true;
    )", SCCompileResult::kOk, true));

    REQUIRE(testCode(R"(
    bool k2 = false;
    )", SCCompileResult::kOk, true));

    REQUIRE(testCode(R"(
    bool k3 = 3 == 4;
    )", SCCompileResult::kOk, true));

    REQUIRE(testCode(R"(
    bool k4 = 3 >= 4;
    )", SCCompileResult::kOk, true));

    REQUIRE(testCode(R"(
    bool k5 = 3 <= 4;
    )", SCCompileResult::kOk, true));

    REQUIRE(testCode(R"(
    bool k6 = 3 != 4;
    )", SCCompileResult::kOk, true));

    REQUIRE(testCode(R"(
    bool k7 = 3 > 4;
    )", SCCompileResult::kOk, true));

    REQUIRE(testCode(R"(
    bool k8 = 3 < 4;
    )", SCCompileResult::kOk, true));

    REQUIRE(testCode(R"(
    bool k9 = 3.1 == 4.1;
    )", SCCompileResult::kOk, true));

    REQUIRE(testCode(R"(
    bool k10 = 3.1 >= 4.1;
    )", SCCompileResult::kOk, true));

    REQUIRE(testCode(R"(
    bool k11 = 3.1 <= 4.1;
    )", SCCompileResult::kOk, true));

    REQUIRE(testCode(R"(
    bool k12 = 3.1 != 4.1;
    )", SCCompileResult::kOk, true));

    REQUIRE(testCode(R"(
    bool k13 = 3.1 > 4.1;
    )", SCCompileResult::kOk, true));

    REQUIRE(testCode(R"(
    bool k14 = 3.1 < 4.1;
    )", SCCompileResult::kOk, true));

    REQUIRE(testCode(R"(
    bool k15 = true && false;
    )", SCCompileResult::kOk, true));

    REQUIRE(testCode(R"(
    bool k13 = 3.1 > 4.1;
    bool k14 = 3.1 < 4.1;
    bool k15 = true && false;
    bool k16 = k13 && k14 && k15;
    )", SCCompileResult::kOk, true));

    REQUIRE(testCode(R"(
    bool k17 = true || false;
    )", SCCompileResult::kOk, true));

    REQUIRE(testCode(R"(
    bool k13 = 3.1 > 4.1;
    bool k14 = 3.1 < 4.1;
    bool k15 = true && false;
    bool k18 = k13 || k14 || k15;
    )", SCCompileResult::kOk, true));

    REQUIRE(testCode(R"(
    bool k13 = 3.1 > 4.1;
    bool k14 = 3.1 < 4.1;
    bool k15 = true && false;
    bool k16 = k13 && k14 && k15;
    bool k19 = k13 && k14 || k15 && k16;
    )", SCCompileResult::kOk, true));

    /* Comment */

    REQUIRE(testCode(R"(
    /* Comment */
    void func1() { }
    )", SCCompileResult::kOk, true));

    REQUIRE(testCode(R"(
    void func2() { return; }
    )", SCCompileResult::kOk, true));

    REQUIRE(testCode(R"(
    void func3(int i, float f, bool b) { { int i; float f; bool b; } }
    )", SCCompileResult::kOk, true));

    REQUIRE(testCode(R"(
    float func4(int i, float f, bool b) { { int i=5; float f=5.0; bool b=false; } return f; }
    )", SCCompileResult::kOk, true));

    REQUIRE(testCode(R"(
    int   func5() { return 5; }
    )", SCCompileResult::kOk, true));

    REQUIRE(testCode(R"(
    float func6() { return 5.0; }
    )", SCCompileResult::kOk, true));

    REQUIRE(testCode(R"(
    bool  func7() { return true; }
    )", SCCompileResult::kOk, true));

    REQUIRE(testCode(R"(
    bool  func8() { return false; }
    )", SCCompileResult::kOk, true));

    REQUIRE(testCode(R"(
    int   func9() { int i=5; return i; }
    )", SCCompileResult::kOk, true));

    REQUIRE(testCode(R"(
    float func10() { float f=5.0; return f; }
    )", SCCompileResult::kOk, true));

    REQUIRE(testCode(R"(
    bool  func11()  { bool b=true; return b; }
    )", SCCompileResult::kOk, true));

    REQUIRE(testCode(R"(
    bool  func12()  { bool b=false; { return b; } }
    )", SCCompileResult::kOk, true));

    REQUIRE(testCode(R"(
    bool  func13(bool bArg)  { return bArg; }
    )", SCCompileResult::kOk, true));

    REQUIRE(testCode(R"(
    bool  func14(bool bArg)  { bool b = bArg; return b; }
    )", SCCompileResult::kOk, true));

    /* Use global variables */

    REQUIRE(testCode(R"(
    /* Use global variables */
    int i;
    int i1 = 1;
    int   func15() { return i; return i1; }
    )", SCCompileResult::kOk, true));

    REQUIRE(testCode(R"(
    float f;
    float f1_ = 1.0;
    float func16() { return f; return f1_; }
    )", SCCompileResult::kOk, true));

    REQUIRE(testCode(R"(
    bool k;
    bool k1 = true;
    bool  func17() { return k; return k1; }
    )", SCCompileResult::kOk, true));

    /* Call function in function */

    REQUIRE(testCode(R"(
    /* Call function in function */
    bool  _func_14_(bool bArg)  { bool b = bArg; return b; }
    void  func18() { _func_14_(false); }
    )", SCCompileResult::kOk, true));

    REQUIRE(testCode(R"(
    bool  func14(bool bArg)  { bool b = bArg; return b; }
    void  func19() { { func14(true); } }
    )", SCCompileResult::kOk, true));

    REQUIRE(testCode(R"(
    int   func9() { int i=5; return i; }
    int   func20() { return func9(); }
    )", SCCompileResult::kOk, true));

    REQUIRE(testCode(R"(
    float func10() { float f=5.0; return f; }
    float func21() { { return func10(); } }
    )", SCCompileResult::kOk, true));

    REQUIRE(testCode(R"(
    int   func9() { int i=5; return i; }
    int   func22() { int i=func9(); return i; }
    )", SCCompileResult::kOk, true));

    REQUIRE(testCode(R"(
    float func10() { float f=5.0; return f; }
    float func23() { float f=func10(); return f; }
    )", SCCompileResult::kOk, true));

    REQUIRE(testCode(R"(
    bool  func13(bool bArg)  { return bArg; }
    bool  func24() { bool b=func13(true); return b; }
    )", SCCompileResult::kOk, true));

    REQUIRE(testCode(R"(
    float func4(int i, float f, bool b) { { int i=5; float f=5.0; bool b=false; } return f; }
    float func25() { return func4((4*5)+2/(2-3)*5, (4.2*5.1)+2.99/(2.10-3.0)*5.0, false); }
    )", SCCompileResult::kOk, true));

    REQUIRE(testCode(R"(
    int   func26() { return (4*5)+2/(2-3)*5; }
    )", SCCompileResult::kOk, true));

    REQUIRE(testCode(R"(
    float func4(int i, float f, bool b) { { int i=5; float f=5.0; bool b=false; } return f; }
    float func27() { return -func4(-5, -4.2, false); }
    )", SCCompileResult::kOk, true));

    REQUIRE(testCode(R"(
    int   func28(int i) { int a=i; if (i == 2) { a=11; return 4; a = 5; return 3; } else { if (i == 3) { return 10; } a = 7; } return a; }
    )", SCCompileResult::kOk, true));

    REQUIRE(testCode(R"(
    bool  func29(float f) { return bool(!f); }
    )", SCCompileResult::kOk, true));

    REQUIRE(testCode(R"(
    bool  func30(int i) { return bool(!i); }
    )", SCCompileResult::kOk, true));

    REQUIRE(testCode(R"(
    bool  func31(bool b) { return !b; }
    )", SCCompileResult::kOk, true));

    REQUIRE(testCode(R"(
    void  func32(int i)  { if (i <= 0) return; func32(i - 1);  }
    )", SCCompileResult::kOk, true));

    REQUIRE(testCode(R"(
    void  func33() { for ( ; ; ) { }  }
    )", SCCompileResult::kOk, true));

    REQUIRE(testCode(R"(
    void  func34() { for (int i,j,k; ; ) { }  }
    )", SCCompileResult::kOk, true));

    REQUIRE(testCode(R"(
    void  func35() { for (int i=0,j=i*2; ; ) { }  }
    )", SCCompileResult::kOk, true));

    REQUIRE(testCode(R"(
    int   func36() { int a; for (int i=0,j=i*2; i < 10; i=j+1, j=j+i) { a = j + i; }  return a; }
    )", SCCompileResult::kOk, true));

    REQUIRE(testCode(R"(
    int   func37() { int a; for (int i=0,j=i*2; i < 10; i=j+1, j=j+i) a = j + i;  return a; }
    )", SCCompileResult::kOk, true));

    REQUIRE(testCode(R"(
    int   func38() { for (int i=0; i < 10; i=i+1) continue;  return 0; }
    )", SCCompileResult::kOk, true));

    REQUIRE(testCode(R"(
    int   func39() { for (int i=0; i < 10; i=i+1) { continue; i=i+1; } return 0; }
    )", SCCompileResult::kOk, true));

    REQUIRE(testCode(R"(
    int   func40() { for (int i=0; i < 10; i=i+1) break;  return 0; }
    )", SCCompileResult::kOk, true));

    REQUIRE(testCode(R"(
    int   func41() { for (int i=0; i < 10; i=i+1) { break; i=i+1; } return 0; }
    )", SCCompileResult::kOk, true));

    REQUIRE(testCode(R"(
    void  func42() { int i=0; while (i < 10) { } }
    )", SCCompileResult::kOk, true));

    REQUIRE(testCode(R"(
    void  func43() { int i=0; while (i < 10) { i=i+1; } }
    )", SCCompileResult::kOk, true));

    REQUIRE(testCode(R"(
    int   func44() { int i=0; while (i < 10) continue;  return 0; }
    )", SCCompileResult::kOk, true));

    REQUIRE(testCode(R"(
    int   func45() { int i=0; while (i < 10) { continue; i=i+1; } return 0; }
    )", SCCompileResult::kOk, true));

    REQUIRE(testCode(R"(
    int   func46() { int i=0; while (i < 10) break; return 0; }
    )", SCCompileResult::kOk, true));

    REQUIRE(testCode(R"(
    int   func47() { int i=0; while (i < 10) { break; i=i+1; } return 0; }
    )", SCCompileResult::kOk, true));

    REQUIRE(testCode(R"(
    void  func48() { int i=0; do { } while (i < 10); }
    )", SCCompileResult::kOk, true));

    REQUIRE(testCode(R"(
    void  func49() { int i=0; do { i=i+1; } while (i < 10); }
    )", SCCompileResult::kOk, true));

    REQUIRE(testCode(R"(
    int   func50() { int i=0; do continue; while (i < 10); return 0; }
    )", SCCompileResult::kOk, true));

    REQUIRE(testCode(R"(
    int   func51() { int i=0; do { continue; i=i+1; } while (i < 10); return 0; }
    )", SCCompileResult::kOk, true));

    REQUIRE(testCode(R"(
    int   func52() { int i=0; do break; while (i < 10); return 0; }
    )", SCCompileResult::kOk, true));

    REQUIRE(testCode(R"(
    int   func53() { int i=0; do { break; i=i+1; } while (i < 10); return 0; }
    )", SCCompileResult::kOk, true));
}

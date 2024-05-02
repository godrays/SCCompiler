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
    REQUIRE(TestCode(R"(
    int i;
    int _i;
    int i_;
    int i_12_;
    )", SCCompileResult::kSCCompileResultOk, true));

    REQUIRE(TestCode(R"(
    int i1 = 1;
    )", SCCompileResult::kSCCompileResultOk, true));

    REQUIRE(TestCode(R"(
    int i2 = (4*5)+2/(2-3)*5;
    )", SCCompileResult::kSCCompileResultOk, true));

    REQUIRE(TestCode(R"(
    int i3 = -4*5;
    )", SCCompileResult::kSCCompileResultOk, true));

    REQUIRE(TestCode(R"(
    int i3 = -4*5;
    int i4 = -i3;
    )", SCCompileResult::kSCCompileResultOk, true));

    REQUIRE(TestCode(R"(
    int i;
    int i5 = ++i;
    )", SCCompileResult::kSCCompileResultOk, true));

    REQUIRE(TestCode(R"(
    int i;
    int i6 = --i;
    )", SCCompileResult::kSCCompileResultOk, true));

    REQUIRE(TestCode(R"(
    float f;
    )", SCCompileResult::kSCCompileResultOk, true));

    REQUIRE(TestCode(R"(
    float f1 = 1.0;
    )", SCCompileResult::kSCCompileResultOk, true));

    REQUIRE(TestCode(R"(
    float f2 = (4.2*5.1)+2.99/(2.10-3.0)*5.0;
    )", SCCompileResult::kSCCompileResultOk, true));

    REQUIRE(TestCode(R"(
    float f3 = -4.2*5.1;
    )", SCCompileResult::kSCCompileResultOk, true));

    REQUIRE(TestCode(R"(
    bool k;
    )", SCCompileResult::kSCCompileResultOk, true));

    REQUIRE(TestCode(R"(
    bool k1 = true;
    )", SCCompileResult::kSCCompileResultOk, true));

    REQUIRE(TestCode(R"(
    bool k2 = false;
    )", SCCompileResult::kSCCompileResultOk, true));

    REQUIRE(TestCode(R"(
    bool k3 = 3 == 4;
    )", SCCompileResult::kSCCompileResultOk, true));

    REQUIRE(TestCode(R"(
    bool k4 = 3 >= 4;
    )", SCCompileResult::kSCCompileResultOk, true));

    REQUIRE(TestCode(R"(
    bool k5 = 3 <= 4;
    )", SCCompileResult::kSCCompileResultOk, true));

    REQUIRE(TestCode(R"(
    bool k6 = 3 != 4;
    )", SCCompileResult::kSCCompileResultOk, true));

    REQUIRE(TestCode(R"(
    bool k7 = 3 > 4;
    )", SCCompileResult::kSCCompileResultOk, true));

    REQUIRE(TestCode(R"(
    bool k8 = 3 < 4;
    )", SCCompileResult::kSCCompileResultOk, true));

    REQUIRE(TestCode(R"(
    bool k9 = 3.1 == 4.1;
    )", SCCompileResult::kSCCompileResultOk, true));

    REQUIRE(TestCode(R"(
    bool k10 = 3.1 >= 4.1;
    )", SCCompileResult::kSCCompileResultOk, true));

    REQUIRE(TestCode(R"(
    bool k11 = 3.1 <= 4.1;
    )", SCCompileResult::kSCCompileResultOk, true));

    REQUIRE(TestCode(R"(
    bool k12 = 3.1 != 4.1;
    )", SCCompileResult::kSCCompileResultOk, true));

    REQUIRE(TestCode(R"(
    bool k13 = 3.1 > 4.1;
    )", SCCompileResult::kSCCompileResultOk, true));

    REQUIRE(TestCode(R"(
    bool k14 = 3.1 < 4.1;
    )", SCCompileResult::kSCCompileResultOk, true));

    REQUIRE(TestCode(R"(
    bool k15 = true && false;
    )", SCCompileResult::kSCCompileResultOk, true));

    REQUIRE(TestCode(R"(
    bool k13 = 3.1 > 4.1;
    bool k14 = 3.1 < 4.1;
    bool k15 = true && false;
    bool k16 = k13 && k14 && k15;
    )", SCCompileResult::kSCCompileResultOk, true));

    REQUIRE(TestCode(R"(
    bool k17 = true || false;
    )", SCCompileResult::kSCCompileResultOk, true));

    REQUIRE(TestCode(R"(
    bool k13 = 3.1 > 4.1;
    bool k14 = 3.1 < 4.1;
    bool k15 = true && false;
    bool k18 = k13 || k14 || k15;
    )", SCCompileResult::kSCCompileResultOk, true));

    REQUIRE(TestCode(R"(
    bool k13 = 3.1 > 4.1;
    bool k14 = 3.1 < 4.1;
    bool k15 = true && false;
    bool k16 = k13 && k14 && k15;
    bool k19 = k13 && k14 || k15 && k16;
    )", SCCompileResult::kSCCompileResultOk, true));

    /* Comment */

    REQUIRE(TestCode(R"(
    /* Comment */
    void func1() { }
    )", SCCompileResult::kSCCompileResultOk, true));

    REQUIRE(TestCode(R"(
    void func2() { return; }
    )", SCCompileResult::kSCCompileResultOk, true));

    REQUIRE(TestCode(R"(
    void func3(int i, float f, bool b) { { int i; float f; bool b; } }
    )", SCCompileResult::kSCCompileResultOk, true));

    REQUIRE(TestCode(R"(
    float func4(int i, float f, bool b) { { int i=5; float f=5.0; bool b=false; } return f; }
    )", SCCompileResult::kSCCompileResultOk, true));

    REQUIRE(TestCode(R"(
    int   func5() { return 5; }
    )", SCCompileResult::kSCCompileResultOk, true));

    REQUIRE(TestCode(R"(
    float func6() { return 5.0; }
    )", SCCompileResult::kSCCompileResultOk, true));

    REQUIRE(TestCode(R"(
    bool  func7() { return true; }
    )", SCCompileResult::kSCCompileResultOk, true));

    REQUIRE(TestCode(R"(
    bool  func8() { return false; }
    )", SCCompileResult::kSCCompileResultOk, true));

    REQUIRE(TestCode(R"(
    int   func9() { int i=5; return i; }
    )", SCCompileResult::kSCCompileResultOk, true));

    REQUIRE(TestCode(R"(
    float func10() { float f=5.0; return f; }
    )", SCCompileResult::kSCCompileResultOk, true));

    REQUIRE(TestCode(R"(
    bool  func11()  { bool b=true; return b; }
    )", SCCompileResult::kSCCompileResultOk, true));

    REQUIRE(TestCode(R"(
    bool  func12()  { bool b=false; { return b; } }
    )", SCCompileResult::kSCCompileResultOk, true));

    REQUIRE(TestCode(R"(
    bool  func13(bool bArg)  { return bArg; }
    )", SCCompileResult::kSCCompileResultOk, true));

    REQUIRE(TestCode(R"(
    bool  func14(bool bArg)  { bool b = bArg; return b; }
    )", SCCompileResult::kSCCompileResultOk, true));

    /* Use global variables */

    REQUIRE(TestCode(R"(
    /* Use global variables */
    int i;
    int i1 = 1;
    int   func15() { return i; return i1; }
    )", SCCompileResult::kSCCompileResultOk, true));

    REQUIRE(TestCode(R"(
    float f;
    float f1_ = 1.0;
    float func16() { return f; return f1_; }
    )", SCCompileResult::kSCCompileResultOk, true));

    REQUIRE(TestCode(R"(
    bool k;
    bool k1 = true;
    bool  func17() { return k; return k1; }
    )", SCCompileResult::kSCCompileResultOk, true));

    /* Call function in function */

    REQUIRE(TestCode(R"(
    /* Call function in function */
    bool  _func_14_(bool bArg)  { bool b = bArg; return b; }
    void  func18() { _func_14_(false); }
    )", SCCompileResult::kSCCompileResultOk, true));

    REQUIRE(TestCode(R"(
    bool  func14(bool bArg)  { bool b = bArg; return b; }
    void  func19() { { func14(true); } }
    )", SCCompileResult::kSCCompileResultOk, true));

    REQUIRE(TestCode(R"(
    int   func9() { int i=5; return i; }
    int   func20() { return func9(); }
    )", SCCompileResult::kSCCompileResultOk, true));

    REQUIRE(TestCode(R"(
    float func10() { float f=5.0; return f; }
    float func21() { { return func10(); } }
    )", SCCompileResult::kSCCompileResultOk, true));

    REQUIRE(TestCode(R"(
    int   func9() { int i=5; return i; }
    int   func22() { int i=func9(); return i; }
    )", SCCompileResult::kSCCompileResultOk, true));

    REQUIRE(TestCode(R"(
    float func10() { float f=5.0; return f; }
    float func23() { float f=func10(); return f; }
    )", SCCompileResult::kSCCompileResultOk, true));

    REQUIRE(TestCode(R"(
    bool  func13(bool bArg)  { return bArg; }
    bool  func24() { bool b=func13(true); return b; }
    )", SCCompileResult::kSCCompileResultOk, true));

    REQUIRE(TestCode(R"(
    float func4(int i, float f, bool b) { { int i=5; float f=5.0; bool b=false; } return f; }
    float func25() { return func4((4*5)+2/(2-3)*5, (4.2*5.1)+2.99/(2.10-3.0)*5.0, false); }
    )", SCCompileResult::kSCCompileResultOk, true));

    REQUIRE(TestCode(R"(
    int   func26() { return (4*5)+2/(2-3)*5; }
    )", SCCompileResult::kSCCompileResultOk, true));

    REQUIRE(TestCode(R"(
    float func4(int i, float f, bool b) { { int i=5; float f=5.0; bool b=false; } return f; }
    float func27() { return -func4(-5, -4.2, false); }
    )", SCCompileResult::kSCCompileResultOk, true));

    REQUIRE(TestCode(R"(
    int   func28(int i) { int a=i; if (i == 2) { a=11; return 4; a = 5; return 3; } else { if (i == 3) { return 10; } a = 7; } return a; }
    )", SCCompileResult::kSCCompileResultOk, true));

    REQUIRE(TestCode(R"(
    bool  func29(float f) { return bool(!f); }
    )", SCCompileResult::kSCCompileResultOk, true));

    REQUIRE(TestCode(R"(
    bool  func30(int i) { return bool(!i); }
    )", SCCompileResult::kSCCompileResultOk, true));

    REQUIRE(TestCode(R"(
    bool  func31(bool b) { return !b; }
    )", SCCompileResult::kSCCompileResultOk, true));

    REQUIRE(TestCode(R"(
    void  func32(int i)  { if (i <= 0) return; func32(i - 1);  }
    )", SCCompileResult::kSCCompileResultOk, true));

    REQUIRE(TestCode(R"(
    void  func33() { for ( ; ; ) { }  }
    )", SCCompileResult::kSCCompileResultOk, true));

    REQUIRE(TestCode(R"(
    void  func34() { for (int i,j,k; ; ) { }  }
    )", SCCompileResult::kSCCompileResultOk, true));

    REQUIRE(TestCode(R"(
    void  func35() { for (int i=0,j=i*2; ; ) { }  }
    )", SCCompileResult::kSCCompileResultOk, true));

    REQUIRE(TestCode(R"(
    int   func36() { int a; for (int i=0,j=i*2; i < 10; i=j+1, j=j+i) { a = j + i; }  return a; }
    )", SCCompileResult::kSCCompileResultOk, true));

    REQUIRE(TestCode(R"(
    int   func37() { int a; for (int i=0,j=i*2; i < 10; i=j+1, j=j+i) a = j + i;  return a; }
    )", SCCompileResult::kSCCompileResultOk, true));

    REQUIRE(TestCode(R"(
    int   func38() { for (int i=0; i < 10; i=i+1) continue;  return 0; }
    )", SCCompileResult::kSCCompileResultOk, true));

    REQUIRE(TestCode(R"(
    int   func39() { for (int i=0; i < 10; i=i+1) { continue; i=i+1; } return 0; }
    )", SCCompileResult::kSCCompileResultOk, true));

    REQUIRE(TestCode(R"(
    int   func40() { for (int i=0; i < 10; i=i+1) break;  return 0; }
    )", SCCompileResult::kSCCompileResultOk, true));

    REQUIRE(TestCode(R"(
    int   func41() { for (int i=0; i < 10; i=i+1) { break; i=i+1; } return 0; }
    )", SCCompileResult::kSCCompileResultOk, true));

    REQUIRE(TestCode(R"(
    void  func42() { int i=0; while (i < 10) { } }
    )", SCCompileResult::kSCCompileResultOk, true));

    REQUIRE(TestCode(R"(
    void  func43() { int i=0; while (i < 10) { i=i+1; } }
    )", SCCompileResult::kSCCompileResultOk, true));

    REQUIRE(TestCode(R"(
    int   func44() { int i=0; while (i < 10) continue;  return 0; }
    )", SCCompileResult::kSCCompileResultOk, true));

    REQUIRE(TestCode(R"(
    int   func45() { int i=0; while (i < 10) { continue; i=i+1; } return 0; }
    )", SCCompileResult::kSCCompileResultOk, true));

    REQUIRE(TestCode(R"(
    int   func46() { int i=0; while (i < 10) break; return 0; }
    )", SCCompileResult::kSCCompileResultOk, true));

    REQUIRE(TestCode(R"(
    int   func47() { int i=0; while (i < 10) { break; i=i+1; } return 0; }
    )", SCCompileResult::kSCCompileResultOk, true));

    REQUIRE(TestCode(R"(
    void  func48() { int i=0; do { } while (i < 10); }
    )", SCCompileResult::kSCCompileResultOk, true));

    REQUIRE(TestCode(R"(
    void  func49() { int i=0; do { i=i+1; } while (i < 10); }
    )", SCCompileResult::kSCCompileResultOk, true));

    REQUIRE(TestCode(R"(
    int   func50() { int i=0; do continue; while (i < 10); return 0; }
    )", SCCompileResult::kSCCompileResultOk, true));

    REQUIRE(TestCode(R"(
    int   func51() { int i=0; do { continue; i=i+1; } while (i < 10); return 0; }
    )", SCCompileResult::kSCCompileResultOk, true));

    REQUIRE(TestCode(R"(
    int   func52() { int i=0; do break; while (i < 10); return 0; }
    )", SCCompileResult::kSCCompileResultOk, true));

    REQUIRE(TestCode(R"(
    int   func53() { int i=0; do { break; i=i+1; } while (i < 10); return 0; }
    )", SCCompileResult::kSCCompileResultOk, true));
}

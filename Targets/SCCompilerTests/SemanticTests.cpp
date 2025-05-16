//
//  Created by Arkin Terli on 4/18/18.
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


TEST_CASE("SemanticUndeclaredIdentifierTest", "[SemanticTests]")
{
    // Compiler must fail in use of an undeclared identifier.

    REQUIRE(testCode(R"(
    void func() { i=5; }
    )", SCCompileResult::kSCCompileResultSemanticError, true));

    REQUIRE(testCode(R"(
    void func() { f=5.0; }
    )", SCCompileResult::kSCCompileResultSemanticError, true));

    REQUIRE(testCode(R"(
    void func() { b=true; }
    )", SCCompileResult::kSCCompileResultSemanticError, true));

    REQUIRE(testCode(R"(
    void func() { func2(); }
    )", SCCompileResult::kSCCompileResultSemanticError, true));

    REQUIRE(testCode(R"(
    void func() { func2(); }  void func2() { }
    )", SCCompileResult::kSCCompileResultSemanticError, true));

    REQUIRE(testCode(R"(
    int func() { return i; }  int i;
    )", SCCompileResult::kSCCompileResultSemanticError, true));
}


TEST_CASE("SemanticTypeMismatchTest", "[SemanticTests]")
{
    // Compiler must fails for mismathed type use.

    REQUIRE(testCode(R"(
    int i = 5 * false;
    )", SCCompileResult::kSCCompileResultSemanticError, true));

    REQUIRE(testCode(R"(
    float f = 5.0 * true;
    )", SCCompileResult::kSCCompileResultSemanticError, true));

    REQUIRE(testCode(R"(
    int i = 5.0;
    )", SCCompileResult::kSCCompileResultSemanticError, true));

    // Parameter type does not match.
    REQUIRE(testCode(R"(
    void func(int i) { }
    void func2() { func(1.1); }
    )", SCCompileResult::kSCCompileResultSemanticError, true));

    // Function return type should match with return value type.
    REQUIRE(testCode(R"(
    float func() { return 1.0; }
    float func1() { { return 1.0; } }
    float func2() { { { return 1.0; } } }
    void  func3() { return; }
    void  func4() { { return; } }
    )", SCCompileResult::kSCCompileResultOk, true));

    REQUIRE(testCode(R"(
    void  func()  { return 1.0; }
    float func1() { return; }
    )", SCCompileResult::kSCCompileResultSemanticError, true));
}


TEST_CASE("SemanticNonSpecificTest", "[SemanticTests]")
{
    // Function with return type must have at least one return statement.

    REQUIRE(testCode(R"(
    float  func()  {  }
    )", SCCompileResult::kSCCompileResultSemanticError, true));
}


TEST_CASE("SemanticUnaryOPTest", "[SemanticTests]")
{
    REQUIRE(testCode(R"(
    bool   func()  { return -true; }
    )", SCCompileResult::kSCCompileResultSemanticError, true));

    REQUIRE(testCode(R"(
    bool   func(bool b)  { return -b; }
    )", SCCompileResult::kSCCompileResultSemanticError, true));
}


TEST_CASE("SemanticContinueStatementTest", "[SemanticTests]")
{
    // Continue statement is allowed only in loops.
    REQUIRE(testCode(R"(
    void   func()  { continue; }
    )", SCCompileResult::kSCCompileResultSemanticError, true));
}


TEST_CASE("SemanticBreakStatementTest", "[SemanticTests]")
{
    // Break statement is allowed only in loops.
    REQUIRE(testCode(R"(
    void   func()  { break; }
    )", SCCompileResult::kSCCompileResultSemanticError, true));
}

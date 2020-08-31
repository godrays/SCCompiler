//
//  SemanticTests.cpp
//  SCC
//
//  Created by Arkin Terli on 4/18/18.
//  Copyright © 2018-Present, Arkin Terli. All rights reserved.
//

#include <iostream>
#include <string>

#include <catch.hpp>

#include <Compiler.hpp>
#include "TestUtils.hpp"

using namespace scc;


TEST_CASE("SemanticUndeclaredIdentifierTest", "[SemanticTests]")
{
    // Compiler must fails in use of an undeclared identifier.

    REQUIRE(TestCode("\
    void func() { i=5; }     \n\
    ", SCCompileResult::kSCCompileResultSemanticError, true));

    REQUIRE(TestCode("\
    void func() { f=5.0; }     \n\
    ", SCCompileResult::kSCCompileResultSemanticError, true));

    REQUIRE(TestCode("\
    void func() { b=true; }     \n\
    ", SCCompileResult::kSCCompileResultSemanticError, true));

    REQUIRE(TestCode("\
    void func() { func2(); }     \n\
    ", SCCompileResult::kSCCompileResultSemanticError, true));

    REQUIRE(TestCode("\
    void func() { func2(); }  void func2() { }   \n\
    ", SCCompileResult::kSCCompileResultSemanticError, true));

    REQUIRE(TestCode("\
    int func() { return i; }  int i;   \n\
    ", SCCompileResult::kSCCompileResultSemanticError, true));
}


TEST_CASE("SemanticTypeMismatchTest", "[SemanticTests]")
{
    // Compiler must fails for mismathed type use.

    REQUIRE(TestCode("\
    int i = 5 * false;        \n\
    ", SCCompileResult::kSCCompileResultSemanticError, true));

    REQUIRE(TestCode("\
    float f = 5.0 * true;     \n\
    ", SCCompileResult::kSCCompileResultSemanticError, true));

    REQUIRE(TestCode("\
    int i = 5.0;              \n\
    ", SCCompileResult::kSCCompileResultSemanticError, true));

    // Parameter type does not match.
    REQUIRE(TestCode("\
    void func(int i) { }    \n\
    void func2() { func(1.1); }    \n\
    ", SCCompileResult::kSCCompileResultSemanticError, true));

    // Function return type should match with return value type.
    REQUIRE(TestCode("\
    float func() { return 1.0; }            \n\
    float func1() { { return 1.0; } }       \n\
    float func2() { { { return 1.0; } } }   \n\
    void  func3() { return; }               \n\
    void  func4() { { return; } }           \n\
    ", SCCompileResult::kSCCompileResultOk, true));

    REQUIRE(TestCode("\
    void  func()  { return 1.0; }    \n\
    float func1() { return; }        \n\
    ", SCCompileResult::kSCCompileResultSemanticError, true));
}


TEST_CASE("SemanticNonSpecificTest", "[SemanticTests]")
{
    // Function with return type must have at least one return statement.

    REQUIRE(TestCode("\
    float  func()  {  }    \n\
    ", SCCompileResult::kSCCompileResultSemanticError, true));
}


TEST_CASE("SemanticUnaryOPTest", "[SemanticTests]")
{
    REQUIRE(TestCode("\
    bool   func()  { return -true; }       \n\
    ", SCCompileResult::kSCCompileResultSemanticError, true));

    REQUIRE(TestCode("\
    bool   func(bool b)  { return -b; }    \n\
    ", SCCompileResult::kSCCompileResultSemanticError, true));
}


TEST_CASE("SemanticContinueStatementTest", "[SemanticTests]")
{
    // Continue statement is allowed only in loops.
    REQUIRE(TestCode("\
    void   func()  { continue; }           \n\
    ", SCCompileResult::kSCCompileResultSemanticError, true));
}


TEST_CASE("SemanticBreakStatementTest", "[SemanticTests]")
{
    // Break statement is allowed only in loops.
    REQUIRE(TestCode("\
    void   func()  { break; }              \n\
    ", SCCompileResult::kSCCompileResultSemanticError, true));
}

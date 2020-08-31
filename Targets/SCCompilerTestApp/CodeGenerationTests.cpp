//
//  CodeGenerationTests.cpp
//
//  Created by Arkin Terli on 5/8/18.
//  Copyright © 2018-Present, Arkin Terli. All rights reserved.
//

#include <limits>
#include <string>

#include <catch2/catch.hpp>

#include <Compiler.hpp>


using namespace scc;


TEST_CASE("CodeGenerationExplicitTypeConversionTests", "[CodeGenerationTests]")
{
    Compiler compiler;
    SCCompileResult compileResult;

    std::string testCode = "\
    /* Float Conversions */                            \
    bool  FloatToBool(float f)   { return bool(f);  }  \
    int   FloatToInt(float f)    { return int(f);   }  \
    float FloatToFloat(float f)  { return float(f); }  \
    /* Int Conversions */                              \
    bool  IntToBool(int i)       { return bool(i);  }  \
    int   IntToInt(int i)        { return int(i);   }  \
    float IntToFloat(int i)      { return float(i); }  \
    /* Bool Conversions */                             \
    bool  BoolToBool(bool b)     { return bool(b);  }  \
    int   BoolToInt(bool b)      { return int(b);   }  \
    float BoolToFloat(bool b)    { return float(b); }  \
    ";
    auto scModule = compiler.CompileFromMemory(testCode, compileResult);

    SECTION("Should compile without an issue.")
    {
        REQUIRE(compileResult == scc::SCCompileResult::kSCCompileResultOk);
        REQUIRE(scModule != nullptr);
    }
    
    // FLOAT CONVERSIONS -----------------------------------

    SECTION("FLOAT to BOOL conversions")
    {
        using FuncFloatToBool = bool (*)(float);
        auto FloatToBool = reinterpret_cast<FuncFloatToBool>(scModule->GetFunctionPtr("FloatToBool"));

        REQUIRE(FloatToBool(0.0f) == false);
        REQUIRE(FloatToBool(1.0f) == true);
        REQUIRE(FloatToBool(-1.0f) == true);
        REQUIRE(FloatToBool(std::numeric_limits<float>::max()) == true);
        REQUIRE(FloatToBool(std::numeric_limits<float>::min()) == true);
    }

    SECTION("FLOAT to INT conversions")
    {
        using FuncFloatToInt = int (*)(float);
        auto FloatToInt = reinterpret_cast<FuncFloatToInt>(scModule->GetFunctionPtr("FloatToInt"));

        REQUIRE(FloatToInt(0.0f) == 0);
        REQUIRE(FloatToInt(1.5f) == 1);
        REQUIRE(FloatToInt(-1.5f) == -1);
        REQUIRE(FloatToInt(std::numeric_limits<float>::min()) == int(std::numeric_limits<float>::min()));
        // According to C++ standards, int(FLT_MAX) has undefined behaviour. Not a valid test.
        // REQUIRE(FloatToInt(std::numeric_limits<float>::max()) == int(std::numeric_limits<float>::max()));
    }

    SECTION("FLOAT to FLOAT conversions")
    {
        using FuncFloatToFloat = float (*)(float);
        auto FloatToFloat = reinterpret_cast<FuncFloatToFloat>(scModule->GetFunctionPtr("FloatToFloat"));

        REQUIRE(FloatToFloat(0.0f) == 0.0f);
        REQUIRE(FloatToFloat(1.5f) == 1.5f);
        REQUIRE(FloatToFloat(-1.5f) == -1.5f);
        REQUIRE(FloatToFloat(std::numeric_limits<float>::max()) == std::numeric_limits<float>::max());
        REQUIRE(FloatToFloat(std::numeric_limits<float>::min()) == std::numeric_limits<float>::min());
    }

    // INT CONVERSIONS -----------------------------------

    SECTION("INT to BOOL conversions")
    {
        using FuncIntToBool = bool (*)(int);
        auto IntToBool = reinterpret_cast<FuncIntToBool>(scModule->GetFunctionPtr("IntToBool"));

        REQUIRE(IntToBool(0) == false);
        REQUIRE(IntToBool(1) == true);
        REQUIRE(IntToBool(-1) == true);
        REQUIRE(IntToBool(std::numeric_limits<int>::max()) == bool(std::numeric_limits<int>::max()));
        REQUIRE(IntToBool(std::numeric_limits<int>::min()) == bool(std::numeric_limits<int>::min()));
    }

    SECTION("INT to INT conversions")
    {
        using FuncIntToInt = int (*)(int);
        auto IntToInt = reinterpret_cast<FuncIntToInt>(scModule->GetFunctionPtr("IntToInt"));

        REQUIRE(IntToInt(0) == 0);
        REQUIRE(IntToInt(1) == 1);
        REQUIRE(IntToInt(-1) == -1);
        REQUIRE(IntToInt(std::numeric_limits<int>::max()) == std::numeric_limits<int>::max());
        REQUIRE(IntToInt(std::numeric_limits<int>::min()) == std::numeric_limits<int>::min());
    }

    SECTION("INT to FLOAT conversions")
    {
        using FuncIntToFloat = float (*)(int);
        auto IntToFloat = reinterpret_cast<FuncIntToFloat>(scModule->GetFunctionPtr("IntToFloat"));

        REQUIRE(IntToFloat(0) == 0.0f);
        REQUIRE(IntToFloat(1) == 1.0f);
        REQUIRE(IntToFloat(-1) == -1.0f);
        REQUIRE(IntToFloat(std::numeric_limits<int>::max()) == float(std::numeric_limits<int>::max()));
        REQUIRE(IntToFloat(std::numeric_limits<int>::min()) == float(std::numeric_limits<int>::min()));
    }

    // BOOL CONVERSIONS -----------------------------------

    SECTION("BOOL to BOOL conversions")
    {
        using FuncBoolToBool = bool (*)(bool);
        auto BoolToBool = reinterpret_cast<FuncBoolToBool>(scModule->GetFunctionPtr("BoolToBool"));

        REQUIRE(BoolToBool(false) == false);
        REQUIRE(BoolToBool(true) == true);
    }

    SECTION("BOOL to INT conversions")
    {
        using FuncBoolToInt = int (*)(bool);
        auto BoolToInt = reinterpret_cast<FuncBoolToInt>(scModule->GetFunctionPtr("BoolToInt"));

        REQUIRE(BoolToInt(false) == 0);
        REQUIRE(BoolToInt(true) == 1);
    }

    SECTION("BOOL to FLOAT conversions")
    {
        using FuncBoolToFloat = float (*)(bool);
        auto BoolToFloat = reinterpret_cast<FuncBoolToFloat>(scModule->GetFunctionPtr("BoolToFloat"));

        REQUIRE(BoolToFloat(false) == 0.0f);
        REQUIRE(BoolToFloat(true) == 1.0f);
    }

    delete scModule;
}


TEST_CASE("CodeGenerationUnaryOPTests", "[CodeGenerationTests]")
{
    Compiler compiler;
    SCCompileResult compileResult;

    std::string testCode = "\
    float NegFloat(float f) { return -f;  }       \
    float PosFloat(float f) { return +f;  }       \
    int   NegInt(int i)     { return -i;  }       \
    int   PosInt(int i)     { return +i;  }       \
    ";
    auto scModule = compiler.CompileFromMemory(testCode, compileResult);

    SECTION("Should compile without an issue.")
    {
        REQUIRE(compileResult == scc::SCCompileResult::kSCCompileResultOk);
        REQUIRE(scModule != nullptr);
    }

    // FLOAT

    SECTION("Negative Float")
    {
        using FuncNegFloat = float (*)(float);
        auto NegFloat = reinterpret_cast<FuncNegFloat>(scModule->GetFunctionPtr("NegFloat"));

        REQUIRE(NegFloat(0.0f) == 0.0f);
        REQUIRE(NegFloat(-1.123456f) == 1.123456f);
        REQUIRE(NegFloat(1.123456f) == -1.123456f);
        REQUIRE(NegFloat(std::numeric_limits<float>::max()) == -std::numeric_limits<float>::max());
        REQUIRE(NegFloat(std::numeric_limits<float>::min()) == -std::numeric_limits<float>::min());
    }

    SECTION("Positive Float")
    {
        using FuncPosFloat = float (*)(float);
        auto PosFloat = reinterpret_cast<FuncPosFloat>(scModule->GetFunctionPtr("PosFloat"));

        REQUIRE(PosFloat(0.0f) == 0.0f);
        REQUIRE(PosFloat(1.123456f) == 1.123456f);
        REQUIRE(PosFloat(-1.123456f) == -1.123456f);
        REQUIRE(PosFloat(std::numeric_limits<float>::max()) == std::numeric_limits<float>::max());
        REQUIRE(PosFloat(std::numeric_limits<float>::min()) == std::numeric_limits<float>::min());
        REQUIRE(PosFloat(-std::numeric_limits<float>::max()) == -std::numeric_limits<float>::max());
        REQUIRE(PosFloat(-std::numeric_limits<float>::min()) == -std::numeric_limits<float>::min());
    }

    // INT

    SECTION("Negative Integer")
    {
        using FuncNegInt = int (*)(int);
        auto NegInt = reinterpret_cast<FuncNegInt>(scModule->GetFunctionPtr("NegInt"));

        REQUIRE(NegInt(0.0f) == 0.0f);
        REQUIRE(NegInt(-1) == 1);
        REQUIRE(NegInt(1) == -1);
        REQUIRE(NegInt(std::numeric_limits<int>::max()) == -std::numeric_limits<int>::max());
        REQUIRE(NegInt(std::numeric_limits<int>::min()) == -std::numeric_limits<int>::min());
    }

    SECTION("Positive Integer")
    {
        using FuncPosInt = int (*)(int);
        auto PosInt = reinterpret_cast<FuncPosInt>(scModule->GetFunctionPtr("PosInt"));

        REQUIRE(PosInt(0.0f) == 0.0f);
        REQUIRE(PosInt(1) == 1);
        REQUIRE(PosInt(-1) == -1);
        REQUIRE(PosInt(std::numeric_limits<int>::max()) == std::numeric_limits<int>::max());
        REQUIRE(PosInt(std::numeric_limits<int>::min()) == std::numeric_limits<int>::min());
        REQUIRE(PosInt(-std::numeric_limits<int>::max()) == -std::numeric_limits<int>::max());
        REQUIRE(PosInt(-std::numeric_limits<int>::min()) == -std::numeric_limits<int>::min());
    }

    delete scModule;
}


TEST_CASE("CodeGenerationComparisonOPTests", "[CodeGenerationTests]")
{
    Compiler compiler;
    SCCompileResult compileResult;

    std::string testCode = "\
    bool FloatCmpEQ(float a, float b)  { return a == b;  }       \
    bool FloatCmpNEQ(float a, float b) { return a != b;  }       \
    bool FloatCmpLE(float a, float b)  { return a <= b;  }       \
    bool FloatCmpGE(float a, float b)  { return a >= b;  }       \
    bool FloatCmpL(float a, float b)   { return a < b;  }        \
    bool FloatCmpG(float a, float b)   { return a > b;  }        \
    ";
    auto scModule = compiler.CompileFromMemory(testCode, compileResult);

    SECTION("Should compile without an issue.")
    {
        REQUIRE(compileResult == scc::SCCompileResult::kSCCompileResultOk);
        REQUIRE(scModule != nullptr);
    }

    auto fmax = std::numeric_limits<float>::max();
    auto fmin = std::numeric_limits<float>::min();

    // FLOAT
    using FuncFloatCmp = bool (*)(float, float);

    auto FloatCmp = reinterpret_cast<FuncFloatCmp>(scModule->GetFunctionPtr("FloatCmpEQ"));
    REQUIRE(FloatCmp(0.0f, 0.0f) == true);
    REQUIRE(FloatCmp(-0.0f, 0.0f) == true);
    REQUIRE(FloatCmp(1.12f, 1.12f) == true);
    REQUIRE(FloatCmp(1.12f, -1.12f) == false);
    REQUIRE(FloatCmp(-1.0f, 1.0f) == false);
    REQUIRE(FloatCmp(fmax, fmax) == true);
    REQUIRE(FloatCmp(fmin, fmin) == true);

    FloatCmp = reinterpret_cast<FuncFloatCmp>(scModule->GetFunctionPtr("FloatCmpNEQ"));
    REQUIRE(FloatCmp(0.0f, 0.0f) == false);
    REQUIRE(FloatCmp(-0.0f, 0.0f) == false);
    REQUIRE(FloatCmp(1.12f, 1.12f) == false);
    REQUIRE(FloatCmp(1.12f, -1.12f) == true);
    REQUIRE(FloatCmp(-1.0f, 1.0f) == true);
    REQUIRE(FloatCmp(fmax, fmax) == false);
    REQUIRE(FloatCmp(fmin, fmin) == false);

    FloatCmp = reinterpret_cast<FuncFloatCmp>(scModule->GetFunctionPtr("FloatCmpLE"));
    REQUIRE(FloatCmp(0.0f, 0.0f) == true);
    REQUIRE(FloatCmp(-0.0f, 0.0f) == true);
    REQUIRE(FloatCmp(1.12f, 1.12f) == true);
    REQUIRE(FloatCmp(1.11f, 1.12f) == true);
    REQUIRE(FloatCmp(-1.0f, 1.0f) == true);
    REQUIRE(FloatCmp(fmax, fmax) == true);
    REQUIRE(FloatCmp(fmin, fmax) == true);
    REQUIRE(FloatCmp(fmax, fmin) == false);
    REQUIRE(FloatCmp(fmin, fmin) == true);

    FloatCmp = reinterpret_cast<FuncFloatCmp>(scModule->GetFunctionPtr("FloatCmpGE"));
    REQUIRE(FloatCmp(0.0f, 0.0f) == true);
    REQUIRE(FloatCmp(-0.0f, 0.0f) == true);
    REQUIRE(FloatCmp(1.12f, 1.12f) == true);
    REQUIRE(FloatCmp(1.11f, 1.12f) == false);
    REQUIRE(FloatCmp(-1.0f, 1.0f) == false);
    REQUIRE(FloatCmp(fmax, fmax) == true);
    REQUIRE(FloatCmp(fmin, fmax) == false);
    REQUIRE(FloatCmp(fmax, fmin) == true);
    REQUIRE(FloatCmp(fmin, fmin) == true);

    FloatCmp = reinterpret_cast<FuncFloatCmp>(scModule->GetFunctionPtr("FloatCmpL"));
    REQUIRE(FloatCmp(0.0f, 0.0f) == false);
    REQUIRE(FloatCmp(-0.0f, 0.0f) == false);
    REQUIRE(FloatCmp(1.12f, 1.12f) == false);
    REQUIRE(FloatCmp(1.11f, 1.12f) == true);
    REQUIRE(FloatCmp(-1.0f, 1.0f) == true);
    REQUIRE(FloatCmp(fmax, fmax) == false);
    REQUIRE(FloatCmp(fmin, fmax) == true);
    REQUIRE(FloatCmp(fmax, fmin) == false);
    REQUIRE(FloatCmp(fmin, fmin) == false);

    FloatCmp = reinterpret_cast<FuncFloatCmp>(scModule->GetFunctionPtr("FloatCmpG"));
    REQUIRE(FloatCmp(0.0f, 0.0f) == false);
    REQUIRE(FloatCmp(-0.0f, 0.0f) == false);
    REQUIRE(FloatCmp(1.12f, 1.12f) == false);
    REQUIRE(FloatCmp(1.11f, 1.12f) == false);
    REQUIRE(FloatCmp(-1.0f, 1.0f) == false);
    REQUIRE(FloatCmp(fmax, fmax) == false);
    REQUIRE(FloatCmp(fmin, fmax) == false);
    REQUIRE(FloatCmp(fmax, fmin) == true);
    REQUIRE(FloatCmp(fmin, fmin) == false);

    delete scModule;
}


TEST_CASE("CodeGenerationIfStatementTests", "[CodeGenerationTests]")
{
    Compiler compiler;
    SCCompileResult compileResult;

    std::string testCode = "\
    int IfTest1(bool b1) { int a=-1; if (b1) { return 1; } return a; }                                                  \n\
    int IfTest2(bool b1, bool b2) { int a=-1; if (b1) { return 1; } else { if (b2) { return 2; } a = 3; } return a; }   \n\
    int IfTest3(bool b1) { int a=-1; if (b1) { } else { } return a; }                                                   \n\
    int IfTest4(bool b1) { int a=-1; if (b1) { a=1; } else { a=2; } return a; }                                         \n\
    ";
    auto scModule = compiler.CompileFromMemory(testCode, compileResult);

    REQUIRE(compileResult == scc::SCCompileResult::kSCCompileResultOk);
    REQUIRE(scModule != nullptr);

    using FuncIfTest1 = int (*)(bool);
    auto IfTest1 = reinterpret_cast<FuncIfTest1>(scModule->GetFunctionPtr("IfTest1"));
    REQUIRE(IfTest1(true)  == 1);
    REQUIRE(IfTest1(false) == -1);

    using FuncIfTest2 = int (*)(bool, bool);
    auto IfTest2 = reinterpret_cast<FuncIfTest2>(scModule->GetFunctionPtr("IfTest2"));
    REQUIRE(IfTest2(true, false)  == 1);
    REQUIRE(IfTest2(false, true)  == 2);
    REQUIRE(IfTest2(false, false) == 3);

    using FuncIfTest3 = int (*)(bool);
    auto IfTest3 = reinterpret_cast<FuncIfTest3>(scModule->GetFunctionPtr("IfTest3"));
    REQUIRE(IfTest3(true) == -1);
    REQUIRE(IfTest3(true) == -1);

    using FuncIfTest4 = int (*)(bool);
    auto IfTest4 = reinterpret_cast<FuncIfTest4>(scModule->GetFunctionPtr("IfTest4"));
    REQUIRE(IfTest4(true) == 1);
    REQUIRE(IfTest4(false) == 2);

    delete scModule;
}


TEST_CASE("CodeGenerationLogicalNotOPTests", "[CodeGenerationTests]")
{
    Compiler compiler;
    SCCompileResult compileResult;

    std::string testCode = "\
    bool FloatNot(float f) { return bool(!f); }         \n\
    bool IntNot(int i)     { return bool(!i); }         \n\
    bool BoolNot(bool b)   { return !b; }               \n\
    ";
    auto scModule = compiler.CompileFromMemory(testCode, compileResult);

    REQUIRE(compileResult == scc::SCCompileResult::kSCCompileResultOk);
    REQUIRE(scModule != nullptr);

    auto fmax = std::numeric_limits<float>::max();
    auto fmin = std::numeric_limits<float>::min();

    auto imax = std::numeric_limits<int>::max();
    auto imin = std::numeric_limits<int>::min();

    // Float Logical Not Tests
    using FuncFloatNot = bool (*)(float);
    auto FloatNot = reinterpret_cast<FuncFloatNot>(scModule->GetFunctionPtr("FloatNot"));
    REQUIRE(FloatNot(0.0f) == !bool(0.0f));
    REQUIRE(FloatNot(-0.0f) == !bool(-0.0f));
    REQUIRE(FloatNot(1.12f) == !bool(1.12f));
    REQUIRE(FloatNot(-1.12f) == !bool(-1.12f));
    REQUIRE(FloatNot(fmax) == bool(!fmax));
    REQUIRE(FloatNot(fmin) == bool(!fmin));
    
    // Integer Logical Not Tests
    using FuncIntNot = bool (*)(int);
    auto IntNot = reinterpret_cast<FuncIntNot>(scModule->GetFunctionPtr("IntNot"));
    REQUIRE(IntNot(0) == bool(!0));
    REQUIRE(IntNot(-0) == bool(!-0));
    REQUIRE(IntNot(1) == bool(!1));
    REQUIRE(IntNot(-1) == bool(!-1));
    REQUIRE(IntNot(imax) == bool(!imax));
    REQUIRE(IntNot(imin) == bool(!imin));

    // Bool Logical Not Tests
    using FuncBoolNot = bool (*)(bool);
    auto BoolNot = reinterpret_cast<FuncBoolNot>(scModule->GetFunctionPtr("BoolNot"));
    REQUIRE(BoolNot(true) == false);
    REQUIRE(BoolNot(false) == true);

    delete scModule;
}


TEST_CASE("CodeGenerationLogicalOPTests", "[CodeGenerationTests]")
{
    Compiler compiler;
    SCCompileResult compileResult;

    std::string testCode = "\
    bool AndTest1(bool a, bool b)  { return a && b; }                \n\
    bool AndTest2(bool a, bool b, bool c) { return a && b && c; }    \n\
    bool OrTest1(bool a, bool b)   { return a || b; }                \n\
    bool OrTest2(bool a, bool b, bool c)  { return a || b || c; }    \n\
    bool AndOrTest1(bool a, bool b, bool c, bool d) { return a && b || c && d; }    \n\
    ";
    auto scModule = compiler.CompileFromMemory(testCode, compileResult);

    REQUIRE(compileResult == scc::SCCompileResult::kSCCompileResultOk);
    REQUIRE(scModule != nullptr);

    // AND Tests
    using FuncAndTest1 = bool (*)(bool, bool);
    auto AndTest1 = reinterpret_cast<FuncAndTest1>(scModule->GetFunctionPtr("AndTest1"));
    REQUIRE(AndTest1(true, true) == true);
    REQUIRE(AndTest1(true, false) == false);
    REQUIRE(AndTest1(false, true) == false);
    REQUIRE(AndTest1(false, false) == false);

    using FuncAndTest2 = bool (*)(bool, bool, bool);
    auto AndTest2 = reinterpret_cast<FuncAndTest2>(scModule->GetFunctionPtr("AndTest2"));
    REQUIRE(AndTest2(true, true, true) == true);
    REQUIRE(AndTest2(true, true, false) == false);
    REQUIRE(AndTest2(true, false, true) == false);
    REQUIRE(AndTest2(true, false, false) == false);
    REQUIRE(AndTest2(false, true, true) == false);

    // OR Tests
    using FuncOrTest1 = bool (*)(bool, bool);
    auto OrTest1 = reinterpret_cast<FuncOrTest1>(scModule->GetFunctionPtr("OrTest1"));
    REQUIRE(OrTest1(true, true) == true);
    REQUIRE(OrTest1(true, false) == true);
    REQUIRE(OrTest1(false, true) == true);
    REQUIRE(OrTest1(false, false) == false);

    using FuncOrTest2 = bool (*)(bool, bool, bool);
    auto OrTest2 = reinterpret_cast<FuncOrTest2>(scModule->GetFunctionPtr("OrTest2"));
    REQUIRE(OrTest2(true, true, true) == true);
    REQUIRE(OrTest2(true, true, false) == true);
    REQUIRE(OrTest2(false, true, false) == true);
    REQUIRE(OrTest2(false, false, true) == true);
    REQUIRE(OrTest2(false, false, false) == false);

    using FuncAndOrTest1 = bool (*)(bool, bool, bool, bool);
    auto AndOrTest1 = reinterpret_cast<FuncAndOrTest1>(scModule->GetFunctionPtr("AndOrTest1"));
    REQUIRE(AndOrTest1(false, false, true, true) == true);
    REQUIRE(AndOrTest1(false, false, false, false) == false);

    // TODO: In 'expr || expr' case, if left expr result is true, code for right expr should not run.
    // Currently, it doesn't, but need to add tests to cover these cases.

    delete scModule;
}


TEST_CASE("CodeGenerationRecursiveCallTests", "[CodeGenerationTests]")
{
    Compiler compiler;
    SCCompileResult compileResult;

    std::string testCode = "\
    int counter = 0;                                                                            \n\
    int GetCounter() { return counter; }                                                        \n\
    void RecursiveCall(int i) { if (i > 0) { RecursiveCall(i - 1); counter = counter + 1; } }   \n\
    int Fibonacci(int n) { if (n == 0) return n; else if (n == 1) return n; return Fibonacci(n-1) + Fibonacci(n-2); }   \n\
    ";
    auto scModule = compiler.CompileFromMemory(testCode, compileResult);

    REQUIRE(compileResult == scc::SCCompileResult::kSCCompileResultOk);
    REQUIRE(scModule != nullptr);

    // Recursice function call tests.
    using FuncRecursiveCall = void (*)(int);
    auto RecursiveCall = reinterpret_cast<FuncRecursiveCall>(scModule->GetFunctionPtr("RecursiveCall"));

    using FuncGetCounter = int (*)();
    auto GetCounter = reinterpret_cast<FuncGetCounter>(scModule->GetFunctionPtr("GetCounter"));

    int callCount= 10;
    RecursiveCall(callCount);
    REQUIRE(GetCounter() == callCount);

    using FuncFibonacci = int (*)(int);
    auto Fibonacci = reinterpret_cast<FuncFibonacci>(scModule->GetFunctionPtr("Fibonacci"));
    REQUIRE(Fibonacci(10) == 55);

    delete scModule;
}


TEST_CASE("CodeGenerationForStatementTests", "[CodeGenerationTests]")
{
    Compiler compiler;
    SCCompileResult compileResult;

    std::string testCode = "\
    int Test1(int a)   { for (int i=0; i<5; i=i+1) { a = i; } return a; }                    \n\
    int Test2(int a)   { for (int i=0,j=1; i<5; i=i+1, j=j+1) { a = j; } return a; }         \n\
    int Test3(int a, bool b)   { for (; b; ) { a = a+1; b=false; } return a; }               \n\
    int Test4(int a)   { for (int i=0; i<5; i=i+1) a = i; return a; }                        \n\
    int Test5(int a, bool b)   { for (; b; ) a = a+1; return a; }                            \n\
    int Test6(int a)   { for (int i=0; i<5; i=i+1) { a=i; continue; a=-1; } return a; }      \n\
    int Test7(int a)   { for (int i=0; i<5; i=i+1) { a=i; if (true){ continue; } a=-1; } return a; }   \n\
    int Test8(int a)   { for (int i=0; i<5; i=i+1) { a=i; break; a=-1; } return a; }                   \n\
    int Test9(int a)   { for (int i=0; i<5; i=i+1) { a=i; if (i==2){ break; } a=-1; } return a; }      \n\
    int Test10(int a)  { for (int i=0; i<5; i=i+1) { a=i; for (int j=0; j<5; j=j+1) { break; a=-1; } } return a; }    \n\
    ";
    auto scModule = compiler.CompileFromMemory(testCode, compileResult);

    REQUIRE(compileResult == scc::SCCompileResult::kSCCompileResultOk);
    REQUIRE(scModule != nullptr);

    using FuncTest1 = int (*)(int);
    auto Test1 = reinterpret_cast<FuncTest1>(scModule->GetFunctionPtr("Test1"));
    REQUIRE(Test1(5) == 4);

    using FuncTest2 = int (*)(int);
    auto Test2 = reinterpret_cast<FuncTest2>(scModule->GetFunctionPtr("Test2"));
    REQUIRE(Test2(5) == 5);

    using FuncTest3 = int (*)(int, bool);
    auto Test3 = reinterpret_cast<FuncTest3>(scModule->GetFunctionPtr("Test3"));
    REQUIRE(Test3(5, false) == 5);
    REQUIRE(Test3(5, true) == 6);

    using FuncTest4 = int (*)(int);
    auto Test4 = reinterpret_cast<FuncTest4>(scModule->GetFunctionPtr("Test4"));
    REQUIRE(Test4(5) == 4);

    using FuncTest5 = int (*)(int, bool);
    auto Test5 = reinterpret_cast<FuncTest5>(scModule->GetFunctionPtr("Test5"));
    REQUIRE(Test5(5, false) == 5);

    using FuncTest6 = int (*)(int);
    auto Test6 = reinterpret_cast<FuncTest6>(scModule->GetFunctionPtr("Test6"));
    REQUIRE(Test6(5) == 4);

    using FuncTest7 = int (*)(int);
    auto Test7 = reinterpret_cast<FuncTest7>(scModule->GetFunctionPtr("Test7"));
    REQUIRE(Test7(5) == 4);

    using FuncTest8 = int (*)(int);
    auto Test8 = reinterpret_cast<FuncTest8>(scModule->GetFunctionPtr("Test8"));
    REQUIRE(Test8(5) == 0);

    using FuncTest9 = int (*)(int);
    auto Test9 = reinterpret_cast<FuncTest9>(scModule->GetFunctionPtr("Test9"));
    REQUIRE(Test9(5) == 2);

    using FuncTest10 = int (*)(int);
    auto Test10 = reinterpret_cast<FuncTest10>(scModule->GetFunctionPtr("Test10"));
    REQUIRE(Test10(5) == 4);

    delete scModule;
}


TEST_CASE("CodeGenerationWhileStatementTests", "[CodeGenerationTests]")
{
    Compiler compiler;
    SCCompileResult compileResult;

    std::string testCode = "\
    int Test1(int a)   { int i=0; while (i<5) { a = i;  i=i+1; } return a; }                 \n\
    int Test3(int a, bool b)   { while (b) { a = a+1; b=false; } return a; }                 \n\
    int Test6(int a)   { int i=0; while (i<5) { a=i; i=i+1; continue; a=-1; } return a; }    \n\
    int Test7(int a)   { int i=0; while (i<5) { a=i; i=i+1; if (true) { continue; } a=-1; } return a; }   \n\
    int Test8(int a)   { int i=0; while (i<5) { a=i; i=i+1; break; a=-1; } return a; }                    \n\
    int Test9(int a)   { int i=0; while (i<5) { a=i; if (i==2){ break; } a=-1; i=i+1; } return a; }       \n\
    int Test10(int a)  { int i=0; while (i<5) { a=i; i=i+1; int j=0; while(j<5) { j=j+1; break; a=-1; } } return a; }  \n\
    ";
    auto scModule = compiler.CompileFromMemory(testCode, compileResult);

    REQUIRE(compileResult == scc::SCCompileResult::kSCCompileResultOk);
    REQUIRE(scModule != nullptr);

    using FuncTest1 = int (*)(int);
    auto Test1 = reinterpret_cast<FuncTest1>(scModule->GetFunctionPtr("Test1"));
    REQUIRE(Test1(5) == 4);

    using FuncTest3 = int (*)(int, bool);
    auto Test3 = reinterpret_cast<FuncTest3>(scModule->GetFunctionPtr("Test3"));
    REQUIRE(Test3(5, false) == 5);
    REQUIRE(Test3(5, true) == 6);

    using FuncTest6 = int (*)(int);
    auto Test6 = reinterpret_cast<FuncTest6>(scModule->GetFunctionPtr("Test6"));
    REQUIRE(Test6(5) == 4);

    using FuncTest7 = int (*)(int);
    auto Test7 = reinterpret_cast<FuncTest7>(scModule->GetFunctionPtr("Test7"));
    REQUIRE(Test7(5) == 4);

    using FuncTest8 = int (*)(int);
    auto Test8 = reinterpret_cast<FuncTest8>(scModule->GetFunctionPtr("Test8"));
    REQUIRE(Test8(5) == 0);

    using FuncTest9 = int (*)(int);
    auto Test9 = reinterpret_cast<FuncTest9>(scModule->GetFunctionPtr("Test9"));
    REQUIRE(Test9(5) == 2);

    using FuncTest10 = int (*)(int);
    auto Test10 = reinterpret_cast<FuncTest10>(scModule->GetFunctionPtr("Test10"));
    REQUIRE(Test10(5) == 4);

    delete scModule;
}


TEST_CASE("CodeGenerationDoWhileStatementTests", "[CodeGenerationTests]")
{
    Compiler compiler;
    SCCompileResult compileResult;

    std::string testCode = "\
    int Test1(int a)   { int i=0; do { a = i;  i=i+1; } while (i<5); return a; }                 \n\
    int Test2(int a, bool b)   { do { a = a+1; b=false; } while (b); return a; }                 \n\
    int Test3(int a)   { int i=0; do { a=i; i=i+1; continue; a=-1; } while (i<5); return a; }    \n\
    int Test4(int a)   { int i=0; do { a=i; i=i+1; if (true) { continue; } a=-1; } while (i<5); return a; }   \n\
    int Test5(int a)   { int i=0; do { a=i; i=i+1; break; a=-1; } while (i<5); return a; }                    \n\
    int Test6(int a)   { int i=0; do { a=i; if (i==2){ break; } a=-1; i=i+1; } while (i<5); return a; }       \n\
    int Test7(int a)   { int i=0; do { a=i; i=i+1; int j=0; do { j=j+1; break; a=-1; } while (j<5); } while (i<5); return a; }  \n\
    ";
    auto scModule = compiler.CompileFromMemory(testCode, compileResult);

    REQUIRE(compileResult == scc::SCCompileResult::kSCCompileResultOk);
    REQUIRE(scModule != nullptr);

    using FuncTest1 = int (*)(int);
    auto Test1 = reinterpret_cast<FuncTest1>(scModule->GetFunctionPtr("Test1"));
    REQUIRE(Test1(5) == 4);

    using FuncTest2 = int (*)(int, bool);
    auto Test2 = reinterpret_cast<FuncTest2>(scModule->GetFunctionPtr("Test2"));
    REQUIRE(Test2(5, false) == 6);
    REQUIRE(Test2(5, true) == 6);

    using FuncTest3 = int (*)(int);
    auto Test3 = reinterpret_cast<FuncTest3>(scModule->GetFunctionPtr("Test3"));
    REQUIRE(Test3(5) == 4);

    using FuncTest4 = int (*)(int);
    auto Test4 = reinterpret_cast<FuncTest4>(scModule->GetFunctionPtr("Test4"));
    REQUIRE(Test4(5) == 4);

    using FuncTest5 = int (*)(int);
    auto Test5 = reinterpret_cast<FuncTest5>(scModule->GetFunctionPtr("Test5"));
    REQUIRE(Test5(5) == 0);

    using FuncTest6 = int (*)(int);
    auto Test6 = reinterpret_cast<FuncTest6>(scModule->GetFunctionPtr("Test6"));
    REQUIRE(Test6(5) == 2);

    using FuncTest7 = int (*)(int);
    auto Test7 = reinterpret_cast<FuncTest7>(scModule->GetFunctionPtr("Test7"));
    REQUIRE(Test7(5) == 4);

    delete scModule;
}


TEST_CASE("CodeGenerationPrefixAOPTests", "[CodeGenerationTests]")
{
    Compiler compiler;
    SCCompileResult compileResult;

    std::string testCode = "\
    int Test1(int a)  { return ++a; }        \n\
    int Test2(int a)  { return --a; }        \n\
    ";
    auto scModule = compiler.CompileFromMemory(testCode, compileResult);

    REQUIRE(compileResult == scc::SCCompileResult::kSCCompileResultOk);
    REQUIRE(scModule != nullptr);

    using FuncTest1 = int (*)(int);
    auto Test1 = reinterpret_cast<FuncTest1>(scModule->GetFunctionPtr("Test1"));
    REQUIRE(Test1(5) == 6);
    REQUIRE(Test1(-5) == -4);

    using FuncTest2 = int (*)(int);
    auto Test2 = reinterpret_cast<FuncTest2>(scModule->GetFunctionPtr("Test2"));
    REQUIRE(Test2(5) == 4);
    REQUIRE(Test2(-5) == -6);

    delete scModule;
}

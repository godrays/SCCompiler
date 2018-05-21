//
//  CodeGenerationTests.cpp
//
//  Created by Arkin Terli on 5/8/18.
//  Copyright © 2018 Arkin Terli. All rights reserved.
//

#include <limits>

#include "Compiler.hpp"
#include "CodeGenerationTests.hpp"

using namespace scc;


// Registers the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION( CodeGenerationTests );


#pragma mark - CodeGenerationTests Implementations

void CodeGenerationTests::setUp()
{
    // Common test setup goes here
}


void CodeGenerationTests::tearDown()
{
    // Common test setup cleanup goes here
}


SCModule * CodeGenerationTests::TestCode(std::string sourceCode, SCCompileResult expectedCompileResult, bool acceptExpectedCompileResult)
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


void CodeGenerationTests::CodeGenerationExplicitTypeConversionTests()
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

    CPPUNIT_ASSERT(compileResult == scc::SCCompileResult::kSCCompileResultOk);
    CPPUNIT_ASSERT(scModule != nullptr);

    // FLOAT CONVERSIONS -----------------------------------

    // FLOAT TO BOOL
    using FuncFloatToBool = bool (*)(float);
    auto FloatToBool = reinterpret_cast<FuncFloatToBool>(scModule->GetFunctionPtr("FloatToBool"));

    CPPUNIT_ASSERT(FloatToBool(0.0f) == false);
    CPPUNIT_ASSERT(FloatToBool(1.0f) == true);
    CPPUNIT_ASSERT(FloatToBool(-1.0f) == true);
    CPPUNIT_ASSERT(FloatToBool(std::numeric_limits<float>::max()) == true);
    CPPUNIT_ASSERT(FloatToBool(std::numeric_limits<float>::min()) == true);

    // FLOAT TO INT
    using FuncFloatToInt = int (*)(float);
    auto FloatToInt = reinterpret_cast<FuncFloatToInt>(scModule->GetFunctionPtr("FloatToInt"));

    CPPUNIT_ASSERT(FloatToInt(0.0f) == 0);
    CPPUNIT_ASSERT(FloatToInt(1.5f) == 1);
    CPPUNIT_ASSERT(FloatToInt(-1.5f) == -1);
    CPPUNIT_ASSERT(FloatToInt(std::numeric_limits<float>::max()) == int(std::numeric_limits<float>::max()));
    CPPUNIT_ASSERT(FloatToInt(std::numeric_limits<float>::min()) == int(std::numeric_limits<float>::min()));

    // FLOAT TO FLOAT
    using FuncFloatToFloat = float (*)(float);
    auto FloatToFloat = reinterpret_cast<FuncFloatToFloat>(scModule->GetFunctionPtr("FloatToFloat"));

    CPPUNIT_ASSERT(FloatToFloat(0.0f) == 0.0f);
    CPPUNIT_ASSERT(FloatToFloat(1.5f) == 1.5f);
    CPPUNIT_ASSERT(FloatToFloat(-1.5f) == -1.5f);
    CPPUNIT_ASSERT(FloatToFloat(std::numeric_limits<float>::max()) == std::numeric_limits<float>::max());
    CPPUNIT_ASSERT(FloatToFloat(std::numeric_limits<float>::min()) == std::numeric_limits<float>::min());

    // INT CONVERSIONS -----------------------------------

    // INT TO BOOL
    using FuncIntToBool = bool (*)(int);
    auto IntToBool = reinterpret_cast<FuncIntToBool>(scModule->GetFunctionPtr("IntToBool"));

    CPPUNIT_ASSERT(IntToBool(0) == false);
    CPPUNIT_ASSERT(IntToBool(1) == true);
    CPPUNIT_ASSERT(IntToBool(-1) == true);
    CPPUNIT_ASSERT(IntToBool(std::numeric_limits<int>::max()) == bool(std::numeric_limits<int>::max()));
    CPPUNIT_ASSERT(IntToBool(std::numeric_limits<int>::min()) == bool(std::numeric_limits<int>::min()));

    // INT TO INT
    using FuncIntToInt = int (*)(int);
    auto IntToInt = reinterpret_cast<FuncIntToInt>(scModule->GetFunctionPtr("IntToInt"));

    CPPUNIT_ASSERT(IntToInt(0) == 0);
    CPPUNIT_ASSERT(IntToInt(1) == 1);
    CPPUNIT_ASSERT(IntToInt(-1) == -1);
    CPPUNIT_ASSERT(IntToInt(std::numeric_limits<int>::max()) == std::numeric_limits<int>::max());
    CPPUNIT_ASSERT(IntToInt(std::numeric_limits<int>::min()) == std::numeric_limits<int>::min());

    // INT TO FLOAT
    using FuncIntToFloat = float (*)(int);
    auto IntToFloat = reinterpret_cast<FuncIntToFloat>(scModule->GetFunctionPtr("IntToFloat"));

    CPPUNIT_ASSERT(IntToFloat(0) == 0.0f);
    CPPUNIT_ASSERT(IntToFloat(1) == 1.0f);
    CPPUNIT_ASSERT(IntToFloat(-1) == -1.0f);
    CPPUNIT_ASSERT(IntToFloat(std::numeric_limits<int>::max()) == float(std::numeric_limits<int>::max()));
    CPPUNIT_ASSERT(IntToFloat(std::numeric_limits<int>::min()) == float(std::numeric_limits<int>::min()));

    // BOOL CONVERSIONS -----------------------------------

    // BOOL TO BOOL
    using FuncBoolToBool = bool (*)(bool);
    auto BoolToBool = reinterpret_cast<FuncBoolToBool>(scModule->GetFunctionPtr("BoolToBool"));

    CPPUNIT_ASSERT(BoolToBool(false) == false);
    CPPUNIT_ASSERT(BoolToBool(true) == true);

    // BOOL TO INT
    using FuncBoolToInt = int (*)(bool);
    auto BoolToInt = reinterpret_cast<FuncIntToInt>(scModule->GetFunctionPtr("BoolToInt"));

    CPPUNIT_ASSERT(BoolToInt(false) == 0);
    CPPUNIT_ASSERT(BoolToInt(true) == 1);

    // BOOL TO FLOAT
    using FuncBoolToFloat = float (*)(bool);
    auto BoolToFloat = reinterpret_cast<FuncBoolToFloat>(scModule->GetFunctionPtr("BoolToFloat"));

    CPPUNIT_ASSERT(BoolToFloat(false) == 0.0f);
    CPPUNIT_ASSERT(BoolToFloat(true) == 1.0f);

    delete scModule;
}


void CodeGenerationTests::CodeGenerationUnaryOPTests()
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

    CPPUNIT_ASSERT(compileResult == scc::SCCompileResult::kSCCompileResultOk);
    CPPUNIT_ASSERT(scModule != nullptr);

    // FLOAT
    using FuncNegFloat = float (*)(float);
    auto NegFloat = reinterpret_cast<FuncNegFloat>(scModule->GetFunctionPtr("NegFloat"));

    CPPUNIT_ASSERT(NegFloat(0.0f) == 0.0f);
    CPPUNIT_ASSERT(NegFloat(-1.123456f) == 1.123456f);
    CPPUNIT_ASSERT(NegFloat(1.123456f) == -1.123456f);
    CPPUNIT_ASSERT(NegFloat(std::numeric_limits<float>::max()) == -std::numeric_limits<float>::max());
    CPPUNIT_ASSERT(NegFloat(std::numeric_limits<float>::min()) == -std::numeric_limits<float>::min());

    using FuncPosFloat = float (*)(float);
    auto PosFloat = reinterpret_cast<FuncPosFloat>(scModule->GetFunctionPtr("PosFloat"));

    CPPUNIT_ASSERT(PosFloat(0.0f) == 0.0f);
    CPPUNIT_ASSERT(PosFloat(1.123456f) == 1.123456f);
    CPPUNIT_ASSERT(PosFloat(-1.123456f) == -1.123456f);
    CPPUNIT_ASSERT(PosFloat(std::numeric_limits<float>::max()) == std::numeric_limits<float>::max());
    CPPUNIT_ASSERT(PosFloat(std::numeric_limits<float>::min()) == std::numeric_limits<float>::min());
    CPPUNIT_ASSERT(PosFloat(-std::numeric_limits<float>::max()) == -std::numeric_limits<float>::max());
    CPPUNIT_ASSERT(PosFloat(-std::numeric_limits<float>::min()) == -std::numeric_limits<float>::min());

    // INT
    using FuncNegInt = int (*)(int);
    auto NegInt = reinterpret_cast<FuncNegInt>(scModule->GetFunctionPtr("NegInt"));

    CPPUNIT_ASSERT(NegInt(0.0f) == 0.0f);
    CPPUNIT_ASSERT(NegInt(-1) == 1);
    CPPUNIT_ASSERT(NegInt(1) == -1);
    CPPUNIT_ASSERT(NegInt(std::numeric_limits<int>::max()) == -std::numeric_limits<int>::max());
    CPPUNIT_ASSERT(NegInt(std::numeric_limits<int>::min()) == -std::numeric_limits<int>::min());

    using FuncPosInt = int (*)(int);
    auto PosInt = reinterpret_cast<FuncPosInt>(scModule->GetFunctionPtr("PosInt"));

    CPPUNIT_ASSERT(PosInt(0.0f) == 0.0f);
    CPPUNIT_ASSERT(PosInt(1) == 1);
    CPPUNIT_ASSERT(PosInt(-1) == -1);
    CPPUNIT_ASSERT(PosInt(std::numeric_limits<int>::max()) == std::numeric_limits<int>::max());
    CPPUNIT_ASSERT(PosInt(std::numeric_limits<int>::min()) == std::numeric_limits<int>::min());
    CPPUNIT_ASSERT(PosInt(-std::numeric_limits<int>::max()) == -std::numeric_limits<int>::max());
    CPPUNIT_ASSERT(PosInt(-std::numeric_limits<int>::min()) == -std::numeric_limits<int>::min());

    delete scModule;
}

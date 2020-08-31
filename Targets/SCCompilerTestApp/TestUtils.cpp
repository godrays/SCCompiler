//
//  SyntaxTests.cpp
//
//  Created by Arkin Terli on 4/17/18.
//  Copyright © 2018-Present, Arkin Terli. All rights reserved.
//

#include <iostream>
#include <utility>

#include <catch2/catch.hpp>

#include "TestUtils.hpp"


bool TestCode(std::string sourceCode, scc::SCCompileResult expectedCompileResult, bool acceptExpectedCompileResult)
{
    scc::Compiler compiler;
    scc::SCCompileResult compileResult;

    auto scModule = compiler.CompileFromMemory(std::move(sourceCode), compileResult);

    // Assert if compiler result is not expected.
    if ((acceptExpectedCompileResult && (compileResult != expectedCompileResult)) ||
        (!acceptExpectedCompileResult && (compileResult == expectedCompileResult)))
    {
        std::cerr << compiler.GetErrorMessage() << std::endl;
        return false;
    }

    delete scModule;

    return true;
}

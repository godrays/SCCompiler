//
//  Created by Arkin Terli on 4/17/18.
//  Copyright © 2018-Present, Arkin Terli. All rights reserved.
//

// Project includes
#include "TestUtils.hpp"
// External includes
#include <catch2/catch.hpp>
// System includes
#include <iostream>
#include <utility>


bool testCode(std::string sourceCode, scc::SCCompileResult expectedCompileResult, bool acceptExpectedCompileResult)
{
    scc::Compiler compiler;
    scc::SCCompileResult compileResult;

    auto scModule = compiler.compileFromMemory(std::move(sourceCode), compileResult);

    // Assert if compiler result is not expected.
    if ((acceptExpectedCompileResult && (compileResult != expectedCompileResult)) ||
        (!acceptExpectedCompileResult && (compileResult == expectedCompileResult)))
    {
        std::cerr << compiler.getErrorMessage() << std::endl;
        return false;
    }

    delete scModule;

    return true;
}

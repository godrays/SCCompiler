
#include <iostream>
#include <catch.hpp>

#include "TestUtils.hpp"


bool TestCode(std::string sourceCode, scc::SCCompileResult expectedCompileResult, bool acceptExpectedCompileResult)
{
    scc::Compiler compiler;
    scc::SCCompileResult compileResult;

    auto scModule = compiler.CompileFromMemory(sourceCode, compileResult);

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

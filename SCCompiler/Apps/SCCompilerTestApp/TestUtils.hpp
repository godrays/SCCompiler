
#pragma once

#include <string>

#include "Compiler.hpp"

bool TestCode(std::string sourceCode, scc::SCCompileResult expectedCompileResult, bool acceptExpectedCompileResult);

scc::SCModule * TestCodeM(std::string sourceCode, scc::SCCompileResult expectedCompileResult, bool acceptExpectedCompileResult);

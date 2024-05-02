//
//  Created by Arkin Terli on 4/17/18.
//  Copyright © 2018-Present, Arkin Terli. All rights reserved.
//

#pragma once

// Project includes
#include <Compiler.hpp>
// External includes
// System includes
#include <string>


bool TestCode(std::string sourceCode, scc::SCCompileResult expectedCompileResult, bool acceptExpectedCompileResult);

scc::SCModule * TestCodeM(std::string sourceCode, scc::SCCompileResult expectedCompileResult, bool acceptExpectedCompileResult);

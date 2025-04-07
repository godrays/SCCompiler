//
//  Created by Arkin Terli on 5/11/18.
//  Copyright © 2018-Present, Arkin Terli. All rights reserved.
//

#pragma once

// Project includes
#include "SCModule.hpp"
// External includes
// System includes


namespace scc
{

enum class SCCompileResult
{
    kSCCompileResultOk,
    kSCCompileResultSyntaxError,
    kSCCompileResultSemanticError,
    kSCCompileResultCompileError,
};


class SCCompiler
{
public:
    // Creates SCCompilerLib object.
    static SCCompiler * Create();

    // Destructor.
    virtual ~SCCompiler() = 0;

    // Compiles Simple C Source code from file.
    virtual SCModule * CompileFromFile(std::string filename, SCCompileResult & compileResult) = 0;

    // Compiles Simple C Source code from memory.
    virtual SCModule * CompileFromMemory(std::string sourceCode, SCCompileResult & compileResult) = 0;

    // Returns compile error message.
    virtual std::string GetErrorMessage() = 0;
};

}

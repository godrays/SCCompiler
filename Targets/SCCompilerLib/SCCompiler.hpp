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
    kOk,
    kSyntaxError,
    kSemanticError,
    kCompileError,
};


class SCCompiler
{
public:
    // Creates SCCompilerLib object.
    static SCCompiler * create();

    // Destructor.
    virtual ~SCCompiler() = 0;

    // Compiles Simple C Source code from file.
    virtual SCModule * compileFromFile(std::string filename, SCCompileResult & compileResult) = 0;

    // Compiles Simple C Source code from memory.
    virtual SCModule * compileFromMemory(std::string sourceCode, SCCompileResult & compileResult) = 0;

    // Returns compile error message.
    virtual std::string getErrorMessage() = 0;
};

}

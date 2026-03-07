//
//  Created by Arkin Terli on 5/11/18.
//  Copyright © 2018-Present, Arkin Terli. All rights reserved.
//

#pragma once

// Project includes
#include "SCModule.hpp"
// External includes
// System includes
#include <memory>


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
    static std::unique_ptr<SCCompiler> create();

    // Destructor.
    virtual ~SCCompiler() = 0;

    // Compiles Simple C Source code from file.
    virtual std::unique_ptr<SCModule> compileFromFile(std::string filename, SCCompileResult & compileResult) = 0;

    // Compiles Simple C Source code from memory.
    virtual std::unique_ptr<SCModule> compileFromMemory(std::string sourceCode, SCCompileResult & compileResult) = 0;

    // Returns compile error message.
    virtual std::string getErrorMessage() = 0;
};

}

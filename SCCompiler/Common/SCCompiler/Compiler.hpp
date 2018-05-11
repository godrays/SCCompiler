//
//  Compiler.hpp
//
//  Created by Arkin Terli on 4/10/18.
//  Copyright © 2018 Arkin Terli. All rights reserved.
//

#pragma once

#include <string>

#include "SCModule.hpp"


namespace SCCompiler
{

    #pragma mark - Class CompilerErrorListenerBase.

    enum CompileResult : uint32_t
    {
        rCompileResultOk,
        rCompileResultSyntaxError,
        rCompileResultSemanticError,
        rCompileResultCompileError,
    };


    #pragma mark - Class Compiler.

    class Compiler
    {
    public:

        // Compiles Simple C Source code from file.
        SCModule * CompileFromFile(std::string filename, CompileResult & compileResult);

        // Compiles Simple C Source code from memory.
        SCModule * CompileFromMemory(std::string sourceCode, CompileResult & compileResult);

        // Returns compile error message.
        std::string GetErrorMessage()   { return m_errorMessage; }

    protected:
        // Compiles Simple C Source code.
        SCModule * Compile(std::istream & sourceStream, CompileResult & compileResult);

    private:
        std::string     m_errorMessage;
    };

};

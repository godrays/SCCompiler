//
//  SCCompiler.hpp
//
//  Created by Arkin Terli on 5/11/18.
//  Copyright © 2018 Arkin Terli. All rights reserved.
//

#pragma once

#include "SCModule.hpp"

namespace scc
{

    #pragma mark - Enum SCCompileResult.

    enum SCCompileResult : uint32_t
    {
        kSCCompileResultOk,
        kSCCompileResultSyntaxError,
        kSCCompileResultSemanticError,
        kSCCompileResultCompileError,
    };


    #pragma mark - Class SCCompiler.

    class SCCompiler
    {
    public:
        // Creates SCCompiler object.
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

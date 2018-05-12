//
//  Compiler.hpp
//
//  Created by Arkin Terli on 4/10/18.
//  Copyright © 2018 Arkin Terli. All rights reserved.
//

#pragma once

#include <string>

#include "SCModule.hpp"
#include "SCCompiler.hpp"


namespace scc
{

    #pragma mark - Class Compiler.

    class Compiler : public SCCompiler
    {
    public:

        // Compiles Simple C Source code from file.
        SCModule * CompileFromFile(std::string filename, SCCompileResult & compileResult) override final;

        // Compiles Simple C Source code from memory.
        SCModule * CompileFromMemory(std::string sourceCode, SCCompileResult & compileResult) override final;

        // Returns compile error message.
        std::string GetErrorMessage() override final  { return m_errorMessage; }

    protected:
        // Compiles Simple C Source code.
        SCModule * Compile(std::istream & sourceStream, SCCompileResult & compileResult);

    private:
        std::string     m_errorMessage;
    };

};

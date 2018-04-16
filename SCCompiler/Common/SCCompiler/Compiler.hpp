//
//  Compiler.hpp
//
//  Created by Arkin Terli on 4/10/18.
//  Copyright © 2018 Arkin Terli. All rights reserved.
//

#pragma once

#include <string>


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
        CompileResult Compile(std::string filename);
        
        // Returns compile error message.
        std::string GetErrorMessage()   { return m_errorMessage; }
    
    private:
        std::string     m_errorMessage;
    };

};

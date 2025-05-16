//
//  Created by Arkin Terli on 4/10/18.
//  Copyright © 2018-Present, Arkin Terli. All rights reserved.
//

#pragma once

// Project includes
#include "SCCompiler.hpp"
#include "SCModule.hpp"
// External includes
// System includes
#include <string>


namespace scc
{

class Compiler : public SCCompiler
{
public:

    // Compiles Simple C Source code from file.
    SCModule * compileFromFile(std::string filename, SCCompileResult & compileResult) final;

    // Compiles Simple C Source code from memory.
    SCModule * compileFromMemory(std::string sourceCode, SCCompileResult & compileResult) final;

    // Returns compile error message.
    std::string getErrorMessage() final  { return m_errorMessage; }

protected:
    // Compiles Simple C Source code.
    SCModule * compile(std::istream & sourceStream, SCCompileResult & compileResult);

private:
    std::string     m_errorMessage;
};

}

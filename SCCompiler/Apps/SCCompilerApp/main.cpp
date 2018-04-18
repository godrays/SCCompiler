//
//  main.cpp
//  SCCompiler
//
//  Created by Arkin Terli on 3/31/18.
//  Copyright © 2018 Arkin Terli. All rights reserved.
//

#include <iostream>

#include "Compiler.hpp"


int main(int , const char **)
{
    SCCompiler::Compiler  compiler;
    
    if (SCCompiler::rCompileResultOk != compiler.CompileFromFile("SCCompilerTestCode.src"))
    {
        std::cerr << compiler.GetErrorMessage() << std::endl;
    }
    
    return 0;
}

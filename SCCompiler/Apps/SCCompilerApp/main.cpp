//
//  main.cpp
//
//  Created by Arkin Terli on 3/31/18.
//  Copyright © 2018 Arkin Terli. All rights reserved.
//

#include <iostream>

#include "JITEngine.hpp"
#include "Compiler.hpp"


int main(int , const char **)
{
    SCC::Compiler  * compiler = new SCC::Compiler();
    SCC::CompileResult  compileResult;
    
    auto scModule = compiler->CompileFromFile("SCCompilerTestCode.src", compileResult);

    if (SCC::rCompileResultOk != compileResult)
    {
        std::cerr << compiler->GetErrorMessage() << std::endl;
        return -1;
    }

    // We no longer need compiler. We just need SCModule, compiled module.
    delete compiler;

    typedef int (* FuncFib)(int);
    auto fib = reinterpret_cast<FuncFib>(scModule->GetFunctionPtr("fib"));
    std::cout << fib(3) << std::endl;

    delete scModule;

    return 0;
}

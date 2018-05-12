//
//  main.cpp
//
//  Created by Arkin Terli on 3/31/18.
//  Copyright © 2018 Arkin Terli. All rights reserved.
//

#include <iostream>

#include "SCCompiler.hpp"

int main(int , const char **)
{
    auto compiler = scc::SCCompiler::Create();
    scc::SCCompileResult  compileResult;
    
    auto scModule = compiler->CompileFromFile("SCCompilerTestCode.src", compileResult);

    if (scc::kSCCompileResultOk != compileResult)
    {
        std::cerr << compiler->GetErrorMessage() << std::endl;
        return -1;
    }

    // We no longer need compiler. We just need SCModule, compiled module.
    delete compiler;

    using FuncFib = int (*)(int);
    auto fib = reinterpret_cast<FuncFib>(scModule->GetFunctionPtr("fib"));
    std::cout << fib(3) << std::endl;

    delete scModule;

    return 0;
}

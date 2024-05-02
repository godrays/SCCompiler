//
//  Created by Arkin Terli on 3/31/18.
//  Copyright © 2018-Present, Arkin Terli. All rights reserved.
//

// Project includes
#include "SCCompiler.hpp"
// External includes
// System includes
#include <iostream>


int main(int , const char **)
{
    auto compiler = scc::SCCompiler::Create();
    scc::SCCompileResult  compileResult;

    auto scModule = compiler->CompileFromFile("SCCompilerTestCode.src", compileResult);

    if (scc::SCCompileResult::kSCCompileResultOk != compileResult)
    {
        std::cerr << compiler->GetErrorMessage() << std::endl;
        return -1;
    }

    // We no longer need compiler since SCModule holds compiled machine code.
    delete compiler;

    // SCModule holds compiled machine code. Let's bind to the compiled main function.
    using mainFuncType = int (*)(int);
    auto mainFunc = reinterpret_cast<mainFuncType>(scModule->GetFunctionPtr("main"));

    // Call the main function, which is the machine code in memory, directly.
    std::cout << "fib(10) = " << mainFunc(10) << std::endl;

    delete scModule;

    return 0;
}

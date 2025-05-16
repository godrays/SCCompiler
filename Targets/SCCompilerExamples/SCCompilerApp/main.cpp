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
    const std::string sourceCode =
    R"(
        // Returns fibonacci number
        int fib(int n)
        {
            if (n <= 1)
                return n;

            return fib(n-1) + fib(n-2);
        }

        int main(int a)
        {
            return fib(a);
        }
    )";

    // Create the compiler.
    const auto compiler = scc::SCCompiler::create();
    scc::SCCompileResult  compileResult;

    // Compile the source code from memory.
    const auto scModule = compiler->compileFromMemory(sourceCode, compileResult);

    if (scc::SCCompileResult::kOk != compileResult)
    {
        std::cerr << compiler->getErrorMessage() << std::endl;
        return -1;
    }

    // We no longer need compiler since SCModule holds compiled machine code.
    delete compiler;

    // SCModule holds compiled machine code. Let's bind to the compiled main function.
    using mainFuncType = int (*)(int);
    const auto mainFunc = reinterpret_cast<mainFuncType>(scModule->getFunctionPtr("main"));

    // Call the main function, which is the machine code in memory, directly.
    std::cout << "fib(10) = " << mainFunc(10) << std::endl;

    delete scModule;

    return 0;
}

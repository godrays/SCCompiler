# Simple C JIT Compiler

Welcome to the Simple C JIT Compiler project designed by `Arkin Terli` to demonstrate the construction of a Just-In-Time (JIT) compiler using modern tools and technologies.

This compiler is built using ANTLR4 for the frontend and LLVM for the backend, providing a practical example of how these powerful libraries can be leveraged to create a fully functional JIT compiler in C++.

The entire purpose is experimentation/research; although with limited language features, it's a fully functional, production-ready JIT compiler that has been tested.

---

### Overview
The Simple C JIT Compiler aims to provide a comprehensive understanding of the compiler design process, from lexical analysis and parsing to code generation and optimization. Despite its simplicity, this compiler supports a wide range of features typically found in the C programming language, including:

- Variable declarations (float, int, bool)
- Functions and recursive function calls
- Control flow statements (while, do-while, for, if-else)
- Loop control statements (return, continue, break)
- Arithmetic operations (`+`, `-`, `*`, `/`)
- Comparison operations (`<`, `<=`, `>`, `>=`, `==`, `!=`)
- Prefix increment/decrement operators (`++`, `--`)
- Explicit type conversions
- And many more...

---

### Example

This example demonstrates how to use the Simple C JIT Compiler to compile and execute C code from memory.

Let's go through the code step by step:

```C++
#include "SCCompiler.hpp"
#include <iostream>

int main()
{
    // An example source code to compile in memory.
    const std::string sourceCode = R"(
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
    
    // We no longer need the compiler.
    delete compiler;

    // SCModule holds compiled machine code. Let's bind to the compiled main function.
    using mainFuncType = int (*)(int);
    const auto mainFunc = reinterpret_cast<mainFuncType>(scModule->getFunctionPtr("main"));

    // Call the main function, which is the machine code in memory, directly.
    std::cout << "fib(10) = " << mainFunc(10) << std::endl;

    delete scModule;

    return 0;
}
```

Alternatively, you can load the source code from a file with a single line change.

```C++
auto scModule = compiler->CompileFromFile("my_source_file.src", compileResult);
```

# Guidance

The following steps are necessary to understand and add a new language feature.

---

### How to Update the Language Grammar

1. Make your change in the language grammar file, assuming that you are already familiar with ANTLR4. The grammar file is located at: 
   ```
   Targets/SCCompilerLib/Parser/SCCompiler.g4
   ```

2. We need to check if our grammar can parse our new language feature. Create a sample source code file that uses the new language feature. Let's assume it's called `example.src`. 


3. A vital step is to ensure your language grammar is constructed as expected. The following script will generate a temporary Java parser and use your source code to parse and visualize the parsed tree:
   ```bash
   python show_ptree.py build-release Targets/SCCompilerLib/Parser/SCCompiler.g4 example.src
   ```

4. If everything is OK, update your C++ parser source code files so that the parser knows how to parse the new feature:
   ```bash
   python generate_parser.py <cmake-build-dir>
   ```

Now you should see that some files under the `Targets/SCCompilerLib/Parser` folder have been updated.

---

### How to Make the Code Changes

The next step is to change the source code to handle the new grammar feature.

SCCompiler follows a typical compiler construction process:

1. The C++ parser constructs a noisy AST (Abstract Syntax Tree) called a Parser-Tree.
2. We visit every parser-tree node and generate our own AST.
3. Perform a Symbol Definition pass by visiting the AST nodes to identify symbols.
4. Perform a Semantic Analysis pass by visiting the AST nodes again to ensure the language is used as expected.
5. Perform a Code Generation pass to generate code with LLVM by visiting the AST nodes as a final step.

You can see the entire process clearly at a higher level in the `scc::Compiler::Compile(...)` method in the `Targets/SCCompilerLib/Compiler.cpp` file.

While it's not possible to cover everything here, the following files typically need to be changed for each step listed above when adding a new language feature:

1. Explained in the previous section on how to update parser files under `Targets/SCCompilerLib/Parser`
2. `ASTGenerator.hpp/cpp` and `AST.hpp/cpp`
3. `SymbolDefPass.hpp/cpp`
4. `SemanticPass.hpp/cpp`
5. `CodeGenPass.hpp/cpp`

Last but not least, you have to add tests under `Targets/SCCompilerTests` that cover all the possible scenarios.


# Project Build Instructions

Follow these steps to build the project and make it deployment-ready.

Currently, it has been built and tested on `macOS Sonoma` and Windows 10 (MSVC) with no issues.

---

### Step 1: Build Targets

This step will build all binaries and deploy into a specific folder. Assuming you are in the root folder of the project.

```bash
python build.py build release build-release product-rel
```

After a successful build, all target binaries will be deployed into the product-rel folder.

Note: Run the build.py file without parameters to see all options.

---

### Step 2: Install Development Specific Dependencies (Optional).

This step will install dependencies, and it's necessary only if you want to work on the project. Feel free to skip this step if you want to use the SCCompiler as an external library in your project. Assuming XCode and MacPorts is already installed.

```bash
sudo port install ossp-uuid pkgconfig graphviz
```

Install JAVA SE SDK.

```bash
https://www.oracle.com/technetwork/java/javase/downloads/index.html
```


# Citing 

The SCCompiler is designed and developed by Arkin Terli. If you find SCCompiler useful in your research and wish to cite it, please use the following BibTex entry:

```
@software{SCCompiler2018,
   author = {Arkin Terli},
   title = {{SCCompiler}: Simple C JIT Compiler},
   url = {https://github.com/godrays/sccompiler},
   version = {0.0.0},
   year = {2018},
}
```

# License

Copyright © 2018 - Present, Arkin Terli. All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright
   notice, this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright
   notice, this list of conditions and the following disclaimer in the
   documentation and/or other materials provided with the distribution.

3. Neither the name of Arkin Terli nor the names of its contributors may be 
   used to endorse or promote products derived from this software without
   specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
POSSIBILITY OF SUCH DAMAGE.
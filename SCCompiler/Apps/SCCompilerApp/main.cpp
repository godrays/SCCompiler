//
//  main.cpp
//  SCCompiler
//
//  Created by Arkin Terli on 3/31/18.
//  Copyright © 2018 Arkin Terli. All rights reserved.
//

#include "Compiler.hpp"


int main(int , const char **)
{
    SCCompiler::Compiler  compiler;
    
    compiler.Compile("SCCompilerTestCode.src");
    
    return 0;
}

//
//  SCCompilerLib.cpp
//
//  Created by Arkin Terli on 5/11/18.
//  Copyright © 2018-Present, Arkin Terli. All rights reserved.
//

#include "Compiler.hpp"
#include "SCCompiler.hpp"

using namespace scc;


#pragma mark - SCCompiler Implementations.

SCCompiler * SCCompiler::Create()
{
    return new Compiler();
}


SCCompiler::~SCCompiler()
{
    // Abstract classes with pure virtual functions do not implement methods but destructor has to be implemented.
}


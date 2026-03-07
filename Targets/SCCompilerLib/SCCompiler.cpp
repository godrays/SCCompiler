//
//  Created by Arkin Terli on 5/11/18.
//  Copyright © 2018-Present, Arkin Terli. All rights reserved.
//

// Project includes
#include "SCCompiler.hpp"
#include "Compiler.hpp"
// External includes
// System includes


using namespace scc;


std::unique_ptr<SCCompiler> SCCompiler::create()
{
    return std::make_unique<Compiler>();
}


SCCompiler * SCCompiler::createRaw()
{
    return create().release();
}


SCModule * SCCompiler::compileFromFileRaw(std::string filename, SCCompileResult & compileResult)
{
    return compileFromFile(std::move(filename), compileResult).release();
}


SCModule * SCCompiler::compileFromMemoryRaw(std::string sourceCode, SCCompileResult & compileResult)
{
    return compileFromMemory(std::move(sourceCode), compileResult).release();
}


SCCompiler::~SCCompiler()
{
    // Abstract classes with pure virtual functions do not implement methods, but the destructor has to be implemented.
}

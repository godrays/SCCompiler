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


SCCompiler::~SCCompiler()
{
    // Abstract classes with pure virtual functions do not implement methods, but the destructor has to be implemented.
}

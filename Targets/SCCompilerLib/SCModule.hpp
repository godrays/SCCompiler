//
//  SCModule.hpp
//
//  Created by Arkin Terli on 5/11/18.
//  Copyright © 2018-Present, Arkin Terli. All rights reserved.
//

#pragma once

#include <string>


namespace scc
{

#pragma mark - Class SCModule.

class SCModule
{
public:
    // Destructor.
    virtual ~SCModule() = 0;

    // Returns pointer of a function.
    virtual void * GetFunctionPtr(std::string name) = 0;

    // Reset and initialize global variables.
    virtual void Reset() = 0;
};

}

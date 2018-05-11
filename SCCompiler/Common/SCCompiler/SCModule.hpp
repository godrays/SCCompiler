//
//  SCModule.hpp
//
//  Created by Arkin Terli on 5/11/18.
//  Copyright © 2018 Arkin Terli. All rights reserved.
//


#pragma once

#include <string>


namespace SCC
{

    #pragma mark - Class SCModule.

    class SCModule
    {
    public:
        // Destructor.
        virtual ~SCModule() = 0;

        // Returns pointer of a function.
        virtual void * GetFunctionPtr(std::string name) = 0;
    };

};

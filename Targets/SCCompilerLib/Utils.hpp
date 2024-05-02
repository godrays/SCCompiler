//
//  Created by Arkin Terli on 9/30/20.
//  Copyright © 2018-Present, Arkin Terli. All rights reserved.
//

#pragma once


namespace scc
{

// Throws an exception if the condition is true. It's a macro since it can't be implemented as efficiently as a macro
// with a template. This macro eliminates redundant constructor calls.
#define throw_if(condition, exception) \
    if (condition)          \
    {                       \
        throw exception;    \
    }                       \

}

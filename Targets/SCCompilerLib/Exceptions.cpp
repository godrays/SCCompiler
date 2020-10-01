//
//  Exceptions.cpp
//
//  Created by Arkin Terli on 4/16/18.
//  Copyright © 2018-Present, Arkin Terli. All rights reserved.
//

#include "Exceptions.hpp"

namespace scc
{


const char * CompileErrorException::what() const noexcept
{
    return m_message.c_str();
}


const char * SemanticErrorException::what() const noexcept
{
    return m_message.c_str();
}


}

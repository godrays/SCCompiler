//
//  Created by Arkin Terli on 4/16/18.
//  Copyright © 2018-Present, Arkin Terli. All rights reserved.
//

// Project includes
#include "Exceptions.hpp"
// External includes
// System includes


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

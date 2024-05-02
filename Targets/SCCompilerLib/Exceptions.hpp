//
//  Created by Arkin Terli on 4/16/18.
//  Copyright © 2018-Present, Arkin Terli. All rights reserved.
//

#pragma once

// Project includes
// External includes
// System includes
#include <exception>
#include <sstream>
#include <string>


namespace scc
{

#pragma mark - Class CompileErrorException.

class CompileErrorException : public std::exception
{
public:
    template<typename ...Args>
    explicit CompileErrorException(Args &&... args)
    {
        std::ostringstream  os;
        (os << ... <<  std::forward<Args>(args));
        m_message = os.str();
    }

    const char* what() const noexcept final;

private:
    std::string     m_message;
};


#pragma mark - Class SemanticErrorException.

class SemanticErrorException : public std::exception
{
public:
    template<typename ...Args>
    explicit SemanticErrorException(Args &&... args)
    {
        std::ostringstream  os;
        (os << ... <<  std::forward<Args>(args));
        m_message = os.str();
    }

    const char* what() const noexcept final;

private:
    std::string     m_message;
};

}

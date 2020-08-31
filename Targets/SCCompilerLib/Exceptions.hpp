//
//  Exceptions.hpp
//
//  Created by Arkin Terli on 4/16/18.
//  Copyright © 2018-Present, Arkin Terli. All rights reserved.
//

#pragma once

#include <string>
#include <exception>
#include <utility>


namespace scc
{

#pragma mark - Class CompileErrorException.

class CompileErrorException : public std::exception
{
public:
    explicit CompileErrorException(std::string message) : m_message(std::move(message)) { }

    const char * what() const noexcept final
    {
        return m_message.c_str();
    }

private:
    std::string  m_message;
};


#pragma mark - Class SemanticErrorException.

class SemanticErrorException : public std::exception
{
public:
    explicit SemanticErrorException(std::string message) : m_message(std::move(message)) { }

    const char * what() const noexcept final
    {
        return m_message.c_str();
    }

private:
    std::string  m_message;
};

}

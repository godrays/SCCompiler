//
//  Created by Arkin Terli on 4/15/18.
//  Copyright © 2018-Present, Arkin Terli. All rights reserved.
//

// Project includes
#include "Symbols.hpp"
// External includes
// System includes
#include <utility>


using namespace scc;


Symbol::Symbol(std::string name, SymbolCategory category, Type type) :
    m_name(std::move(name)),
    m_category(category),
    m_type(type),
    m_scopeNode(nullptr)
{

}


std::string Symbol::getName() const
{
    return m_name;
}


Type Symbol::getType() const
{
    return m_type;
}


void Symbol::setScope(ScopeNode * scopeNode)
{
    m_scopeNode = scopeNode;
}


SymbolCategory Symbol::getCategory()
{
    return m_category;
}


SymbolPropertyBase * Symbol::getProperty()
{
    return m_property.get();
}


void Symbol::setProperty(std::unique_ptr<SymbolPropertyBase> property)
{
    // Can't assign new property without deleting the previous one.
    assert(m_property == nullptr);
    m_property = std::move(property);
}


BuiltInTypeSymbol::BuiltInTypeSymbol(std::string name) :
    Symbol(std::move(name), SymbolCategory::kType, Type::kTypeUnknown)
{

}


VariableSymbol::VariableSymbol(std::string name, Type type) :
    Symbol(std::move(name), SymbolCategory::kVariable, type)
{

}


FunctionArgumentSymbol::FunctionArgumentSymbol(std::string name, Type type) :
    Symbol(std::move(name), SymbolCategory::kFunctionArgument, type)
{

}


FunctionSymbol::FunctionSymbol(std::string name, Type type) :
    Symbol(std::move(name), SymbolCategory::kFunction, type)
{

}

void FunctionSymbol::addArgumentSymbol(FunctionArgumentSymbol * argSymbol)
{
    m_argumentSymbols.emplace_back(argSymbol);
}


size_t FunctionSymbol::argumentCount()
{
    return m_argumentSymbols.size();
}


FunctionArgumentSymbol * FunctionSymbol::getArgumentSymbol(size_t index)
{
    return m_argumentSymbols[index];
}


ScopeNode::ScopeNode(ScopeCategory category, ScopeNode * enclosingScope) :
    m_category(category),
    m_enclosingScope(enclosingScope)
{
}


ScopeNode::~ScopeNode()
= default;


ScopeCategory ScopeNode::getCategory()
{
    return m_category;
}


bool ScopeNode::isDefined(const std::string & symbolName)
{
    // Return true if the symbol exists. Otherwise, false.
    return  m_symbolTable.find(symbolName) != m_symbolTable.end();
}


Symbol * ScopeNode::insertSymbol(std::unique_ptr<Symbol> symbol)
{
    assert(symbol != nullptr);

    // No duplicate symbol is allowed. The program should check before adding a new symbol.
    assert(m_symbolTable.find(symbol->getName()) == m_symbolTable.end());

    auto * symbolPtr = symbol.get();

    // Add the symbol to the symbol table. We are basically defining a new symbol in this scope.
    m_symbolTable[symbol->getName()] = std::move(symbol);

    // Set the scope for the symbol. Each symbol should know which scope they are in.
    symbolPtr->setScope(this);

    return symbolPtr;
}


Symbol *  ScopeNode::resolveSymbol(const std::string & symbolName)
{
    // Check if the symbol is available in the symbol table.
    auto pair = m_symbolTable.find(symbolName);

    // Return if the symbol exists.
    if ( pair != m_symbolTable.end())
    {
        return pair->second.get();
    }

    // If it can't be found in this scope, then check the enclosing scopes.
    if ( m_enclosingScope != nullptr )
    {
        return m_enclosingScope->resolveSymbol(symbolName);
    }

    // Not found.
    return nullptr;
}

ScopeNode * ScopeNode::addChild(std::unique_ptr<ScopeNode> childNode)
{
    assert(childNode != nullptr);

    auto * childPtr = childNode.get();
    m_children.emplace_back(std::move(childNode));

    return childPtr;
}


ScopeNode * ScopeNode::createChildScope(ScopeCategory category)
{
    return addChild(std::make_unique<ScopeNode>(category, this));
}


ScopeNode *  ScopeNode::getEnclosingScope()
{
    return m_enclosingScope;
}

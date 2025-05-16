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
    m_scopeNode(nullptr),
    m_property(nullptr)
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
    return m_property;
}


void Symbol::setProperty(SymbolPropertyBase * property)
{
    // Can't assign new property without deleting the previous one.
    assert(m_property == nullptr);
    m_property = property;
}


BuiltInTypeSymbol::BuiltInTypeSymbol(std::string name) :
    Symbol(std::move(name), SymbolCategory::kType, Type::kTypeUnknown)
{

}


VariableSymbol::VariableSymbol(std::string name, Type type) :
    Symbol(std::move(name), SymbolCategory::kVariable, type)
{

}


FuncArgSymbol::FuncArgSymbol(std::string name, Type type) :
    Symbol(std::move(name), SymbolCategory::kFunctionArgument, type)
{

}


FunctionSymbol::FunctionSymbol(std::string name, Type type) :
    Symbol(std::move(name), SymbolCategory::kFunction, type)
{

}

void FunctionSymbol::addArgumentSymbol(FuncArgSymbol * argSymbol)
{
    m_argumentSymbols.emplace_back(argSymbol);
}


size_t FunctionSymbol::argumentCount()
{
    return m_argumentSymbols.size();
}


FuncArgSymbol * FunctionSymbol::getArgumentSymbol(size_t index)
{
    return m_argumentSymbols[index];
}


ScopeNode::ScopeNode(ScopeCategory category, ScopeNode * enclosingScope) :
    m_category(category),
    m_enclosingScope(enclosingScope)
{
    // In the scope tree, a child is always connected to its parent.
    // Because of that, the child should add itself to the parent's children list.
    // In fact, the parent never needs to know its children since children point to the parent due to the nature of the scope tree.
    // However, we want the parent node to know its children since we need to delete child nodes when we delete the scope node root node.

    if (enclosingScope != nullptr)
    {
        enclosingScope->addChild(this);
    }
}


ScopeNode::~ScopeNode()
{
    // Delete all symbol objects.
    for (auto pair : m_symbolTable)
    {
        // Has table pair.first = key, pair.second = symbol
        delete pair.second->getProperty();
        delete pair.second;
    }

    // Clear symbol table.
    m_symbolTable.clear();

    // Delete all children.
    for (auto child : m_children)
    {
        delete child;
    }

    m_children.clear();
}


ScopeCategory ScopeNode::getCategory()
{
    return m_category;
}


bool ScopeNode::isDefined(const std::string & symbolName)
{
    // Return true if the symbol exists. Otherwise, false.
    return  m_symbolTable.find(symbolName) != m_symbolTable.end();
}


void  ScopeNode::insertSymbol(Symbol *  symbol)
{
    // No duplicate symbol is allowed. The program should check before adding a new symbol.
    assert(m_symbolTable.find(symbol->getName()) == m_symbolTable.end());

    // Add the symbol to the symbol table. We are basically defining a new symbol in this scope.
    m_symbolTable[symbol->getName()] = symbol;

    // Set the scope for the symbol. Each symbol should know which scope they are in.
    symbol->setScope(this);
}


Symbol *  ScopeNode::resolveSymbol(const std::string & symbolName)
{
    // Check if the symbol is available in the symbol table.
    auto pair = m_symbolTable.find(symbolName);

    // Return if the symbol exists.
    if ( pair != m_symbolTable.end())
    {
        return pair->second;
    }

    // If it can't be found in this scope, then check the enclosing scopes.
    if ( m_enclosingScope != nullptr )
    {
        return m_enclosingScope->resolveSymbol(symbolName);
    }

    // Not found.
    return nullptr;
}

void ScopeNode::addChild(ScopeNode * childNode)
{
    m_children.emplace_back(childNode);
}


ScopeNode *  ScopeNode::getEnclosingScope()
{
    return m_enclosingScope;
}

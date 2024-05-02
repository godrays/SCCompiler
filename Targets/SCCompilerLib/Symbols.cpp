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


#pragma mark - Symbol Implementations.

Symbol::Symbol(std::string name, SymbolCategory category, Type type) :
    m_name(std::move(name)),
    m_category(category),
    m_type(type),
    m_scopeNode(nullptr),
    m_property(nullptr)
{

}


std::string Symbol::GetName() const
{
    return m_name;
}


Type Symbol::GetType() const
{
    return m_type;
}


void Symbol::SetScope(ScopeNode * scopeNode)
{
    m_scopeNode = scopeNode;
}


SymbolCategory Symbol::GetCategory()
{
    return m_category;
}


SymbolPropertyBase * Symbol::GetProperty()
{
    return m_property;
}


void Symbol::SetProperty(SymbolPropertyBase * property)
{
    // Can't assign new property without deleting the previous one.
    assert(m_property == nullptr);
    m_property = property;
}


#pragma mark - Class BuiltInTypeSymbol

BuiltInTypeSymbol::BuiltInTypeSymbol(std::string name) :
    Symbol(std::move(name), SymbolCategory::kSymbolCategoryType, Type::kTypeUnknown)
{

}


#pragma mark - Class VariableSymbol

VariableSymbol::VariableSymbol(std::string name, Type type) :
    Symbol(std::move(name), SymbolCategory::kSymbolCategoryVariable, type)
{

}


#pragma mark - Class FuncArgSymbol

FuncArgSymbol::FuncArgSymbol(std::string name, Type type) :
    Symbol(std::move(name), SymbolCategory::kSymbolCategoryFunctionArgument, type)
{

}


#pragma mark - Class FunctionSymbol

FunctionSymbol::FunctionSymbol(std::string name, Type type) :
    Symbol(std::move(name), SymbolCategory::kSymbolCategoryFunction, type)
{

}

void FunctionSymbol::AddArgumentSymbol(FuncArgSymbol * argSymbol)
{
    m_argumentSymbols.emplace_back(argSymbol);
}


size_t FunctionSymbol::ArgumentCount()
{
    return m_argumentSymbols.size();
}


FuncArgSymbol * FunctionSymbol::GetArgumentSymbol(size_t index)
{
    return m_argumentSymbols[index];
}


#pragma mark - ScopeNode Implementations.

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
        enclosingScope->AddChild(this);
    }
}


ScopeNode::~ScopeNode()
{
    // Delete all symbol objects.
    for (auto pair : m_symbolTable)
    {
        // Has table pair.first = key, pair.second = symbol
        delete pair.second->GetProperty();
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


ScopeCategory ScopeNode::GetCategory()
{
    return m_category;
}


bool ScopeNode::IsDefined(const std::string & symbolName)
{
    // Return true if the symbol exists. Otherwise, false.
    return  m_symbolTable.find(symbolName) != m_symbolTable.end();
}


void  ScopeNode::InsertSymbol(Symbol *  symbol)
{
    // No duplicate symbol is allowed. The program should check before adding a new symbol.
    assert(m_symbolTable.find(symbol->GetName()) == m_symbolTable.end());

    // Add the symbol to the symbol table. We are basically defining a new symbol in this scope.
    m_symbolTable[symbol->GetName()] = symbol;

    // Set the scope for the symbol. Each symbol should know which scope they are in.
    symbol->SetScope(this);
}


Symbol *  ScopeNode::ResolveSymbol(const std::string & symbolName)
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
        return m_enclosingScope->ResolveSymbol(symbolName);
    }

    // Not found.
    return nullptr;
}

void ScopeNode::AddChild(ScopeNode * childNode)
{
    m_children.emplace_back(childNode);
}


ScopeNode *  ScopeNode::GetEnclosingScope()
{
    return m_enclosingScope;
}

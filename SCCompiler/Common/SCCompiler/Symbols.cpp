//
//  Symbols.cpp
//
//  Created by Arkin Terli on 4/15/18.
//  Copyright © 2018 Arkin Terli. All rights reserved.
//

#include "Symbols.hpp"


using namespace SCCompiler;


#pragma mark - Symbol Implementations.


Symbol::Symbol(std::string name, SymbolCategory category, Type type) : m_name(name), m_category(category), m_type(type), m_scopeNode(nullptr)
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


#pragma mark - Class BuiltInTypeSymbol

BuiltInTypeSymbol::BuiltInTypeSymbol(std::string name) : Symbol(name, SymbolCategory::tSymbolCategoryType, Type::tTypeUnknown)
{

}


#pragma mark - Class VariableSymbol

VariableSymbol::VariableSymbol(std::string name, Type type) : Symbol(name, SymbolCategory::tSymbolCategoryVariable, type)
{

}


#pragma mark - Class FuncArgSymbol

FuncArgSymbol::FuncArgSymbol(std::string name, Type type) : Symbol(name, SymbolCategory::tSymbolCategoryFunctionArgument, type)
{

}


#pragma mark - Class FunctionSymbol

FunctionSymbol::FunctionSymbol(std::string name, Type type) : Symbol(name, SymbolCategory::tSymbolCategoryFunction, type)
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


ScopeNode::ScopeNode(std::string name, ScopeNode * enclosingScope) : m_name(name), m_enclosingScope(enclosingScope)
{
    // In scope tree, child is always connect itself to parent.
    // Because of that, child should add itself to parents childs list.
    // In fact, parent never needs to know it's childs since childs points to parent due to nature of the scope tree.
    // But we want parent node knows it's child since we need to delete child nodes when we delete scope node root node.

    if (enclosingScope != nullptr)
    {
        enclosingScope->AddChild(this);
    }
}


ScopeNode::~ScopeNode()
{
    // Delete all childs.
    for (auto child : m_childs)
    {
        // Delete all symbol objects.
        for (auto pair : m_symbolTable)
        {
            // Has table pair.first = key, pair.second = symbol
            delete pair.second;
        }
        
        // Clear symbol table.
        m_symbolTable.clear();
        
        delete child;
    }

    m_childs.clear();
}


bool ScopeNode::IsDefined(std::string symbolName)
{
    // Return true if the symbol is exist. Othersie, false.
    return  m_symbolTable.find(symbolName) != m_symbolTable.end();
}


void  ScopeNode::InsertSymbol(Symbol *  symbol)
{
    // No duplicate symbol is allowed. Program should check before adding new symbol.
    assert(m_symbolTable.find(symbol->GetName()) == m_symbolTable.end());

    // Add symbol to the symbol table. We basically, define a new symbol in this scope.
    m_symbolTable[symbol->GetName()] = symbol;

    // Set scope for the symbol. Each symbol should know which scope are they in.
    symbol->SetScope(this);
}


Symbol *  ScopeNode::ResolveSymbol(std::string symbolName)
{
    // Check if symbol is available in symbol table.
    auto pair = m_symbolTable.find(symbolName);

    // Return if the symbol is exist.
    if ( pair != m_symbolTable.end())
    {
        return pair->second;
    }

    // If can't find in this scope then check enclosing scopes.
    if ( m_enclosingScope != nullptr )
    {
        return m_enclosingScope->ResolveSymbol(symbolName);
    }

    // Not found.
    return nullptr;
}


void ScopeNode::AddChild(ScopeNode * childNode)
{
    m_childs.emplace_back(childNode);
}


ScopeNode *  ScopeNode::GeEnclosingScope()
{
    return m_enclosingScope;
}

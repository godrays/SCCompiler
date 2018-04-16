//
//  Symbols.cpp
//
//  Created by Arkin Terli on 4/15/18.
//  Copyright © 2018 Arkin Terli. All rights reserved.
//

#include "Symbols.hpp"


using namespace SCCompiler;


#pragma mark - ScopeNode Implementations.


bool ScopeNode::IsDefined(std::string symbolName)
{
    // Return true if the symbol is exist. Othersie, false.
    return  m_symbolTable.find(symbolName) != m_symbolTable.end();
}


void  ScopeNode::InsertSymbol(Symbol *  symbol)
{
    // No duplicate symbol is allowed.
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

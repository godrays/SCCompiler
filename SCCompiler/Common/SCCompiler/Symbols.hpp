//
//  Symbols.hpp
//
//  Created by Arkin Terli on 4/15/18.
//  Copyright © 2018 Arkin Terli. All rights reserved.
//

#pragma once

#include <string>
#include <unordered_map>
#include "AST.hpp"


namespace SCCompiler
{
    class ScopeNode;

    #pragma mark - Enum SymbolType

    // Symbol category.
    enum SymbolCategory : uint32_t
    {
        tSymbolCategoryUnknown,
        tSymbolCategoryBuiltInType,
        tSymbolCategoryVariable,
        tSymbolCategoryFunction,
        tSymbolCategoryFunctionArgument,
    };


    #pragma mark - Class Symbol
    
    class Symbol
    {
    public:
        // Constructor.
        Symbol(std::string name, SymbolCategory category, AST::Type type) : m_name(name), m_category(category), m_type(type), m_scopeNode(nullptr) { }

        // Returns symbol name.
        std::string GetName() const     { return m_name; }

        // Returns symbol name.
        void SetScope(ScopeNode * scopeNode)     { m_scopeNode = scopeNode; }

    protected:
        // Symbol name.
        std::string  m_name;

        // Symbol category.
        SymbolCategory  m_category;

        // Symbol type.
        AST::Type   m_type;
        
        // Scope node.
        ScopeNode *  m_scopeNode;
    };


    #pragma mark - Class VariableSymbol
    
    class VariableSymbol : public Symbol
    {
    public:
        // Constructor.
        VariableSymbol(std::string name, AST::Type type) : Symbol(name, SymbolCategory::tSymbolCategoryVariable, type) { }
    };


    #pragma mark - Class FunctionSymbol
    
    class FunctionSymbol : public Symbol
    {
    public:
        // Constructor.
        FunctionSymbol(std::string name, AST::Type type) : Symbol(name, SymbolCategory::tSymbolCategoryFunction, type) { }
    };


    #pragma mark - Class FuncArgSymbol
    
    class FuncArgSymbol : public Symbol
    {
    public:
        // Constructor.
        FuncArgSymbol(std::string name, AST::Type type) : Symbol(name, SymbolCategory::tSymbolCategoryFunctionArgument, type) { }
    };


    #pragma mark - Class ScopeNode
    
    // Scoped symbol table node to build tree of symbol tables.
    // Every node in the tree is considered a scope and has a symbol table.
    class ScopeNode
    {
    public:
        // Constructor.
        ScopeNode(std::string name, ScopeNode * enclosingScope) : m_name(name), m_enclosingScope(enclosingScope) { }

        // Destructor
        ~ScopeNode() { }

        // Returns enclosing scope (child node of this node).
        ScopeNode *  GeEnclosingScope()     { return m_enclosingScope; }

        // Returns true if symbol is defined in this scope. Otherwise, false.
        bool  IsDefined(std::string symbolName);

        // Insert symbol.
        void  InsertSymbol(Symbol *  symbolNode);

        // Resolve symbol between current scope and global scope (root node).
        Symbol *  ResolveSymbol(std::string symbolName);

    protected:
        // Scope name.
        std::string   m_name;

        // Hash table for symbols.
        std::unordered_map<std::string, Symbol *>   m_symbolTable;

        // Enclosing scope that covers this scope.
        ScopeNode *   m_enclosingScope;
    };

}

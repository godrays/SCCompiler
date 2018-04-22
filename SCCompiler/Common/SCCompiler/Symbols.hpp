//
//  Symbols.hpp
//
//  Created by Arkin Terli on 4/15/18.
//  Copyright © 2018 Arkin Terli. All rights reserved.
//

#pragma once

#include <string>
#include <cassert>
#include <vector>
#include <unordered_map>

#include "Types.hpp"


namespace SCCompiler
{
    // Forward declaration.
    class ScopeNode;
    class FuncArgSymbol;
    
    #pragma mark - Enum SymbolType

    // Symbol category.
    enum SymbolCategory : uint32_t
    {
        tSymbolCategoryUnknown,
        tSymbolCategoryType,
        tSymbolCategoryVariable,
        tSymbolCategoryFunction,
        tSymbolCategoryFunctionArgument,
    };


    #pragma mark - Class Symbol
    
    class Symbol
    {
    public:
        // Constructor.
        Symbol(std::string name, SymbolCategory category, Type type);

        // Returns symbol name.
        std::string GetName() const;

        // Returns symbol type.
        Type GetType() const;

        // Returns symbol name.
        void SetScope(ScopeNode * scopeNode);

        // Returns symbol category.
        SymbolCategory GetCategory();

    protected:
        // Symbol name.
        std::string  m_name;

        // Symbol category.
        SymbolCategory  m_category;

        // Symbol type.
        Type   m_type;
        
        // Scope node.
        ScopeNode *  m_scopeNode;
    };


    #pragma mark - Class BuiltInTypeSymbol
    
    class BuiltInTypeSymbol : public Symbol
    {
    public:
        // Constructor.
        BuiltInTypeSymbol(std::string name);
    };


    #pragma mark - Class VariableSymbol
    
    class VariableSymbol : public Symbol
    {
    public:
        // Constructor.
        VariableSymbol(std::string name, Type type);
    };


    #pragma mark - Class FuncArgSymbol
    
    class FuncArgSymbol : public Symbol
    {
    public:
        // Constructor.
        FuncArgSymbol(std::string name, Type type);
    };


    #pragma mark - Class FunctionSymbol
    
    class FunctionSymbol : public Symbol
    {
    public:
        // Constructor.
        FunctionSymbol(std::string name, Type type);

        // Add function argument symbol.
        void AddArgumentSymbol(FuncArgSymbol * argSymbol);

        // Return argument count.
        size_t ArgumentCount();

        // Return function argument symbol at index.
        FuncArgSymbol * GetArgumentSymbol(size_t index);

    private:
        std::vector<FuncArgSymbol *>  m_argumentSymbols;
    };


    #pragma mark - Class ScopeNode
    
    // Scoped symbol table node to build tree of symbol tables.
    // Every node in the tree is considered a scope and has a symbol table.
    class ScopeNode
    {
    public:
        // Constructor.
        ScopeNode(std::string name, ScopeNode * enclosingScope);

        // Destructor
        ~ScopeNode();

        // Add child scope node.
        void AddChild(ScopeNode * childNode);

        // Returns enclosing scope (child node of this node).
        ScopeNode *  GeEnclosingScope();

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

        // Stores child scope nodes. We only needs this for deleting scope node tree.
        std::vector<ScopeNode *>    m_childs;
    };

}

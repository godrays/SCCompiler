//
//  Created by Arkin Terli on 4/15/18.
//  Copyright © 2018-Present, Arkin Terli. All rights reserved.
//

#pragma once

// Project includes
#include "Types.hpp"
// External includes
// System includes
#include <cassert>
#include <string>
#include <unordered_map>
#include <vector>


namespace scc
{

// Forward declaration.
class ScopeNode;
class FuncArgSymbol;


// Symbol category.
enum class SymbolCategory
{
    kSymbolCategoryUnknown,
    kSymbolCategoryType,
    kSymbolCategoryVariable,
    kSymbolCategoryFunction,
    kSymbolCategoryFunctionArgument,
};


class SymbolPropertyBase
{
public:
    // Destructor
    virtual ~SymbolPropertyBase() = default;
};


class Symbol
{
public:
    // Constructor.
    Symbol(std::string name, SymbolCategory category, Type type);

    // Destructor.
    virtual ~Symbol() = default;

    // Returns symbol name.
    std::string GetName() const;

    // Returns symbol type.
    Type GetType() const;

    // Returns symbol name.
    void SetScope(ScopeNode * scopeNode);

    // Returns symbol category.
    SymbolCategory GetCategory();

    // Get Property.
    SymbolPropertyBase * GetProperty();

    // Set Property.
    void SetProperty(SymbolPropertyBase * property);

protected:
    // Symbol name.
    std::string  m_name;

    // Symbol category.
    SymbolCategory  m_category;

    // Symbol type.
    Type   m_type;

    // Scope node.
    ScopeNode *  m_scopeNode;

    // Scope Property.
    SymbolPropertyBase *  m_property;
};


class BuiltInTypeSymbol : public Symbol
{
public:
    // Constructor.
    explicit BuiltInTypeSymbol(std::string name);
};


class VariableSymbol : public Symbol
{
public:
    // Constructor.
    VariableSymbol(std::string name, Type type);
};


class FuncArgSymbol : public Symbol
{
public:
    // Constructor.
    FuncArgSymbol(std::string name, Type type);
};


class FunctionSymbol : public Symbol
{
public:
    // Constructor.
    FunctionSymbol(std::string name, Type type);

    // Adds a function argument symbol.
    void AddArgumentSymbol(FuncArgSymbol * argSymbol);

    // Returns the argument count.
    size_t ArgumentCount();

    // Returns the function argument symbol at the given index.
    FuncArgSymbol * GetArgumentSymbol(size_t index);

private:
    std::vector<FuncArgSymbol *>  m_argumentSymbols;
};


// Scope category.
enum class ScopeCategory
{
    kScopeCategoryUnknown,
    kScopeCategoryGlobal,
    kScopeCategoryFunction,
    kScopeCategoryFor,
    kScopeCategoryBlock,
};


// Scoped symbol table node to build a tree of symbol tables.
// Every node in the tree is considered a scope and has a symbol table.
class ScopeNode
{
public:
    // Constructor.
    ScopeNode(ScopeCategory category, ScopeNode * enclosingScope);

    // Destructor.
    ~ScopeNode();

    // Get scope category.
    ScopeCategory GetCategory();

    // Add a child scope node.
    void AddChild(ScopeNode * childNode);

    // Returns the enclosing scope (parent node of this node).
    ScopeNode * GetEnclosingScope();

    // Returns true if the symbol is defined in this scope. Otherwise, false.
    bool  IsDefined(const std::string& symbolName);

    // Insert a symbol.
    void  InsertSymbol(Symbol *  symbolNode);

    // Resolve a symbol between the current scope and the global scope (root node).
    Symbol *  ResolveSymbol(const std::string& symbolName);

protected:
    // Scope category.
    ScopeCategory   m_category;

    // Hash table for symbols.
    std::unordered_map<std::string, Symbol *>   m_symbolTable;

    // Enclosing scope that covers this scope.
    ScopeNode *   m_enclosingScope;

    // Stores child scope nodes. We only need this for deleting the scope node tree.
    std::vector<ScopeNode *>    m_children;
};

}

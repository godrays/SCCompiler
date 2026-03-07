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
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>


namespace scc
{

// Forward declaration.
class ScopeNode;
class FunctionArgumentSymbol;


// Symbol category.
enum class SymbolCategory
{
    kUnknown,
    kType,
    kVariable,
    kFunction,
    kFunctionArgument,
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
    std::string getName() const;

    // Returns symbol type.
    Type getType() const;

    // Returns symbol name.
    void setScope(ScopeNode * scopeNode);

    // Returns symbol category.
    SymbolCategory getCategory();

    // Get Property.
    SymbolPropertyBase * getProperty();

    // Set Property.
    void setProperty(std::unique_ptr<SymbolPropertyBase> property);

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
    std::unique_ptr<SymbolPropertyBase>  m_property;
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


class FunctionArgumentSymbol : public Symbol
{
public:
    // Constructor.
    FunctionArgumentSymbol(std::string name, Type type);
};


class FunctionSymbol : public Symbol
{
public:
    // Constructor.
    FunctionSymbol(std::string name, Type type);

    // Adds a function argument symbol.
    void addArgumentSymbol(FunctionArgumentSymbol * argSymbol);

    // Returns the argument count.
    size_t argumentCount();

    // Returns the function argument symbol at the given index.
    FunctionArgumentSymbol * getArgumentSymbol(size_t index);

private:
    std::vector<FunctionArgumentSymbol *>  m_argumentSymbols;
};


// Scope category.
enum class ScopeCategory
{
    kUnknown,
    kGlobal,
    kFunction,
    kFor,
    kBlock,
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
    ScopeCategory getCategory();

    // Add a child scope node.
    ScopeNode * addChild(std::unique_ptr<ScopeNode> childNode);

    // Creates and adds a child scope node.
    ScopeNode * createChildScope(ScopeCategory category);

    // Returns the enclosing scope (parent node of this node).
    ScopeNode * getEnclosingScope();

    // Returns true if the symbol is defined in this scope. Otherwise, false.
    bool  isDefined(const std::string& symbolName);

    // Insert a symbol.
    Symbol * insertSymbol(std::unique_ptr<Symbol> symbolNode);

    // Resolve a symbol between the current scope and the global scope (root node).
    Symbol *  resolveSymbol(const std::string& symbolName);

protected:
    ScopeCategory   m_category;                                 // Scope category.
    std::unordered_map<std::string, std::unique_ptr<Symbol>>   m_symbolTable;  // Hash table for symbols.
    ScopeNode *   m_enclosingScope;                             // Enclosing scope that covers this scope.
    std::vector<std::unique_ptr<ScopeNode>>    m_children;      // Stores child scope nodes.
};

}

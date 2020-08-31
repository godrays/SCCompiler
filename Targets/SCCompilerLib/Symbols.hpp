//
//  Symbols.hpp
//
//  Created by Arkin Terli on 4/15/18.
//  Copyright © 2018-Present, Arkin Terli. All rights reserved.
//

#pragma once

#include <cassert>
#include <string>
#include <unordered_map>
#include <vector>

#include "Types.hpp"


namespace scc
{

// Forward declaration.
class ScopeNode;
class FuncArgSymbol;


#pragma mark - Enum SymbolType

// Symbol category.
enum SymbolCategory : uint32_t
{
    kSymbolCategoryUnknown,
    kSymbolCategoryType,
    kSymbolCategoryVariable,
    kSymbolCategoryFunction,
    kSymbolCategoryFunctionArgument,
};


#pragma mark - Class BaseSymbolProperty

class SymbolPropertyBase
{
public:
    // Destructor
    virtual ~SymbolPropertyBase() = default;
};


#pragma mark - Class Symbol

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


#pragma mark - Class BuiltInTypeSymbol

class BuiltInTypeSymbol : public Symbol
{
public:
    // Constructor.
    explicit BuiltInTypeSymbol(std::string name);
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


#pragma mark - Enum ScopeCategory

// Scope category.
enum ScopeCategory : uint32_t
{
    kScopeCategoryUnknown,
    kScopeCategoryGlobal,
    kScopeCategoryFunction,
    kScopeCategoryFor,
    kScopeCategoryBlock,
};


#pragma mark - Enum ScopeNode

// Scoped symbol table node to build tree of symbol tables.
// Every node in the tree is considered a scope and has a symbol table.
class ScopeNode
{
public:
    // Constructor.
    ScopeNode(ScopeCategory category, ScopeNode * enclosingScope);

    // Destructor
    ~ScopeNode();

    // Get scope category.
    ScopeCategory GetCategory();

    // Add child scope node.
    void AddChild(ScopeNode * childNode);

    // Returns enclosing scope (child node of this node).
    ScopeNode *  GeEnclosingScope();

    // Returns true if symbol is defined in this scope. Otherwise, false.
    bool  IsDefined(const std::string& symbolName);

    // Insert symbol.
    void  InsertSymbol(Symbol *  symbolNode);

    // Resolve symbol between current scope and global scope (root node).
    Symbol *  ResolveSymbol(const std::string& symbolName);

protected:
    // Scope category.
    ScopeCategory   m_category;

    // Hash table for symbols.
    std::unordered_map<std::string, Symbol *>   m_symbolTable;

    // Enclosing scope that covers this scope.
    ScopeNode *   m_enclosingScope;

    // Stores child scope nodes. We only needs this for deleting scope node tree.
    std::vector<ScopeNode *>    m_childs;
};

}

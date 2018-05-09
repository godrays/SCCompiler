//
//  SymbolDefPass.cpp
//
//  Created by Arkin Terli on 4/15/18.
//  Copyright © 2018 Arkin Terli. All rights reserved.
//

#include "AST.hpp"
#include "Symbols.hpp"
#include "SymbolDefPass.hpp"
#include "Exceptions.hpp"

using namespace SCCompiler;


#pragma mark - SymbolefPass Implementations.


ScopeNode * SymbolDefPass::CreateScopeTree(AST::Node * node)
{
    ScopeNode *  scopeTreeHead = new ScopeNode(ScopeCategory::cScopeCategoryGlobal, nullptr);
    m_currentScope = scopeTreeHead;

    // Add Built-In Types. They have no type definition.
    auto typeSymbol = new BuiltInTypeSymbol("float");
    typeSymbol->SetScope(m_currentScope);
    m_currentScope->InsertSymbol(typeSymbol);
    
    typeSymbol = new BuiltInTypeSymbol("int");
    typeSymbol->SetScope(m_currentScope);
    m_currentScope->InsertSymbol(typeSymbol);

    typeSymbol = new BuiltInTypeSymbol("bool");
    typeSymbol->SetScope(m_currentScope);
    m_currentScope->InsertSymbol(typeSymbol);

    typeSymbol = new BuiltInTypeSymbol("void");
    typeSymbol->SetScope(m_currentScope);
    m_currentScope->InsertSymbol(typeSymbol);

    // Visit nodes to defined symbols.
    Visit(node);
    
    return scopeTreeHead;
}


void SymbolDefPass::Visit(AST::Node * node)
{
    // Set current scope for the node before visiting.
    node->SetScope(m_currentScope);

    switch(node->GetNodeType())
    {
        case AST::NodeType::tNodeTypeVariableDeclaration:
            VisitVariableDeclaration(dynamic_cast<AST::NodeVarDeclaration *>(node));
            break;

        case AST::NodeType::tNodeTypeFunctionDeclaration:
            VisitFunctionDeclaration(dynamic_cast<AST::NodeFuncDeclaration *>(node));
            break;

        case AST::NodeType::tNodeTypeBlock:
            VisitBlock(static_cast<AST::NodeBlock *>(node));
            break;

        case AST::NodeType::tNodeTypeProgram:
        case AST::NodeType::tNodeTypeReturnStatement:
        case AST::NodeType::tNodeTypeFuncCall:
        case AST::NodeType::tNodeTypeAssignment:
        case AST::NodeType::tNodeTypeAOPMul:
        case AST::NodeType::tNodeTypeAOPDiv:
        case AST::NodeType::tNodeTypeAOPAdd:
        case AST::NodeType::tNodeTypeAOPSub:
        case AST::NodeType::tNodeTypeLiteralFloat:
        case AST::NodeType::tNodeTypeLiteralInt32:
        case AST::NodeType::tNodeTypeLiteralBool:
        case AST::NodeType::tNodeTypeLiteralID:
            VisitChilds(node);
            break;

        default:
            assert(false && "Unknown node type in SymbolDefPass.");
            break;
    }
}


void SymbolDefPass::VisitChilds(AST::Node * node)
{
    // Visit node children.
    for (size_t index=0; index<node->ChildCount(); ++index)
    {
        Visit(node->GetChild(index));
    }
}


void SymbolDefPass::SymbolDefPass::VisitVariableDeclaration(AST::NodeVarDeclaration * node)
{
    auto symbolName = node->GetVarName();
    auto symbolType = node->GetVarType();

    // Symbol redefinition is not allowed.
    if (m_currentScope->IsDefined(symbolName))
    {
        throw SemanticErrorException("Redefinition of a symbol: " + symbolName);
    }
    
    auto symbol = new VariableSymbol(symbolName, symbolType);
    symbol->SetScope(m_currentScope);
    // Define new symbol.
    m_currentScope->InsertSymbol(symbol);
    
    VisitChilds(node);
}


void SymbolDefPass::SymbolDefPass::VisitFunctionDeclaration(AST::NodeFuncDeclaration * node)
{
    // ADD FUNCTION SYMBOL TO CURRENT SCOPE
    
    auto funcSymbolName = node->GetFuncName();
    auto funcSymbolType = node->GetReturnType();

    // Symbol redefinition is not allowed.
    if (m_currentScope->IsDefined(funcSymbolName))
    {
        throw SemanticErrorException("Redefinition of a symbol: " + funcSymbolName);
    }
    
    auto funcSymbol = new FunctionSymbol(funcSymbolName, funcSymbolType);
    funcSymbol->SetScope(m_currentScope);
    // Define function symbol.
    m_currentScope->InsertSymbol(funcSymbol);

    // CREATE NEW SCOPE FOR FUNCTION
    
    m_currentScope = new ScopeNode(ScopeCategory::cScopeCategoryFunction, m_currentScope);

    // Add function arguments to function scope.
    auto arguments = node->GetArguments();
    for (size_t index=0; index < arguments.size(); ++index)
    {
        auto argName = arguments[index].GetName();
        auto argType = arguments[index].GetType();

        // Symbol redefinition is not allowed.
        if (m_currentScope->IsDefined(argName))
        {
            throw SemanticErrorException("Redefinition of a symbol: " + argName);
        }

        auto argSymbol = new FuncArgSymbol(argName, argType);
        argSymbol->SetScope(m_currentScope);
        // Define new symbol.
        m_currentScope->InsertSymbol(argSymbol);

        // Add argument symbol to function symbol to track arguments.
        funcSymbol->AddArgumentSymbol(argSymbol);
    }

    // Visit function childs
    VisitChilds(node);

    // LEAVE SCOPE OF FUNCTION
    
    m_currentScope = m_currentScope->GeEnclosingScope();
}


void SymbolDefPass::SymbolDefPass::VisitBlock(AST::NodeBlock * node)
{
    // CREATE NEW SCOPE FOR FUNCTION
    m_currentScope = new ScopeNode(ScopeCategory::cScopeCategoryBlock, m_currentScope);

    // Visit function childs
    VisitChilds(node);

    // LEAVE SCOPE OF FUNCTION
    m_currentScope = m_currentScope->GeEnclosingScope();
}

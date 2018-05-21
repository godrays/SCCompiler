//
//  SymbolDefPass.cpp
//
//  Created by Arkin Terli on 4/15/18.
//  Copyright © 2018 Arkin Terli. All rights reserved.
//

#include <sstream>

#include "AST.hpp"
#include "Symbols.hpp"
#include "SymbolDefPass.hpp"
#include "Exceptions.hpp"

using namespace scc;


#pragma mark - SymbolefPass Implementations.

ScopeNode * SymbolDefPass::CreateScopeTree(ast::Node * node)
{
    ScopeNode *  scopeTreeHead = new ScopeNode(ScopeCategory::kScopeCategoryGlobal, nullptr);
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


void SymbolDefPass::Visit(ast::Node * node)
{
    // Set current scope for the node before visiting.
    node->SetScope(m_currentScope);

    switch(node->GetNodeType())
    {
        case ast::NodeType::kNodeTypeVariableDeclaration:
            VisitVariableDeclaration(dynamic_cast<ast::NodeVarDeclaration *>(node));
            break;

        case ast::NodeType::kNodeTypeFunctionDeclaration:
            VisitFunctionDeclaration(dynamic_cast<ast::NodeFuncDeclaration *>(node));
            break;

        case ast::NodeType::kNodeTypeBlock:
            VisitBlock(static_cast<ast::NodeBlock *>(node));
            break;

        case ast::NodeType::kNodeTypeFuncCall:
            VisitFunctionCall(static_cast<ast::NodeFuncCall *>(node));
            break;

        case ast::NodeType::kNodeTypeLiteralID:
            VisitLiteral(static_cast<ast::NodeLiteral *>(node));
            break;

        case ast::NodeType::kNodeTypeProgram:
        case ast::NodeType::kNodeTypeReturnStatement:
        case ast::NodeType::kNodeTypeAssignment:
        case ast::NodeType::kNodeTypeAOPMul:
        case ast::NodeType::kNodeTypeAOPDiv:
        case ast::NodeType::kNodeTypeAOPAdd:
        case ast::NodeType::kNodeTypeAOPSub:
        case ast::NodeType::kNodeTypeLiteralFloat:
        case ast::NodeType::kNodeTypeLiteralInt32:
        case ast::NodeType::kNodeTypeLiteralBool:
            VisitChilds(node);
            break;
            
        default:
            assert(false && "Unknown node type in SymbolDefPass.");
            break;
    }
}


void SymbolDefPass::VisitChilds(ast::Node * node)
{
    // Visit node children.
    for (size_t index=0; index<node->ChildCount(); ++index)
    {
        Visit(node->GetChild(index));
    }
}


void SymbolDefPass::SymbolDefPass::VisitVariableDeclaration(ast::NodeVarDeclaration * node)
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


void SymbolDefPass::SymbolDefPass::VisitFunctionDeclaration(ast::NodeFuncDeclaration * node)
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
    
    m_currentScope = new ScopeNode(ScopeCategory::kScopeCategoryFunction, m_currentScope);

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


void SymbolDefPass::SymbolDefPass::VisitBlock(ast::NodeBlock * node)
{
    // CREATE NEW SCOPE FOR FUNCTION
    m_currentScope = new ScopeNode(ScopeCategory::kScopeCategoryBlock, m_currentScope);

    // Visit function childs
    VisitChilds(node);

    // LEAVE SCOPE OF FUNCTION
    m_currentScope = m_currentScope->GeEnclosingScope();
}


void SymbolDefPass::VisitFunctionCall(ast::NodeFuncCall * node)
{
    // Rule: Function name must resolve (must defined).
    auto scope = node->GetScope();
    auto symbol = static_cast<FunctionSymbol *>(scope->ResolveSymbol(node->GetFuncName()));
    if (!symbol)
    {
        std::stringstream   message;
        message << "Line: " << node->GetSourceCodeLine() << " - Use of undeclared identifier: " << node->GetFuncName() << std::endl;
        throw SemanticErrorException(message.str());
    }
}


void SymbolDefPass::VisitLiteral(ast::NodeLiteral * node)
{
    
    switch (node->GetNodeType())
    {
        case ast::NodeType::kNodeTypeLiteralFloat:
        case ast::NodeType::kNodeTypeLiteralInt32:
        case ast::NodeType::kNodeTypeLiteralBool:
        // Nothing to do with other literal types.
        break;
        
        case ast::NodeType::kNodeTypeLiteralID:
        {
            // Rule: Resolve variable name. It has to be defined before it's used.
            auto scope = node->GetScope();
            auto symbol = scope->ResolveSymbol(node->GetValue());
            if (!symbol)
            {
                std::stringstream   message;
                message << "Line: " << node->GetSourceCodeLine() << " - Use of undeclared identifier: " << node->GetValue() << std::endl;
                throw SemanticErrorException(message.str());
            }
        }
        break;
        
        default:
            assert(false && "Unknown node type in SemanticPass::VisitLiteral");
        break;
    }

    // This node should have no children.
    assert(node->ChildCount() == 0);
}

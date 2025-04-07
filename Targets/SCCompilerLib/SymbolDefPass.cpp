//
//  Created by Arkin Terli on 4/15/18.
//  Copyright © 2018-Present, Arkin Terli. All rights reserved.
//

// Project includes
#include "SymbolDefPass.hpp"
#include "AST.hpp"
#include "Exceptions.hpp"
#include "Symbols.hpp"
#include "Utils.hpp"
// External includes
// System includes
#include <sstream>


using namespace scc;


ScopeNode * SymbolDefPass::CreateScopeTree(ast::Node * node)
{
    auto scopeTreeHead = new ScopeNode(ScopeCategory::kScopeCategoryGlobal, nullptr);
    m_currentScope = scopeTreeHead;

    // Add Built-In Types. They have no type definitions.
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
    // Sets the current scope for the node before visiting.
    node->SetScope(m_currentScope);

    switch(node->GetNodeType())
    {
        case ast::NodeType::kNodeTypeVariableDeclaration:
            VisitVariableDeclaration(dynamic_cast<ast::NodeVarDeclaration *>(node));
            break;

        case ast::NodeType::kNodeTypeFunctionDeclaration:
            VisitFunctionDeclaration(dynamic_cast<ast::NodeFuncDeclaration *>(node));
            break;

        case ast::NodeType::kNodeTypeForStatement:
            VisitForStatement(dynamic_cast<ast::NodeForStatement *>(node));
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
        case ast::NodeType::kNodeTypeContinue:
        case ast::NodeType::kNodeTypeBreak:
        case ast::NodeType::kNodeTypeAssignment:
        case ast::NodeType::kNodeTypeIfStatement:
        case ast::NodeType::kNodeTypeForVarDecl:
        case ast::NodeType::kNodeTypeForCondition:
        case ast::NodeType::kNodeTypeForIncrement:
        case ast::NodeType::kNodeTypeWhileStatement:
        case ast::NodeType::kNodeTypeDoWhileStatement:
        case ast::NodeType::kNodeTypeExplicitTypeConversion:
        case ast::NodeType::kNodeTypeLogicalNotOP:
        case ast::NodeType::kNodeTypeLogicalAndOP:
        case ast::NodeType::kNodeTypeLogicalOrOP:
        case ast::NodeType::kNodeTypeUOPPlus:
        case ast::NodeType::kNodeTypeUOPMinus:
        case ast::NodeType::kNodeTypeCompOPEQ:
        case ast::NodeType::kNodeTypeCompOPNEQ:
        case ast::NodeType::kNodeTypeCompOPLE:
        case ast::NodeType::kNodeTypeCompOPGE:
        case ast::NodeType::kNodeTypeCompOPL:
        case ast::NodeType::kNodeTypeCompOPG:
        case ast::NodeType::kNodeTypePrefixIncAOP:
        case ast::NodeType::kNodeTypePrefixDecAOP:
        case ast::NodeType::kNodeTypeAOPMul:
        case ast::NodeType::kNodeTypeAOPDiv:
        case ast::NodeType::kNodeTypeAOPAdd:
        case ast::NodeType::kNodeTypeAOPSub:
        case ast::NodeType::kNodeTypeLiteralFloat:
        case ast::NodeType::kNodeTypeLiteralInt32:
        case ast::NodeType::kNodeTypeLiteralBool:
            VisitChildren(node);
            break;
            
        default:
            assert(false && "Unknown node type in SymbolDefPass.");
            break;
    }
}


void SymbolDefPass::VisitChildren(ast::Node * node)
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
    throw_if(m_currentScope->IsDefined(symbolName),
             SemanticErrorException("Line: ", node->GetSourceCodeLine(), " - Redefinition of a symbol: ", symbolName));

    auto symbol = new VariableSymbol(symbolName, symbolType);
    symbol->SetScope(m_currentScope);
    // Define new symbol.
    m_currentScope->InsertSymbol(symbol);

    VisitChildren(node);
}


void SymbolDefPass::SymbolDefPass::VisitFunctionDeclaration(ast::NodeFuncDeclaration * node)
{
    // ADD FUNCTION SYMBOL TO CURRENT SCOPE
    
    auto funcSymbolName = node->GetFuncName();
    auto funcSymbolType = node->GetReturnType();

    // Symbol redefinition is not allowed.
    throw_if(m_currentScope->IsDefined(funcSymbolName),
             SemanticErrorException("Line: ", node->GetSourceCodeLine(), " - Redefinition of a symbol: ", funcSymbolName));

    auto funcSymbol = new FunctionSymbol(funcSymbolName, funcSymbolType);
    funcSymbol->SetScope(m_currentScope);
    // Define the function symbol.
    m_currentScope->InsertSymbol(funcSymbol);

    // CREATE A NEW SCOPE FOR THE FUNCTION

    m_currentScope = new ScopeNode(ScopeCategory::kScopeCategoryFunction, m_currentScope);

    // Add function arguments to the function scope.
    auto arguments = node->GetArguments();
    for (auto & argument : arguments)
    {
        auto argName = argument.GetName();
        auto argType = argument.GetType();

        // Symbol redefinition is not allowed.
        throw_if(m_currentScope->IsDefined(argName),
                 SemanticErrorException("Line: ", node->GetSourceCodeLine(), " - Redefinition of a symbol: ", argName));

        auto argSymbol = new FuncArgSymbol(argName, argType);
        argSymbol->SetScope(m_currentScope);
        // Define the new symbol.
        m_currentScope->InsertSymbol(argSymbol);

        // Add the argument symbol to the function symbol to track arguments.
        funcSymbol->AddArgumentSymbol(argSymbol);
    }

    // Visit the function's children
    VisitChildren(node);

    // LEAVE THE SCOPE OF THE FUNCTION

    m_currentScope = m_currentScope->GetEnclosingScope();
}


void SymbolDefPass::VisitForStatement(ast::NodeForStatement * node)
{
    // CREATE A NEW SCOPE FOR THE 'FOR' STATEMENT

    m_currentScope = new ScopeNode(ScopeCategory::kScopeCategoryFor, m_currentScope);

    // Visit the children
    VisitChildren(node);

    // LEAVE THE SCOPE OF THE 'FOR' STATEMENT

    m_currentScope = m_currentScope->GetEnclosingScope();
}


void SymbolDefPass::SymbolDefPass::VisitBlock(ast::NodeBlock * node)
{
    // CREATE A NEW SCOPE FOR THE 'BLOCK'
    m_currentScope = new ScopeNode(ScopeCategory::kScopeCategoryBlock, m_currentScope);

    // Visit the children
    VisitChildren(node);

    // LEAVE THE SCOPE OF THE 'BLOCK'
    m_currentScope = m_currentScope->GetEnclosingScope();
}


void SymbolDefPass::VisitFunctionCall(ast::NodeFuncCall * node)
{
    // Rule: The function name must be resolved (must be defined).
    auto scope = node->GetScope();
    auto symbol = static_cast<FunctionSymbol *>(scope->ResolveSymbol(node->GetFuncName()));
    throw_if(!symbol,
             SemanticErrorException("Line: ", node->GetSourceCodeLine(), " - Use of an undeclared identifier: ",
                                    node->GetFuncName()));

    VisitChildren(node);
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
                // Rule: Resolve the variable name. It has to be defined before it is used.
                auto scope = node->GetScope();
                auto symbol = scope->ResolveSymbol(node->GetValue());
                throw_if(!symbol,
                         SemanticErrorException("Line: ", node->GetSourceCodeLine(),
                                                " - Use of an undeclared identifier: ", node->GetValue()));
            }
            break;

        default:
            assert(false && "Unknown node type in SemanticPass::VisitLiteral");
            break;
    }

    // This node should have no children.
    assert(node->ChildCount() == 0);
}
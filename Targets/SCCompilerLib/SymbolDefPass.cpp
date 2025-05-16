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


ScopeNode * SymbolDefPass::createScopeTree(ast::Node * node)
{
    auto scopeTreeHead = new ScopeNode(ScopeCategory::kScopeCategoryGlobal, nullptr);
    m_currentScope = scopeTreeHead;

    // Add Built-In Types. They have no type definitions.
    auto typeSymbol = new BuiltInTypeSymbol("float");
    typeSymbol->setScope(m_currentScope);
    m_currentScope->insertSymbol(typeSymbol);
    
    typeSymbol = new BuiltInTypeSymbol("int");
    typeSymbol->setScope(m_currentScope);
    m_currentScope->insertSymbol(typeSymbol);

    typeSymbol = new BuiltInTypeSymbol("bool");
    typeSymbol->setScope(m_currentScope);
    m_currentScope->insertSymbol(typeSymbol);

    typeSymbol = new BuiltInTypeSymbol("void");
    typeSymbol->setScope(m_currentScope);
    m_currentScope->insertSymbol(typeSymbol);

    // visit nodes to defined symbols.
    visit(node);
    
    return scopeTreeHead;
}


void SymbolDefPass::visit(ast::Node * node)
{
    // Sets the current scope for the node before visiting.
    node->setScope(m_currentScope);

    switch(node->getNodeType())
    {
        case ast::NodeType::kNodeTypeVariableDeclaration:
            visitVariableDeclaration(dynamic_cast<ast::NodeVarDeclaration *>(node));
            break;

        case ast::NodeType::kNodeTypeFunctionDeclaration:
            visitFunctionDeclaration(dynamic_cast<ast::NodeFuncDeclaration *>(node));
            break;

        case ast::NodeType::kNodeTypeForStatement:
            visitForStatement(dynamic_cast<ast::NodeForStatement *>(node));
            break;

        case ast::NodeType::kNodeTypeBlock:
            visitBlock(static_cast<ast::NodeBlock *>(node));
            break;

        case ast::NodeType::kNodeTypeFuncCall:
            visitFunctionCall(static_cast<ast::NodeFuncCall *>(node));
            break;

        case ast::NodeType::kNodeTypeLiteralID:
            visitLiteral(static_cast<ast::NodeLiteral *>(node));
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
            visitChildren(node);
            break;
            
        default:
            assert(false && "Unknown node type in SymbolDefPass.");
            break;
    }
}


void SymbolDefPass::visitChildren(ast::Node * node)
{
    // visit node children.
    for (size_t index=0; index<node->childCount(); ++index)
    {
        visit(node->getChild(index));
    }
}


void SymbolDefPass::SymbolDefPass::visitVariableDeclaration(ast::NodeVarDeclaration * node)
{
    auto symbolName = node->GetVarName();
    auto symbolType = node->GetVarType();

    // Symbol redefinition is not allowed.
    throw_if(m_currentScope->isDefined(symbolName),
             SemanticErrorException("Line: ", node->getSourceCodeLine(), " - Redefinition of a symbol: ", symbolName));

    auto symbol = new VariableSymbol(symbolName, symbolType);
    symbol->setScope(m_currentScope);
    // Define new symbol.
    m_currentScope->insertSymbol(symbol);

    visitChildren(node);
}


void SymbolDefPass::SymbolDefPass::visitFunctionDeclaration(ast::NodeFuncDeclaration * node)
{
    // ADD FUNCTION SYMBOL TO CURRENT SCOPE
    
    auto funcSymbolName = node->GetFuncName();
    auto funcSymbolType = node->GetReturnType();

    // Symbol redefinition is not allowed.
    throw_if(m_currentScope->isDefined(funcSymbolName),
             SemanticErrorException("Line: ", node->getSourceCodeLine(), " - Redefinition of a symbol: ", funcSymbolName));

    auto funcSymbol = new FunctionSymbol(funcSymbolName, funcSymbolType);
    funcSymbol->setScope(m_currentScope);
    // Define the function symbol.
    m_currentScope->insertSymbol(funcSymbol);

    // CREATE A NEW SCOPE FOR THE FUNCTION

    m_currentScope = new ScopeNode(ScopeCategory::kScopeCategoryFunction, m_currentScope);

    // Add function arguments to the function scope.
    auto arguments = node->GetArguments();
    for (auto & argument : arguments)
    {
        auto argName = argument.getName();
        auto argType = argument.getType();

        // Symbol redefinition is not allowed.
        throw_if(m_currentScope->isDefined(argName),
                 SemanticErrorException("Line: ", node->getSourceCodeLine(), " - Redefinition of a symbol: ", argName));

        auto argSymbol = new FuncArgSymbol(argName, argType);
        argSymbol->setScope(m_currentScope);
        // Define the new symbol.
        m_currentScope->insertSymbol(argSymbol);

        // Add the argument symbol to the function symbol to track arguments.
        funcSymbol->addArgumentSymbol(argSymbol);
    }

    // visit the function's children
    visitChildren(node);

    // LEAVE THE SCOPE OF THE FUNCTION

    m_currentScope = m_currentScope->getEnclosingScope();
}


void SymbolDefPass::visitForStatement(ast::NodeForStatement * node)
{
    // CREATE A NEW SCOPE FOR THE 'FOR' STATEMENT

    m_currentScope = new ScopeNode(ScopeCategory::kScopeCategoryFor, m_currentScope);

    // visit the children
    visitChildren(node);

    // LEAVE THE SCOPE OF THE 'FOR' STATEMENT

    m_currentScope = m_currentScope->getEnclosingScope();
}


void SymbolDefPass::SymbolDefPass::visitBlock(ast::NodeBlock * node)
{
    // CREATE A NEW SCOPE FOR THE 'BLOCK'
    m_currentScope = new ScopeNode(ScopeCategory::kScopeCategoryBlock, m_currentScope);

    // visit the children
    visitChildren(node);

    // LEAVE THE SCOPE OF THE 'BLOCK'
    m_currentScope = m_currentScope->getEnclosingScope();
}


void SymbolDefPass::visitFunctionCall(ast::NodeFuncCall * node)
{
    // Rule: The function name must be resolved (must be defined).
    auto scope = node->getScope();
    auto symbol = static_cast<FunctionSymbol *>(scope->resolveSymbol(node->GetFuncName()));
    throw_if(!symbol,
             SemanticErrorException("Line: ", node->getSourceCodeLine(), " - Use of an undeclared identifier: ",
                                    node->GetFuncName()));

    visitChildren(node);
}


void SymbolDefPass::visitLiteral(ast::NodeLiteral * node)
{
    switch (node->getNodeType())
    {
        case ast::NodeType::kNodeTypeLiteralFloat:
        case ast::NodeType::kNodeTypeLiteralInt32:
        case ast::NodeType::kNodeTypeLiteralBool:
            // Nothing to do with other literal types.
            break;

        case ast::NodeType::kNodeTypeLiteralID:
            {
                // Rule: Resolve the variable name. It has to be defined before it is used.
                auto scope = node->getScope();
                auto symbol = scope->resolveSymbol(node->GetValue());
                throw_if(!symbol,
                         SemanticErrorException("Line: ", node->getSourceCodeLine(),
                                                " - Use of an undeclared identifier: ", node->GetValue()));
            }
            break;

        default:
            assert(false && "Unknown node type in SemanticPass::visitLiteral");
            break;
    }

    // This node should have no children.
    assert(node->childCount() == 0);
}
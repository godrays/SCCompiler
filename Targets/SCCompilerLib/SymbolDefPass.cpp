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


std::unique_ptr<ScopeNode> SymbolDefPass::createScopeTree(ast::Node * node)
{
    auto scopeTreeHead = std::make_unique<ScopeNode>(ScopeCategory::kGlobal, nullptr);
    m_currentScope = scopeTreeHead.get();

    // Add Built-In Types. They have no type definitions.
    m_currentScope->insertSymbol(std::make_unique<BuiltInTypeSymbol>("float"));
    
    m_currentScope->insertSymbol(std::make_unique<BuiltInTypeSymbol>("int"));

    m_currentScope->insertSymbol(std::make_unique<BuiltInTypeSymbol>("bool"));

    m_currentScope->insertSymbol(std::make_unique<BuiltInTypeSymbol>("void"));

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
        case ast::NodeType::kVariableDeclaration:
            visitVariableDeclaration(dynamic_cast<ast::NodeVarDeclaration *>(node));
            break;

        case ast::NodeType::kFunctionDeclaration:
            visitFunctionDeclaration(dynamic_cast<ast::NodeFuncDeclaration *>(node));
            break;

        case ast::NodeType::kForStatement:
            visitForStatement(dynamic_cast<ast::NodeForStatement *>(node));
            break;

        case ast::NodeType::kBlock:
            visitBlock(static_cast<ast::NodeBlock *>(node));
            break;

        case ast::NodeType::kFuncCall:
            visitFunctionCall(static_cast<ast::NodeFuncCall *>(node));
            break;

        case ast::NodeType::kLiteralID:
            visitLiteral(static_cast<ast::NodeLiteral *>(node));
            break;

        case ast::NodeType::kProgram:
        case ast::NodeType::kReturnStatement:
        case ast::NodeType::kContinue:
        case ast::NodeType::kBreak:
        case ast::NodeType::kAssignment:
        case ast::NodeType::kIfStatement:
        case ast::NodeType::kForVarDecl:
        case ast::NodeType::kForCondition:
        case ast::NodeType::kForIncrement:
        case ast::NodeType::kWhileStatement:
        case ast::NodeType::kDoWhileStatement:
        case ast::NodeType::kExplicitTypeConversion:
        case ast::NodeType::kLogicalNotOP:
        case ast::NodeType::kLogicalAndOP:
        case ast::NodeType::kLogicalOrOP:
        case ast::NodeType::kUOPPlus:
        case ast::NodeType::kUOPMinus:
        case ast::NodeType::kCompOPEQ:
        case ast::NodeType::kCompOPNEQ:
        case ast::NodeType::kCompOPLE:
        case ast::NodeType::kCompOPGE:
        case ast::NodeType::kCompOPL:
        case ast::NodeType::kCompOPG:
        case ast::NodeType::kPrefixIncAOP:
        case ast::NodeType::kPrefixDecAOP:
        case ast::NodeType::kAOPMul:
        case ast::NodeType::kAOPDiv:
        case ast::NodeType::kAOPAdd:
        case ast::NodeType::kAOPSub:
        case ast::NodeType::kLiteralFloat:
        case ast::NodeType::kLiteralInt32:
        case ast::NodeType::kLiteralBool:
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


void SymbolDefPass::visitVariableDeclaration(ast::NodeVarDeclaration * node)
{
    auto symbolName = node->getVarName();
    auto symbolType = node->getVarType();

    // Symbol redefinition is not allowed.
    throw_if(m_currentScope->isDefined(symbolName),
             SemanticErrorException("Line: ", node->getSourceCodeLine(), " - Redefinition of a symbol: ", symbolName));

    // Define new symbol.
    m_currentScope->insertSymbol(std::make_unique<VariableSymbol>(symbolName, symbolType));

    visitChildren(node);
}


void SymbolDefPass::visitFunctionDeclaration(ast::NodeFuncDeclaration * node)
{
    // ADD FUNCTION SYMBOL TO CURRENT SCOPE
    
    auto funcSymbolName = node->getFuncName();
    auto funcSymbolType = node->getReturnType();

    // Symbol redefinition is not allowed.
    throw_if(m_currentScope->isDefined(funcSymbolName),
             SemanticErrorException("Line: ", node->getSourceCodeLine(), " - Redefinition of a symbol: ", funcSymbolName));

    // Define the function symbol.
    auto * funcSymbol = static_cast<FunctionSymbol *>(m_currentScope->insertSymbol(
        std::make_unique<FunctionSymbol>(funcSymbolName, funcSymbolType)));

    // CREATE A NEW SCOPE FOR THE FUNCTION

    m_currentScope = m_currentScope->createChildScope(ScopeCategory::kFunction);

    // Add function arguments to the function scope.
    auto arguments = node->getArguments();
    for (auto & argument : arguments)
    {
        auto argName = argument.getName();
        auto argType = argument.getType();

        // Symbol redefinition is not allowed.
        throw_if(m_currentScope->isDefined(argName),
                 SemanticErrorException("Line: ", node->getSourceCodeLine(), " - Redefinition of a symbol: ", argName));

        // Define the new symbol.
        auto * argSymbol = static_cast<FuncArgSymbol *>(m_currentScope->insertSymbol(
            std::make_unique<FuncArgSymbol>(argName, argType)));

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

    m_currentScope = m_currentScope->createChildScope(ScopeCategory::kFor);

    // visit the children
    visitChildren(node);

    // LEAVE THE SCOPE OF THE 'FOR' STATEMENT

    m_currentScope = m_currentScope->getEnclosingScope();
}


void SymbolDefPass::visitBlock(ast::NodeBlock * node)
{
    // CREATE A NEW SCOPE FOR THE 'BLOCK'
    m_currentScope = m_currentScope->createChildScope(ScopeCategory::kBlock);

    // visit the children
    visitChildren(node);

    // LEAVE THE SCOPE OF THE 'BLOCK'
    m_currentScope = m_currentScope->getEnclosingScope();
}


void SymbolDefPass::visitFunctionCall(ast::NodeFuncCall * node)
{
    // Rule: The function name must be resolved (must be defined).
    auto scope = node->getScope();
    auto symbol = static_cast<FunctionSymbol *>(scope->resolveSymbol(node->getFuncName()));
    throw_if(!symbol,
             SemanticErrorException("Line: ", node->getSourceCodeLine(), " - Use of an undeclared identifier: ",
                                    node->getFuncName()));

    visitChildren(node);
}


void SymbolDefPass::visitLiteral(ast::NodeLiteral * node)
{
    switch (node->getNodeType())
    {
        case ast::NodeType::kLiteralFloat:
        case ast::NodeType::kLiteralInt32:
        case ast::NodeType::kLiteralBool:
            // Nothing to do with other literal types.
            break;

        case ast::NodeType::kLiteralID:
            {
                // Rule: Resolve the variable name. It has to be defined before it is used.
                auto scope = node->getScope();
                auto symbol = scope->resolveSymbol(node->getValue());
                throw_if(!symbol,
                         SemanticErrorException("Line: ", node->getSourceCodeLine(),
                                                " - Use of an undeclared identifier: ", node->getValue()));
            }
            break;

        default:
            assert(false && "Unknown node type in SemanticPass::visitLiteral");
            break;
    }

    // This node should have no children.
    assert(node->childCount() == 0);
}
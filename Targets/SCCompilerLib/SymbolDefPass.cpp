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
    auto scopeTreeHead = new ScopeNode(ScopeCategory::kGlobal, nullptr);
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

    m_currentScope = new ScopeNode(ScopeCategory::kFunction, m_currentScope);

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

    m_currentScope = new ScopeNode(ScopeCategory::kFor, m_currentScope);

    // visit the children
    visitChildren(node);

    // LEAVE THE SCOPE OF THE 'FOR' STATEMENT

    m_currentScope = m_currentScope->getEnclosingScope();
}


void SymbolDefPass::SymbolDefPass::visitBlock(ast::NodeBlock * node)
{
    // CREATE A NEW SCOPE FOR THE 'BLOCK'
    m_currentScope = new ScopeNode(ScopeCategory::kBlock, m_currentScope);

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
        case ast::NodeType::kLiteralFloat:
        case ast::NodeType::kLiteralInt32:
        case ast::NodeType::kLiteralBool:
            // Nothing to do with other literal types.
            break;

        case ast::NodeType::kLiteralID:
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
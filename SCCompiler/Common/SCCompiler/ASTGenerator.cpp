//
//  ASTGenerator.cpp
//
//  Created by Arkin Terli on 4/11/18.
//  Copyright © 2018 Arkin Terli. All rights reserved.
//

#include <cassert>

#include "ASTGenerator.hpp"

using namespace SCCompiler;


#pragma mark - ASTVisualizer Implementations.


Type ASTGenerator::ToASTType(std::string type)
{
    if (type == "float")     return Type::tTypeFloat;
    else if (type == "int")  return Type::tTypeInt;
    else if (type == "bool") return Type::tTypeBool;
    else if (type == "void") return Type::tTypeVoid;
    else assert(false && "Unknown type in ASTGenerator::ToASTType()");

    return Type::tTypeUnknown;
}


antlrcpp::Any ASTGenerator::visitProgram(SCCompilerParser::ProgramContext *ctx)
{
    m_rootNode = new AST::NodeProgram();

    // Push new parent node into stack. It becomes new parent node for child visits.
    m_currentNodeStack.push(m_rootNode);

    // Visit parser tree childrens.
    auto visitResult = visitChildren(ctx);

    // Pop current parent node since we are leaving the method.
    m_currentNodeStack.pop();
    
    return visitResult;
}


antlrcpp::Any ASTGenerator::visitVarDecl(SCCompilerParser::VarDeclContext *ctx)
{
    Type   type = ASTGenerator::ToASTType(ctx->type()->getText());
    std::string varName = ctx->ID()->getText();

    // Create new AST Node.
    auto newNode = new AST::NodeVarDeclaration(type, varName);
    newNode->SetSourceCodeLine(ctx->getStart()->getLine());

    // Set parent node. Parent node is the top element in the currentNode Stack.
    newNode->SetParent(m_currentNodeStack.top());

    // Add yourself as child to parent node.
    m_currentNodeStack.top()->AddChild(newNode);

    // Push new parent node into stack. It becomes new parent node for child visits.
    m_currentNodeStack.push(newNode);

    // Visit parser tree childrens.
    auto visitResult = visitChildren(ctx);

    // Pop current parent node since we are leaving the method.
    m_currentNodeStack.pop();

    return visitResult;
}


antlrcpp::Any ASTGenerator::visitFuncDeclaration(SCCompilerParser::FuncDeclarationContext *ctx)
{
    Type   funcReturnType = ASTGenerator::ToASTType(ctx->type()->getText());
    std::string funcName = ctx->ID()->getText();

    // Create new AST Node.
    auto newNode = new AST::NodeFuncDeclaration(funcReturnType, funcName);
    newNode->SetSourceCodeLine(ctx->getStart()->getLine());

    // Set parent node. Parent node is the top element in the currentNode Stack.
    newNode->SetParent(m_currentNodeStack.top());

    // Add yourself as child to parent node.
    m_currentNodeStack.top()->AddChild(newNode);

    // Push new parent node into stack. It becomes new parent node for child visits.
    m_currentNodeStack.push(newNode);

    // Visit parser tree childrens.
    auto visitResult = visitChildren(ctx);

    // Pop current parent node since we are leaving the method.
    m_currentNodeStack.pop();

    return visitResult;
}


antlrcpp::Any ASTGenerator::visitFuncArgDeclaration(SCCompilerParser::FuncArgDeclarationContext *ctx)
{
    Type   argType = ASTGenerator::ToASTType(ctx->type()->getText());
    std::string argName = ctx->ID()->getText();

    // Parent node has to be function declaration node. Top of Node stack is definitely FuncDeclaratinNode.
    auto parentNode = dynamic_cast<AST::NodeFuncDeclaration*>(m_currentNodeStack.top());
    assert(parentNode != nullptr);

    parentNode->AddArgument({argType, argName});

    return visitChildren(ctx);
}


antlrcpp::Any ASTGenerator::visitBlock(SCCompilerParser::BlockContext *ctx)
{
    // Create new AST Node.
    auto newNode = new AST::NodeBlock();

    // Set parent node. Parent node is the top element in the currentNode Stack.
    newNode->SetParent(m_currentNodeStack.top());

    // Add yourself as child to parent node.
    m_currentNodeStack.top()->AddChild(newNode);

    // Push new parent node into stack. It becomes new parent node for child visits.
    m_currentNodeStack.push(newNode);

    // Visit parser tree childrens.
    auto visitResult = visitChildren(ctx);

    // Pop current parent node since we are leaving the method.
    m_currentNodeStack.pop();

    return visitResult;
}


antlrcpp::Any ASTGenerator::visitReturnStatement(SCCompilerParser::ReturnStatementContext *ctx)
{
    // Create new AST Node.
    auto newNode = new AST::NodeReturnStatement();
    newNode->SetSourceCodeLine(ctx->getStart()->getLine());

    // Set parent node. Parent node is the top element in the currentNode Stack.
    newNode->SetParent(m_currentNodeStack.top());

    // Add yourself as child to parent node.
    m_currentNodeStack.top()->AddChild(newNode);

    // Push new parent node into stack. It becomes new parent node for child visits.
    m_currentNodeStack.push(newNode);

    // Visit parser tree childrens.
    auto visitResult = visitChildren(ctx);

    // Pop current parent node since we are leaving the method.
    m_currentNodeStack.pop();

    return visitResult;
}


antlrcpp::Any ASTGenerator::visitAssignmentStatement(SCCompilerParser::AssignmentStatementContext *ctx)
{
    // Create new AST Node.
    auto newNode = new AST::NodeAssignment();
    newNode->SetSourceCodeLine(ctx->getStart()->getLine());

    // Set parent node. Parent node is the top element in the currentNode Stack.
    newNode->SetParent(m_currentNodeStack.top());

    // Add yourself as child to parent node.
    m_currentNodeStack.top()->AddChild(newNode);

    // Push new parent node into stack. It becomes new parent node for child visits.
    m_currentNodeStack.push(newNode);

    // Visit parser tree childrens.
    auto visitResult = visitChildren(ctx);

    // Pop current parent node since we are leaving the method.
    m_currentNodeStack.pop();

    return visitResult;
}


antlrcpp::Any  ASTGenerator::visitLiteralExpr(SCCompilerParser::LiteralExprContext *ctx)
{
    AST::NodeType nodeType =AST::NodeType::tNodeTypeUnknown;
    std::string  value = ctx->getText();

    // Get type of the literal.
    switch (ctx->getStart()->getType())
    {
        case SCCompilerParser::ID:
        nodeType = AST::NodeType::tNodeTypeLiteralID;
        break;

        case SCCompilerParser::FLOAT:
        nodeType =AST::NodeType::tNodeTypeLiteralFloat;
        break;

        case SCCompilerParser::INT:
        nodeType =AST::NodeType::tNodeTypeLiteralInt32;
        break;

        case SCCompilerParser::BOOL:
        nodeType =AST::NodeType::tNodeTypeLiteralBool;
        break;

        default:
        assert(false && "Unknown literal type.");
        break;
    }

    // Create new AST Node.
    auto newNode = new AST::NodeLiteral(nodeType, value);
    newNode->SetSourceCodeLine(ctx->getStart()->getLine());

    // Set parent node. Parent node is the top element in the currentNode Stack.
    newNode->SetParent(m_currentNodeStack.top());

    // Add yourself as child to parent node.
    m_currentNodeStack.top()->AddChild(newNode);

    // Visit parser tree childrens. There must be no children of this node though.
    return visitChildren(ctx);
}


antlrcpp::Any ASTGenerator::visitMulDivExpr(SCCompilerParser::MulDivExprContext *ctx)
{
    AST::NodeType nodeType = AST::NodeType::tNodeTypeUnknown;
    assert(ctx->children.size() == 3);
    std::string  aop = ctx->children[1]->getText(); // Second child is arithmetic operator in the expression.

    if (aop == "*") nodeType = AST::NodeType::tNodeTypeAOPMul;
    else if (aop == "/") nodeType = AST::NodeType::tNodeTypeAOPDiv;
    else assert(false && "Unknown arithmetic perator.");

    // Create new AST Node.
    auto newNode = new AST::NodeAOP(nodeType);
    newNode->SetSourceCodeLine(ctx->getStart()->getLine());

    // Set parent node. Parent node is the top element in the currentNode Stack.
    newNode->SetParent(m_currentNodeStack.top());

    // Add yourself as child to parent node.
    m_currentNodeStack.top()->AddChild(newNode);

    // Push new parent node into stack. It becomes new parent node for child visits.
    m_currentNodeStack.push(newNode);

    // Visit parser tree childrens.
    auto visitResult = visitChildren(ctx);

    // Pop current parent node since we are leaving the method.
    m_currentNodeStack.pop();

    return visitResult;
}


antlrcpp::Any ASTGenerator::visitPlusMinusExpr(SCCompilerParser::PlusMinusExprContext *ctx)
{
    AST::NodeType nodeType = AST::NodeType::tNodeTypeUnknown;
    assert(ctx->children.size() == 3);
    std::string  aop = ctx->children[1]->getText(); // Second child is arithmetic operator in the expression.
    
    if (aop == "+") nodeType = AST::NodeType::tNodeTypeAOPAdd;
    else if (aop == "-") nodeType = AST::NodeType::tNodeTypeAOPSub;
    else assert(false && "Unknown arithmetic perator.");

    // Create new AST Node.
    auto newNode = new AST::NodeAOP(nodeType);
    newNode->SetSourceCodeLine(ctx->getStart()->getLine());

    // Set parent node. Parent node is the top element in the currentNode Stack.
    newNode->SetParent(m_currentNodeStack.top());

    // Add yourself as child to parent node.
    m_currentNodeStack.top()->AddChild(newNode);

    // Push new parent node into stack. It becomes new parent node for child visits.
    m_currentNodeStack.push(newNode);

    // Visit parser tree childrens.
    auto visitResult = visitChildren(ctx);

    // Pop current parent node since we are leaving the method.
    m_currentNodeStack.pop();

    return visitResult;
}


antlrcpp::Any ASTGenerator::visitFuncCallExpr(SCCompilerParser::FuncCallExprContext *ctx)
{
    std::string funcName = ctx->ID()->getText();

    // Create new AST Node.
    auto newNode = new AST::NodeFuncCall(funcName);
    newNode->SetSourceCodeLine(ctx->getStart()->getLine());

    // Set parent node. Parent node is the top element in the currentNode Stack.
    newNode->SetParent(m_currentNodeStack.top());

    // Add yourself as child to parent node.
    m_currentNodeStack.top()->AddChild(newNode);

    // Push new parent node into stack. It becomes new parent node for child visits.
    m_currentNodeStack.push(newNode);

    // Visit parser tree childrens.
    auto visitResult = visitChildren(ctx);

    // Pop current parent node since we are leaving the method.
    m_currentNodeStack.pop();

    return visitResult;
}


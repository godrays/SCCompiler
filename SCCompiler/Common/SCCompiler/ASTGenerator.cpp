//
//  ASTGenerator.cpp
//
//  Created by Arkin Terli on 4/11/18.
//  Copyright © 2018 Arkin Terli. All rights reserved.
//

#include <cassert>

#include "AST.hpp"
#include "ASTGenerator.hpp"

using namespace scc;


#pragma mark - ASTVisualizer Implementations.

Type ASTGenerator::ToASTType(std::string type)
{
    if (type == "float")     return Type::kTypeFloat;
    else if (type == "int")  return Type::kTypeInt;
    else if (type == "bool") return Type::kTypeBool;
    else if (type == "void") return Type::kTypeVoid;
    else assert(false && "Unknown type in ASTGenerator::ToASTType()");

    return Type::kTypeUnknown;
}


antlrcpp::Any ASTGenerator::visitProgram(SCCompilerParser::ProgramContext *ctx)
{
    m_rootNode = new ast::NodeProgram();

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
    auto varInits = ctx->getRuleContexts<SCCompilerParser::VarInitContext>();

    // Get all VarInit under this node.
    for (size_t index=0; index < varInits.size(); ++index)
    {
        auto child = dynamic_cast<SCCompilerParser::VarInitContext *>(varInits[index]);
        assert(child && "Child must be exist!");

        std::string varName = child->ID()->getText();

        // Create new AST Node.
        auto newNode = new ast::NodeVarDeclaration(type, varName);
        newNode->SetSourceCodeLine(child->getStart()->getLine());

        // Set parent node. Parent node is the top element in the currentNode Stack.
        newNode->SetParent(m_currentNodeStack.top());

        // Add yourself as child to parent node.
        m_currentNodeStack.top()->AddChild(newNode);

        // Push new parent node into stack. It becomes new parent node for child visits.
        m_currentNodeStack.push(newNode);

        // Visit parser tree children.
        visitChildren(child);

        // Pop current parent node since we are leaving the method.
        m_currentNodeStack.pop();
    }

    // Since we visit multiple child from this node, we have no result to return from child nodes.
    // Also any return value is not used.
    return nullptr;
}


antlrcpp::Any ASTGenerator::visitFuncDeclaration(SCCompilerParser::FuncDeclarationContext *ctx)
{
    Type   funcReturnType = ASTGenerator::ToASTType(ctx->type()->getText());
    std::string funcName = ctx->ID()->getText();

    // Create new AST Node.
    auto newNode = new ast::NodeFuncDeclaration(funcReturnType, funcName);
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
    auto parentNode = dynamic_cast<ast::NodeFuncDeclaration*>(m_currentNodeStack.top());
    assert(parentNode != nullptr);

    parentNode->AddArgument({argType, argName});

    return visitChildren(ctx);
}


antlrcpp::Any ASTGenerator::visitBlock(SCCompilerParser::BlockContext *ctx)
{
    // Create new AST Node.
    auto newNode = new ast::NodeBlock();

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


antlrcpp::Any ASTGenerator::visitIfStatement(SCCompilerParser::IfStatementContext *ctx)
{
    // Create new AST Node.
    auto newNode = new ast::NodeIfStatement();
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


antlrcpp::Any ASTGenerator::visitForStatement(SCCompilerParser::ForStatementContext *ctx)
{
    // Create new AST Node.
    auto newNode = new ast::NodeForStatement();
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


antlrcpp::Any  ASTGenerator::visitForVarDecl(SCCompilerParser::ForVarDeclContext *ctx)
{
    // Create new AST Node.
    auto newNode = new ast::NodeFor(ast::NodeType::kNodeTypeForVarDecl);
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


antlrcpp::Any  ASTGenerator::visitForCondition(SCCompilerParser::ForConditionContext *ctx)
{
    // Create new AST Node.
    auto newNode = new ast::NodeFor(ast::NodeType::kNodeTypeForCondition);
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


antlrcpp::Any  ASTGenerator::visitForIncrements(SCCompilerParser::ForIncrementsContext *ctx)
{
    // Create new AST Node.
    auto newNode = new ast::NodeFor(ast::NodeType::kNodeTypeForIncrement);
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


antlrcpp::Any ASTGenerator::visitReturnStatement(SCCompilerParser::ReturnStatementContext *ctx)
{
    // Create new AST Node.
    auto newNode = new ast::NodeReturnStatement();
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


antlrcpp::Any ASTGenerator::visitAssignment(SCCompilerParser::AssignmentContext *ctx)
{
    // Create new AST Node.
    auto newNode = new ast::NodeAssignment();
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


antlrcpp::Any ASTGenerator::visitExplicitTypeConversion(SCCompilerParser::ExplicitTypeConversionContext *ctx)
{
    Type conversionType = Type::kTypeUnknown;
    auto strConvType = ctx->getStart()->getText();
    
    if (strConvType == "float") conversionType = Type::kTypeFloat;
    else if (strConvType == "int") conversionType = Type::kTypeInt;
    else if (strConvType == "bool") conversionType = Type::kTypeBool;

    // Create new AST Node.
    auto newNode = new ast::NodeExplicitTypeConversion(conversionType);
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


antlrcpp::Any ASTGenerator::visitLogicalNotExpr(SCCompilerParser::LogicalNotExprContext *ctx)
{
    // Create new AST Node.
    auto newNode = new ast::NodeLogicalNotOP();
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
    ast::NodeType nodeType =ast::NodeType::kNodeTypeUnknown;
    std::string  value = ctx->getText();

    // Get type of the literal.
    switch (ctx->getStart()->getType())
    {
        case SCCompilerParser::ID:
        nodeType = ast::NodeType::kNodeTypeLiteralID;
        break;

        case SCCompilerParser::FLOAT:
        nodeType =ast::NodeType::kNodeTypeLiteralFloat;
        break;

        case SCCompilerParser::INT:
        nodeType =ast::NodeType::kNodeTypeLiteralInt32;
        break;

        case SCCompilerParser::BOOL:
        nodeType =ast::NodeType::kNodeTypeLiteralBool;
        break;

        default:
        assert(false && "Unknown literal type.");
        break;
    }

    // Create new AST Node.
    auto newNode = new ast::NodeLiteral(nodeType, value);
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


antlrcpp::Any ASTGenerator::visitAOPExpr(SCCompilerParser::AOPExprContext *ctx)
{
    ast::NodeType nodeType = ast::NodeType::kNodeTypeUnknown;
    assert(ctx->children.size() == 3);
    std::string  aop = ctx->children[1]->getText(); // Second child is arithmetic operator in the expression.

    if (aop == "*") nodeType = ast::NodeType::kNodeTypeAOPMul;
    else if (aop == "/") nodeType = ast::NodeType::kNodeTypeAOPDiv;
    else if (aop == "+") nodeType = ast::NodeType::kNodeTypeAOPAdd;
    else if (aop == "-") nodeType = ast::NodeType::kNodeTypeAOPSub;
    else assert(false && "Unknown arithmetic operator.");

    // Create new AST Node.
    auto newNode = new ast::NodeAOP(nodeType);
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
    auto newNode = new ast::NodeFuncCall(funcName);
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


antlrcpp::Any  ASTGenerator::visitUnaryExpr(SCCompilerParser::UnaryExprContext *ctx)
{
    ast::NodeType nodeType = ast::NodeType::kNodeTypeUnknown;
    assert(ctx->children.size() == 2);
    std::string  uop = ctx->children[0]->getText(); // First child is unary operator in the expression.

    if (uop == "-") nodeType = ast::NodeType::kNodeTypeUOPMinus;
    else if (uop == "+") nodeType = ast::NodeType::kNodeTypeUOPPlus;
    else assert(false && "Unknown unary operator.");

    // Create new AST Node.
    auto newNode = new ast::NodeUnaryOP(nodeType);
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


antlrcpp::Any ASTGenerator::visitCompExpr(SCCompilerParser::CompExprContext *ctx)
{
    ast::NodeType nodeType = ast::NodeType::kNodeTypeUnknown;
    assert(ctx->children.size() == 3);
    std::string  compOP = ctx->children[1]->getText(); // Second child is comparison operator in the expression.

    if (compOP == "==") nodeType = ast::NodeType::kNodeTypeCompOPEQ;
    else if (compOP == "!=") nodeType = ast::NodeType::kNodeTypeCompOPNEQ;
    else if (compOP == "<=") nodeType = ast::NodeType::kNodeTypeCompOPLE;
    else if (compOP == ">=") nodeType = ast::NodeType::kNodeTypeCompOPGE;
    else if (compOP == "<") nodeType = ast::NodeType::kNodeTypeCompOPL;
    else if (compOP == ">") nodeType = ast::NodeType::kNodeTypeCompOPG;
    else assert(false && "Unknown arithmetic operator.");

    // Create new AST Node.
    auto newNode = new ast::NodeCompOP(nodeType);
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

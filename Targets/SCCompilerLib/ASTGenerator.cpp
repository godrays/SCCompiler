//
//  Created by Arkin Terli on 4/11/18.
//  Copyright © 2018-Present, Arkin Terli. All rights reserved.
//

// Project includes
#include "ASTGenerator.hpp"
#include "AST.hpp"
// External includes
// System includes
#include <cassert>


using namespace scc;


Type ASTGenerator::toASTType(const std::string & type)
{
    if (type == "float") return Type::kTypeFloat;
    if (type == "int")   return Type::kTypeInt;
    if (type == "bool")  return Type::kTypeBool;
    if (type == "void")  return Type::kTypeVoid;
    assert(false && "Unknown type in ASTGenerator::toASTType()");

    return Type::kTypeUnknown;
}


antlrcpp::Any ASTGenerator::visitProgram(SCCompilerParser::ProgramContext *ctx)
{
    m_rootNode = new ast::NodeProgram();

    // Push a new parent node onto the stack. It becomes the new parent node for child visits.
    m_currentNodeStack.push(m_rootNode);

    // Visit parser tree children.
    auto visitResult = visitChildren(ctx);

    // Pop the current parent node since we are leaving the method.
    m_currentNodeStack.pop();
    
    return visitResult;
}


antlrcpp::Any ASTGenerator::visitVarDecl(SCCompilerParser::VarDeclContext *ctx)
{
    Type   type = ASTGenerator::toASTType(ctx->type()->getText());
    auto varInits = ctx->getRuleContexts<SCCompilerParser::VarInitContext>();

    // Get all VarInit under this node.
    for (const auto & varInit : varInits)
    {
        auto child = dynamic_cast<SCCompilerParser::VarInitContext *>(varInit);
        assert(child && "Child must be exist!");

        std::string varName = child->ID()->getText();

        // Create new AST Node.
        auto newNode = new ast::NodeVarDeclaration(type, varName);
        newNode->setSourceCodeLine(child->getStart()->getLine());
        pushNodeToStack(newNode);

        // Visit parser tree children.
        visitChildren(child);

        // Pop the current parent node since we are leaving the method.
        m_currentNodeStack.pop();
    }

    // Since we visit multiple children from this node, we have no result to return from child nodes.
    // Also, any return value is not used.
    return nullptr;
}


antlrcpp::Any ASTGenerator::visitFuncDeclaration(SCCompilerParser::FuncDeclarationContext *ctx)
{
    Type   funcReturnType = ASTGenerator::toASTType(ctx->type()->getText());
    std::string funcName = ctx->ID()->getText();

    // Create new AST Node.
    auto newNode = new ast::NodeFuncDeclaration(funcReturnType, funcName);
    newNode->setSourceCodeLine(ctx->getStart()->getLine());
    pushNodeToStack(newNode);

    // Visit parser tree children.
    auto visitResult = visitChildren(ctx);

    // Pop the current parent node since we are leaving the method.
    m_currentNodeStack.pop();

    return visitResult;
}


antlrcpp::Any ASTGenerator::visitFuncArgDeclaration(SCCompilerParser::FuncArgDeclarationContext *ctx)
{
    Type   argType = ASTGenerator::toASTType(ctx->type()->getText());
    std::string argName = ctx->ID()->getText();

    // The parent node has to be a function declaration node. The top of the Node stack is definitely a FuncDeclarationNode.
    auto parentNode = dynamic_cast<ast::NodeFuncDeclaration*>(m_currentNodeStack.top());
    assert(parentNode != nullptr);

    parentNode->AddArgument({argType, argName});

    return visitChildren(ctx);
}


antlrcpp::Any ASTGenerator::visitBlock(SCCompilerParser::BlockContext *ctx)
{
    // Create new AST Node.
    auto newNode = new ast::NodeBlock();
    pushNodeToStack(newNode);

    // Visit parser tree children.
    auto visitResult = visitChildren(ctx);

    // Pop the current parent node since we are leaving the method.
    m_currentNodeStack.pop();

    return visitResult;
}


antlrcpp::Any ASTGenerator::visitIfStatement(SCCompilerParser::IfStatementContext *ctx)
{
    // Create new AST Node.
    auto newNode = new ast::NodeIfStatement();
    newNode->setSourceCodeLine(ctx->getStart()->getLine());
    pushNodeToStack(newNode);

    // Visit parser tree children.
    auto visitResult = visitChildren(ctx);

    // Pop the current parent node since we are leaving the method.
    m_currentNodeStack.pop();

    return visitResult;
}


antlrcpp::Any ASTGenerator::visitForStatement(SCCompilerParser::ForStatementContext *ctx)
{
    // Create new AST Node.
    auto newNode = new ast::NodeForStatement();
    newNode->setSourceCodeLine(ctx->getStart()->getLine());
    pushNodeToStack(newNode);

    // Visit parser tree children.
    auto visitResult = visitChildren(ctx);

    // Pop the current parent node since we are leaving the method.
    m_currentNodeStack.pop();

    return visitResult;
}


antlrcpp::Any  ASTGenerator::visitForVarDecl(SCCompilerParser::ForVarDeclContext *ctx)
{
    // Create new AST Node.
    auto newNode = new ast::NodeFor(ast::NodeType::kForVarDecl);
    newNode->setSourceCodeLine(ctx->getStart()->getLine());
    pushNodeToStack(newNode);

    // Visit parser tree children.
    auto visitResult = visitChildren(ctx);

    // Pop the current parent node since we are leaving the method.
    m_currentNodeStack.pop();

    return visitResult;
}


antlrcpp::Any  ASTGenerator::visitForCondition(SCCompilerParser::ForConditionContext *ctx)
{
    // Create new AST Node.
    auto newNode = new ast::NodeFor(ast::NodeType::kForCondition);
    newNode->setSourceCodeLine(ctx->getStart()->getLine());
    pushNodeToStack(newNode);

    // Visit parser tree children.
    auto visitResult = visitChildren(ctx);

    // Pop the current parent node since we are leaving the method.
    m_currentNodeStack.pop();

    return visitResult;
}


antlrcpp::Any  ASTGenerator::visitForIncrements(SCCompilerParser::ForIncrementsContext *ctx)
{
    // Create new AST Node.
    auto newNode = new ast::NodeFor(ast::NodeType::kForIncrement);
    newNode->setSourceCodeLine(ctx->getStart()->getLine());
    pushNodeToStack(newNode);

    // Visit parser tree children.
    auto visitResult = visitChildren(ctx);

    // Pop the current parent node since we are leaving the method.
    m_currentNodeStack.pop();

    return visitResult;
}


antlrcpp::Any ASTGenerator::visitWhileStatement(SCCompilerParser::WhileStatementContext *ctx)
{
    // Create new AST Node.
    auto newNode = new ast::NodeWhileStatement();
    newNode->setSourceCodeLine(ctx->getStart()->getLine());
    pushNodeToStack(newNode);

    // Visit parser tree children.
    auto visitResult = visitChildren(ctx);

    // Pop the current parent node since we are leaving the method.
    m_currentNodeStack.pop();

    return visitResult;
}


antlrcpp::Any ASTGenerator::visitDoWhileStatement(SCCompilerParser::DoWhileStatementContext *ctx)
{
    // Create new AST Node.
    auto newNode = new ast::NodeDoWhileStatement();
    newNode->setSourceCodeLine(ctx->getStart()->getLine());
    pushNodeToStack(newNode);

    // Visit parser tree children.
    auto visitResult = visitChildren(ctx);

    // Pop the current parent node since we are leaving the method.
    m_currentNodeStack.pop();

    return visitResult;
}


antlrcpp::Any ASTGenerator::visitReturnStatement(SCCompilerParser::ReturnStatementContext *ctx)
{
    // Create new AST Node.
    auto newNode = new ast::NodeReturnStatement();
    newNode->setSourceCodeLine(ctx->getStart()->getLine());
    pushNodeToStack(newNode);

    // Visit parser tree children.
    auto visitResult = visitChildren(ctx);

    // Pop the current parent node since we are leaving the method.
    m_currentNodeStack.pop();

    return visitResult;
}


antlrcpp::Any ASTGenerator::visitContinue(SCCompilerParser::ContinueContext *ctx)
{
    // Create new AST Node.
    auto newNode = new ast::NodeContinue();
    newNode->setSourceCodeLine(ctx->getStart()->getLine());
    pushNodeToStack(newNode);

    // Visit parser tree children.
    auto visitResult = visitChildren(ctx);

    // Pop the current parent node since we are leaving the method.
    m_currentNodeStack.pop();

    return visitResult;
}


antlrcpp::Any ASTGenerator::visitBreak(SCCompilerParser::BreakContext *ctx)
{
    // Create new AST Node.
    auto newNode = new ast::NodeBreak();
    newNode->setSourceCodeLine(ctx->getStart()->getLine());
    pushNodeToStack(newNode);

    // Visit parser tree children.
    auto visitResult = visitChildren(ctx);

    // Pop the current parent node since we are leaving the method.
    m_currentNodeStack.pop();

    return visitResult;
}


antlrcpp::Any ASTGenerator::visitAssignment(SCCompilerParser::AssignmentContext *ctx)
{
    // Create new AST Node.
    auto newNode = new ast::NodeAssignment();
    newNode->setSourceCodeLine(ctx->getStart()->getLine());
    pushNodeToStack(newNode);

    // Visit parser tree children.
    auto visitResult = visitChildren(ctx);

    // Pop the current parent node since we are leaving the method.
    m_currentNodeStack.pop();

    return visitResult;
}


antlrcpp::Any ASTGenerator::visitExplicitTypeConversion(SCCompilerParser::ExplicitTypeConversionContext *ctx)
{
    Type conversionType = Type::kTypeUnknown;
    auto strConvType = ctx->getStart()->getText();
    
    if (strConvType == "float")     conversionType = Type::kTypeFloat;
    else if (strConvType == "int")  conversionType = Type::kTypeInt;
    else if (strConvType == "bool") conversionType = Type::kTypeBool;

    // Create new AST Node.
    auto newNode = new ast::NodeExplicitTypeConversion(conversionType);
    newNode->setSourceCodeLine(ctx->getStart()->getLine());
    pushNodeToStack(newNode);

    // Visit parser tree children.
    auto visitResult = visitChildren(ctx);

    // Pop the current parent node since we are leaving the method.
    m_currentNodeStack.pop();

    return visitResult;
}


antlrcpp::Any ASTGenerator::visitLogicalNotOPExpr(SCCompilerParser::LogicalNotOPExprContext *ctx)
{
    // Create new AST Node.
    auto newNode = new ast::NodeLogicalOP(ast::NodeType::kLogicalNotOP);
    newNode->setSourceCodeLine(ctx->getStart()->getLine());
    pushNodeToStack(newNode);

    // Visit parser tree children.
    auto visitResult = visitChildren(ctx);

    // Pop the current parent node since we are leaving the method.
    m_currentNodeStack.pop();

    return visitResult;
}



antlrcpp::Any ASTGenerator::visitLogicalOPExpr(SCCompilerParser::LogicalOPExprContext *ctx)
{
    ast::NodeType  nodeType = ast::NodeType::kUnknown;
    std::string  logicalOP = ctx->children[1]->getText();

    if (logicalOP == "&&") nodeType = ast::NodeType::kLogicalAndOP;
    else if (logicalOP == "||") nodeType = ast::NodeType::kLogicalOrOP;
    else assert(false && "Unknown logical operator.");

    // Create new AST Node.
    auto newNode = new ast::NodeLogicalOP(nodeType);
    newNode->setSourceCodeLine(ctx->getStart()->getLine());
    pushNodeToStack(newNode);

    // Visit parser tree children.
    auto visitResult = visitChildren(ctx);

    // Pop the current parent node since we are leaving the method.
    m_currentNodeStack.pop();

    return visitResult;
}


antlrcpp::Any  ASTGenerator::visitLiteralExpr(SCCompilerParser::LiteralExprContext *ctx)
{
    ast::NodeType nodeType =ast::NodeType::kUnknown;
    std::string  value = ctx->getText();

    // Get type of the literal.
    switch (ctx->getStart()->getType())
    {
        case SCCompilerParser::ID:
            nodeType = ast::NodeType::kLiteralID;
            break;

        case SCCompilerParser::FLOAT:
            nodeType =ast::NodeType::kLiteralFloat;
            break;

        case SCCompilerParser::INT:
            nodeType =ast::NodeType::kLiteralInt32;
            break;

        case SCCompilerParser::BOOL:
            nodeType =ast::NodeType::kLiteralBool;
            break;

        default:
            assert(false && "Unknown literal type.");
            break;
    }

    // Create new AST Node.
    auto newNode = new ast::NodeLiteral(nodeType, value);
    newNode->setSourceCodeLine(ctx->getStart()->getLine());
    pushNodeToStack(newNode);

    // Visit parser tree children.
    auto visitResult = visitChildren(ctx);

    // Pop the current parent node since we are leaving the method.
    m_currentNodeStack.pop();

    return visitResult;
}


antlrcpp::Any ASTGenerator::visitPrefixAOPExpr(SCCompilerParser::PrefixAOPExprContext *ctx)
{
    ast::NodeType nodeType = ast::NodeType::kUnknown;
    assert(ctx->children.size() == 2);
    std::string  prefixAOP = ctx->getStart()->getText();

    if (prefixAOP == "++")      nodeType = ast::NodeType::kPrefixIncAOP;
    else if (prefixAOP == "--") nodeType = ast::NodeType::kPrefixDecAOP;
    else assert(false && "Unknown prefix arithmetic operator.");

    // Create new AST Node: '++' or '--'
    auto newNode = new ast::NodePrefixAOP(nodeType);
    newNode->setSourceCodeLine(ctx->getStart()->getLine());
    pushNodeToStack(newNode);

    // Create new AST Node: ID
    auto IDToken = ctx->getStop();
    std::string  ID = IDToken->getText();
    auto newNodeID = new ast::NodeLiteral(ast::NodeType::kLiteralID, ID);
    newNodeID->setSourceCodeLine(IDToken->getLine());
    pushNodeToStack(newNodeID);

    // Visit parser tree child.
    // NOTE: We don't expect a child node, but we still call for the conventions.
    // ANTLR4 used to visit visitLiteralExpr() when we called visitChildren(), but it looks like newer versions
    // do not visit visitLiteralExpr() as a child. Handling Prefix and ID token in this call to fix the issue.
    auto visitResult = visitChildren(ctx);

    // Pop the current parent node since we are leaving the method.
    m_currentNodeStack.pop();
    // Pop the current parent node since we are leaving the method.
    m_currentNodeStack.pop();

    return visitResult;
}


antlrcpp::Any ASTGenerator::visitAOPExpr(SCCompilerParser::AOPExprContext *ctx)
{
    ast::NodeType nodeType = ast::NodeType::kUnknown;
    assert(ctx->children.size() == 3);
    std::string  aop = ctx->children[1]->getText(); // Second child is arithmetic operator in the expression.

    if (aop == "*")      nodeType = ast::NodeType::kAOPMul;
    else if (aop == "/") nodeType = ast::NodeType::kAOPDiv;
    else if (aop == "+") nodeType = ast::NodeType::kAOPAdd;
    else if (aop == "-") nodeType = ast::NodeType::kAOPSub;
    else assert(false && "Unknown arithmetic operator.");

    // Create new AST Node.
    auto newNode = new ast::NodeAOP(nodeType);
    newNode->setSourceCodeLine(ctx->getStart()->getLine());
    pushNodeToStack(newNode);

    // Visit parser tree children.
    auto visitResult = visitChildren(ctx);

    // Pop the current parent node since we are leaving the method.
    m_currentNodeStack.pop();

    return visitResult;
}


antlrcpp::Any ASTGenerator::visitFuncCallExpr(SCCompilerParser::FuncCallExprContext *ctx)
{
    std::string funcName = ctx->ID()->getText();

    // Create new AST Node.
    auto newNode = new ast::NodeFuncCall(funcName);
    newNode->setSourceCodeLine(ctx->getStart()->getLine());
    pushNodeToStack(newNode);

    // Visit parser tree children.
    auto visitResult = visitChildren(ctx);

    // Pop the current parent node since we are leaving the method.
    m_currentNodeStack.pop();

    return visitResult;
}


antlrcpp::Any  ASTGenerator::visitUnaryExpr(SCCompilerParser::UnaryExprContext *ctx)
{
    ast::NodeType nodeType = ast::NodeType::kUnknown;
    assert(ctx->children.size() == 2);
    std::string  uop = ctx->children[0]->getText(); // First child is unary operator in the expression.

    if (uop == "-") nodeType = ast::NodeType::kUOPMinus;
    else if (uop == "+") nodeType = ast::NodeType::kUOPPlus;
    else assert(false && "Unknown unary operator.");

    // Create new AST Node.
    auto newNode = new ast::NodeUnaryOP(nodeType);
    newNode->setSourceCodeLine(ctx->getStart()->getLine());
    pushNodeToStack(newNode);

    // Visit parser tree children.
    auto visitResult = visitChildren(ctx);

    // Pop the current parent node since we are leaving the method.
    m_currentNodeStack.pop();

    return visitResult;
}


antlrcpp::Any ASTGenerator::visitCompExpr(SCCompilerParser::CompExprContext *ctx)
{
    ast::NodeType nodeType = ast::NodeType::kUnknown;
    assert(ctx->children.size() == 3);
    std::string  compOP = ctx->children[1]->getText(); // Second child is comparison operator in the expression.

    if (compOP == "==")      nodeType = ast::NodeType::kCompOPEQ;
    else if (compOP == "!=") nodeType = ast::NodeType::kCompOPNEQ;
    else if (compOP == "<=") nodeType = ast::NodeType::kCompOPLE;
    else if (compOP == ">=") nodeType = ast::NodeType::kCompOPGE;
    else if (compOP == "<")  nodeType = ast::NodeType::kCompOPL;
    else if (compOP == ">")  nodeType = ast::NodeType::kCompOPG;
    else assert(false && "Unknown arithmetic operator.");

    // Create new AST Node.
    auto newNode = new ast::NodeCompOP(nodeType);
    newNode->setSourceCodeLine(ctx->getStart()->getLine());
    pushNodeToStack(newNode);

    // Visit parser tree children.
    auto visitResult = visitChildren(ctx);

    // Pop the current parent node since we are leaving the method.
    m_currentNodeStack.pop();

    return visitResult;
}


void ASTGenerator::pushNodeToStack(ast::Node* node)
{
    // Set the parent node. The parent node is the top element in the currentNode stack.
    node->setParent(m_currentNodeStack.top());

    // Add yourself as a child to the parent node.
    m_currentNodeStack.top()->addChild(node);

    // Push a new parent node onto the stack. It becomes the new parent node for child visits.
    m_currentNodeStack.push(node);
}

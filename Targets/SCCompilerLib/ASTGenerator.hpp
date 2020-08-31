//
//  ASTGenerator.hpp
//
//  Created by Arkin Terli on 4/11/18.
//  Copyright © 2018-Present, Arkin Terli. All rights reserved.
//

#pragma once

#include <stack>

#include "Parser/SCCompilerBaseVisitor.h"
#include "Types.hpp"


namespace scc
{

// Fordward declaration
namespace ast
{
    class Node;
}

class  ASTGenerator final : public SCCompilerBaseVisitor
{
public:
    // Contructor.
    ASTGenerator() = default;

    // Destructor.
    ~ASTGenerator() final = default;

    // Return AST Node.
    ast::Node *   GetAST()    { return m_rootNode; }

    static Type  ToASTType(const std::string&);

    antlrcpp::Any  visitProgram(SCCompilerParser::ProgramContext *ctx) final;

    antlrcpp::Any  visitVarDecl(SCCompilerParser::VarDeclContext *ctx) final;

    antlrcpp::Any  visitFuncDeclaration(SCCompilerParser::FuncDeclarationContext *ctx) final;

    antlrcpp::Any  visitFuncArgDeclaration(SCCompilerParser::FuncArgDeclarationContext *ctx) final;

    antlrcpp::Any  visitBlock(SCCompilerParser::BlockContext *ctx) final;

    antlrcpp::Any  visitIfStatement(SCCompilerParser::IfStatementContext *ctx) final;

    antlrcpp::Any  visitForStatement(SCCompilerParser::ForStatementContext *ctx) final;

    antlrcpp::Any  visitForVarDecl(SCCompilerParser::ForVarDeclContext *ctx) final;

    antlrcpp::Any  visitForCondition(SCCompilerParser::ForConditionContext *ctx) final;

    antlrcpp::Any  visitForIncrements(SCCompilerParser::ForIncrementsContext *ctx) final;

    antlrcpp::Any  visitWhileStatement(SCCompilerParser::WhileStatementContext *ctx) final;

    antlrcpp::Any  visitDoWhileStatement(SCCompilerParser::DoWhileStatementContext *ctx) final;

    antlrcpp::Any  visitReturnStatement(SCCompilerParser::ReturnStatementContext *ctx) final;

    antlrcpp::Any  visitContinue(SCCompilerParser::ContinueContext *ctx) final;

    antlrcpp::Any  visitBreak(SCCompilerParser::BreakContext *ctx) final;

    antlrcpp::Any  visitAssignment(SCCompilerParser::AssignmentContext *ctx) final;

    antlrcpp::Any  visitExplicitTypeConversion(SCCompilerParser::ExplicitTypeConversionContext *ctx) final;

    antlrcpp::Any  visitLiteralExpr(SCCompilerParser::LiteralExprContext *ctx) final;

    antlrcpp::Any  visitPrefixAOPExpr(SCCompilerParser::PrefixAOPExprContext *ctx) final;

    antlrcpp::Any  visitAOPExpr(SCCompilerParser::AOPExprContext *ctx) final;

    antlrcpp::Any  visitFuncCallExpr(SCCompilerParser::FuncCallExprContext *ctx) final;

    antlrcpp::Any  visitUnaryExpr(SCCompilerParser::UnaryExprContext *ctx) final;

    antlrcpp::Any  visitCompExpr(SCCompilerParser::CompExprContext *ctx) final;

    antlrcpp::Any  visitLogicalNotOPExpr(SCCompilerParser::LogicalNotOPExprContext *ctx) final;

    antlrcpp::Any  visitLogicalOPExpr(SCCompilerParser::LogicalOPExprContext *ctx) final;

protected:
    ast::Node *   m_rootNode{nullptr};
    std::stack<ast::Node *>  m_currentNodeStack;
};

}

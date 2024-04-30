
// Generated from ./Targets/SCCompilerLib/Parser/SCCompiler.g4 by ANTLR 4.13.1

#pragma once


#include "antlr4-runtime.h"
#include "SCCompilerParser.h"



/**
 * This class defines an abstract visitor for a parse tree
 * produced by SCCompilerParser.
 */
class  SCCompilerVisitor : public antlr4::tree::AbstractParseTreeVisitor {
public:

  /**
   * Visit parse trees produced by SCCompilerParser.
   */
    virtual std::any visitProgram(SCCompilerParser::ProgramContext *context) = 0;

    virtual std::any visitVarDecl(SCCompilerParser::VarDeclContext *context) = 0;

    virtual std::any visitVarInit(SCCompilerParser::VarInitContext *context) = 0;

    virtual std::any visitType(SCCompilerParser::TypeContext *context) = 0;

    virtual std::any visitFuncDeclaration(SCCompilerParser::FuncDeclarationContext *context) = 0;

    virtual std::any visitFormalParameters(SCCompilerParser::FormalParametersContext *context) = 0;

    virtual std::any visitFuncArgDeclaration(SCCompilerParser::FuncArgDeclarationContext *context) = 0;

    virtual std::any visitBlock(SCCompilerParser::BlockContext *context) = 0;

    virtual std::any visitBlockStatement(SCCompilerParser::BlockStatementContext *context) = 0;

    virtual std::any visitVarDeclStatement(SCCompilerParser::VarDeclStatementContext *context) = 0;

    virtual std::any visitIfStatement(SCCompilerParser::IfStatementContext *context) = 0;

    virtual std::any visitIgnore(SCCompilerParser::IgnoreContext *context) = 0;

    virtual std::any visitWhileStatement(SCCompilerParser::WhileStatementContext *context) = 0;

    virtual std::any visitDoWhileStatement(SCCompilerParser::DoWhileStatementContext *context) = 0;

    virtual std::any visitReturnStatement(SCCompilerParser::ReturnStatementContext *context) = 0;

    virtual std::any visitContinue(SCCompilerParser::ContinueContext *context) = 0;

    virtual std::any visitBreak(SCCompilerParser::BreakContext *context) = 0;

    virtual std::any visitFuncCallStatement(SCCompilerParser::FuncCallStatementContext *context) = 0;

    virtual std::any visitExplicitTypeConversion(SCCompilerParser::ExplicitTypeConversionContext *context) = 0;

    virtual std::any visitPrefixAOPExpr(SCCompilerParser::PrefixAOPExprContext *context) = 0;

    virtual std::any visitParenthesisExpr(SCCompilerParser::ParenthesisExprContext *context) = 0;

    virtual std::any visitLogicalNotOPExpr(SCCompilerParser::LogicalNotOPExprContext *context) = 0;

    virtual std::any visitLiteralExpr(SCCompilerParser::LiteralExprContext *context) = 0;

    virtual std::any visitCompExpr(SCCompilerParser::CompExprContext *context) = 0;

    virtual std::any visitAOPExpr(SCCompilerParser::AOPExprContext *context) = 0;

    virtual std::any visitUnaryExpr(SCCompilerParser::UnaryExprContext *context) = 0;

    virtual std::any visitLogicalOPExpr(SCCompilerParser::LogicalOPExprContext *context) = 0;

    virtual std::any visitFuncCallExpr(SCCompilerParser::FuncCallExprContext *context) = 0;

    virtual std::any visitExprList(SCCompilerParser::ExprListContext *context) = 0;

    virtual std::any visitAssignment(SCCompilerParser::AssignmentContext *context) = 0;

    virtual std::any visitForStatement(SCCompilerParser::ForStatementContext *context) = 0;

    virtual std::any visitForVarDecl(SCCompilerParser::ForVarDeclContext *context) = 0;

    virtual std::any visitForCondition(SCCompilerParser::ForConditionContext *context) = 0;

    virtual std::any visitForIncrements(SCCompilerParser::ForIncrementsContext *context) = 0;

    virtual std::any visitForInc(SCCompilerParser::ForIncContext *context) = 0;


};


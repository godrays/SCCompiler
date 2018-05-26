
// Generated from ./Common/SCCompiler/Parser/SCCompiler.g4 by ANTLR 4.7.1

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
    virtual antlrcpp::Any visitProgram(SCCompilerParser::ProgramContext *context) = 0;

    virtual antlrcpp::Any visitVarDecl(SCCompilerParser::VarDeclContext *context) = 0;

    virtual antlrcpp::Any visitVarInit(SCCompilerParser::VarInitContext *context) = 0;

    virtual antlrcpp::Any visitType(SCCompilerParser::TypeContext *context) = 0;

    virtual antlrcpp::Any visitFuncDeclaration(SCCompilerParser::FuncDeclarationContext *context) = 0;

    virtual antlrcpp::Any visitFormalParameters(SCCompilerParser::FormalParametersContext *context) = 0;

    virtual antlrcpp::Any visitFuncArgDeclaration(SCCompilerParser::FuncArgDeclarationContext *context) = 0;

    virtual antlrcpp::Any visitBlock(SCCompilerParser::BlockContext *context) = 0;

    virtual antlrcpp::Any visitBlockStatement(SCCompilerParser::BlockStatementContext *context) = 0;

    virtual antlrcpp::Any visitVarDeclStatement(SCCompilerParser::VarDeclStatementContext *context) = 0;

    virtual antlrcpp::Any visitIfStatement(SCCompilerParser::IfStatementContext *context) = 0;

    virtual antlrcpp::Any visitIgnore(SCCompilerParser::IgnoreContext *context) = 0;

    virtual antlrcpp::Any visitReturnStatement(SCCompilerParser::ReturnStatementContext *context) = 0;

    virtual antlrcpp::Any visitFuncCallStatement(SCCompilerParser::FuncCallStatementContext *context) = 0;

    virtual antlrcpp::Any visitExplicitTypeConversion(SCCompilerParser::ExplicitTypeConversionContext *context) = 0;

    virtual antlrcpp::Any visitParenthesisExpr(SCCompilerParser::ParenthesisExprContext *context) = 0;

    virtual antlrcpp::Any visitLogicalNotExpr(SCCompilerParser::LogicalNotExprContext *context) = 0;

    virtual antlrcpp::Any visitLiteralExpr(SCCompilerParser::LiteralExprContext *context) = 0;

    virtual antlrcpp::Any visitCompExpr(SCCompilerParser::CompExprContext *context) = 0;

    virtual antlrcpp::Any visitAOPExpr(SCCompilerParser::AOPExprContext *context) = 0;

    virtual antlrcpp::Any visitUnaryExpr(SCCompilerParser::UnaryExprContext *context) = 0;

    virtual antlrcpp::Any visitFuncCallExpr(SCCompilerParser::FuncCallExprContext *context) = 0;

    virtual antlrcpp::Any visitExprList(SCCompilerParser::ExprListContext *context) = 0;

    virtual antlrcpp::Any visitAssignment(SCCompilerParser::AssignmentContext *context) = 0;

    virtual antlrcpp::Any visitForStatement(SCCompilerParser::ForStatementContext *context) = 0;

    virtual antlrcpp::Any visitForVarDecl(SCCompilerParser::ForVarDeclContext *context) = 0;

    virtual antlrcpp::Any visitForCondition(SCCompilerParser::ForConditionContext *context) = 0;

    virtual antlrcpp::Any visitForIncrements(SCCompilerParser::ForIncrementsContext *context) = 0;

    virtual antlrcpp::Any visitForInc(SCCompilerParser::ForIncContext *context) = 0;


};


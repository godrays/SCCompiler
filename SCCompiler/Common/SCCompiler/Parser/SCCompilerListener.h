
// Generated from ./Common/SCCompiler/Parser/SCCompiler.g4 by ANTLR 4.7.1

#pragma once


#include "antlr4-runtime.h"
#include "SCCompilerParser.h"


/**
 * This interface defines an abstract listener for a parse tree produced by SCCompilerParser.
 */
class  SCCompilerListener : public antlr4::tree::ParseTreeListener {
public:

  virtual void enterProgram(SCCompilerParser::ProgramContext *ctx) = 0;
  virtual void exitProgram(SCCompilerParser::ProgramContext *ctx) = 0;

  virtual void enterVarDecl(SCCompilerParser::VarDeclContext *ctx) = 0;
  virtual void exitVarDecl(SCCompilerParser::VarDeclContext *ctx) = 0;

  virtual void enterType(SCCompilerParser::TypeContext *ctx) = 0;
  virtual void exitType(SCCompilerParser::TypeContext *ctx) = 0;

  virtual void enterFuncDeclaration(SCCompilerParser::FuncDeclarationContext *ctx) = 0;
  virtual void exitFuncDeclaration(SCCompilerParser::FuncDeclarationContext *ctx) = 0;

  virtual void enterFormalParameters(SCCompilerParser::FormalParametersContext *ctx) = 0;
  virtual void exitFormalParameters(SCCompilerParser::FormalParametersContext *ctx) = 0;

  virtual void enterFuncArgDeclaration(SCCompilerParser::FuncArgDeclarationContext *ctx) = 0;
  virtual void exitFuncArgDeclaration(SCCompilerParser::FuncArgDeclarationContext *ctx) = 0;

  virtual void enterBlock(SCCompilerParser::BlockContext *ctx) = 0;
  virtual void exitBlock(SCCompilerParser::BlockContext *ctx) = 0;

  virtual void enterBlockStatement(SCCompilerParser::BlockStatementContext *ctx) = 0;
  virtual void exitBlockStatement(SCCompilerParser::BlockStatementContext *ctx) = 0;

  virtual void enterVarDeclStatement(SCCompilerParser::VarDeclStatementContext *ctx) = 0;
  virtual void exitVarDeclStatement(SCCompilerParser::VarDeclStatementContext *ctx) = 0;

  virtual void enterReturnStatement(SCCompilerParser::ReturnStatementContext *ctx) = 0;
  virtual void exitReturnStatement(SCCompilerParser::ReturnStatementContext *ctx) = 0;

  virtual void enterAssignmentStatement(SCCompilerParser::AssignmentStatementContext *ctx) = 0;
  virtual void exitAssignmentStatement(SCCompilerParser::AssignmentStatementContext *ctx) = 0;

  virtual void enterFuncCallStatement(SCCompilerParser::FuncCallStatementContext *ctx) = 0;
  virtual void exitFuncCallStatement(SCCompilerParser::FuncCallStatementContext *ctx) = 0;

  virtual void enterExprList(SCCompilerParser::ExprListContext *ctx) = 0;
  virtual void exitExprList(SCCompilerParser::ExprListContext *ctx) = 0;

  virtual void enterExplicitTypeConversion(SCCompilerParser::ExplicitTypeConversionContext *ctx) = 0;
  virtual void exitExplicitTypeConversion(SCCompilerParser::ExplicitTypeConversionContext *ctx) = 0;

  virtual void enterParenthesisExpr(SCCompilerParser::ParenthesisExprContext *ctx) = 0;
  virtual void exitParenthesisExpr(SCCompilerParser::ParenthesisExprContext *ctx) = 0;

  virtual void enterLiteralExpr(SCCompilerParser::LiteralExprContext *ctx) = 0;
  virtual void exitLiteralExpr(SCCompilerParser::LiteralExprContext *ctx) = 0;

  virtual void enterAOPExpr(SCCompilerParser::AOPExprContext *ctx) = 0;
  virtual void exitAOPExpr(SCCompilerParser::AOPExprContext *ctx) = 0;

  virtual void enterUnaryExpr(SCCompilerParser::UnaryExprContext *ctx) = 0;
  virtual void exitUnaryExpr(SCCompilerParser::UnaryExprContext *ctx) = 0;

  virtual void enterFuncCallExpr(SCCompilerParser::FuncCallExprContext *ctx) = 0;
  virtual void exitFuncCallExpr(SCCompilerParser::FuncCallExprContext *ctx) = 0;


};


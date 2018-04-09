
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

  virtual void enterFunctionDecl(SCCompilerParser::FunctionDeclContext *ctx) = 0;
  virtual void exitFunctionDecl(SCCompilerParser::FunctionDeclContext *ctx) = 0;

  virtual void enterFormalParameters(SCCompilerParser::FormalParametersContext *ctx) = 0;
  virtual void exitFormalParameters(SCCompilerParser::FormalParametersContext *ctx) = 0;

  virtual void enterFormalParameter(SCCompilerParser::FormalParameterContext *ctx) = 0;
  virtual void exitFormalParameter(SCCompilerParser::FormalParameterContext *ctx) = 0;

  virtual void enterBlock(SCCompilerParser::BlockContext *ctx) = 0;
  virtual void exitBlock(SCCompilerParser::BlockContext *ctx) = 0;

  virtual void enterBlockStatement(SCCompilerParser::BlockStatementContext *ctx) = 0;
  virtual void exitBlockStatement(SCCompilerParser::BlockStatementContext *ctx) = 0;

  virtual void enterVarDeclStatement(SCCompilerParser::VarDeclStatementContext *ctx) = 0;
  virtual void exitVarDeclStatement(SCCompilerParser::VarDeclStatementContext *ctx) = 0;

  virtual void enterIfStatement(SCCompilerParser::IfStatementContext *ctx) = 0;
  virtual void exitIfStatement(SCCompilerParser::IfStatementContext *ctx) = 0;

  virtual void enterReturnStatement(SCCompilerParser::ReturnStatementContext *ctx) = 0;
  virtual void exitReturnStatement(SCCompilerParser::ReturnStatementContext *ctx) = 0;

  virtual void enterAssignmentStatement(SCCompilerParser::AssignmentStatementContext *ctx) = 0;
  virtual void exitAssignmentStatement(SCCompilerParser::AssignmentStatementContext *ctx) = 0;

  virtual void enterFuncCallStatement(SCCompilerParser::FuncCallStatementContext *ctx) = 0;
  virtual void exitFuncCallStatement(SCCompilerParser::FuncCallStatementContext *ctx) = 0;

  virtual void enterExprList(SCCompilerParser::ExprListContext *ctx) = 0;
  virtual void exitExprList(SCCompilerParser::ExprListContext *ctx) = 0;

  virtual void enterArrayIndexExpr(SCCompilerParser::ArrayIndexExprContext *ctx) = 0;
  virtual void exitArrayIndexExpr(SCCompilerParser::ArrayIndexExprContext *ctx) = 0;

  virtual void enterBoolNotExpr(SCCompilerParser::BoolNotExprContext *ctx) = 0;
  virtual void exitBoolNotExpr(SCCompilerParser::BoolNotExprContext *ctx) = 0;

  virtual void enterMulDivExpr(SCCompilerParser::MulDivExprContext *ctx) = 0;
  virtual void exitMulDivExpr(SCCompilerParser::MulDivExprContext *ctx) = 0;

  virtual void enterNumberExpr(SCCompilerParser::NumberExprContext *ctx) = 0;
  virtual void exitNumberExpr(SCCompilerParser::NumberExprContext *ctx) = 0;

  virtual void enterVarRefExpr(SCCompilerParser::VarRefExprContext *ctx) = 0;
  virtual void exitVarRefExpr(SCCompilerParser::VarRefExprContext *ctx) = 0;

  virtual void enterUnaryNegationExpr(SCCompilerParser::UnaryNegationExprContext *ctx) = 0;
  virtual void exitUnaryNegationExpr(SCCompilerParser::UnaryNegationExprContext *ctx) = 0;

  virtual void enterPlusMinusExpr(SCCompilerParser::PlusMinusExprContext *ctx) = 0;
  virtual void exitPlusMinusExpr(SCCompilerParser::PlusMinusExprContext *ctx) = 0;

  virtual void enterCompExpr(SCCompilerParser::CompExprContext *ctx) = 0;
  virtual void exitCompExpr(SCCompilerParser::CompExprContext *ctx) = 0;

  virtual void enterParanthesisExpr(SCCompilerParser::ParanthesisExprContext *ctx) = 0;
  virtual void exitParanthesisExpr(SCCompilerParser::ParanthesisExprContext *ctx) = 0;

  virtual void enterFuncCallExpr(SCCompilerParser::FuncCallExprContext *ctx) = 0;
  virtual void exitFuncCallExpr(SCCompilerParser::FuncCallExprContext *ctx) = 0;

  virtual void enterNumber(SCCompilerParser::NumberContext *ctx) = 0;
  virtual void exitNumber(SCCompilerParser::NumberContext *ctx) = 0;


};



// Generated from ./Common/SCCompilerLib/Parser/SCCompilerLib.g4 by ANTLR 4.7.1

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

  virtual void enterVarInit(SCCompilerParser::VarInitContext *ctx) = 0;
  virtual void exitVarInit(SCCompilerParser::VarInitContext *ctx) = 0;

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

  virtual void enterIfStatement(SCCompilerParser::IfStatementContext *ctx) = 0;
  virtual void exitIfStatement(SCCompilerParser::IfStatementContext *ctx) = 0;

  virtual void enterIgnore(SCCompilerParser::IgnoreContext *ctx) = 0;
  virtual void exitIgnore(SCCompilerParser::IgnoreContext *ctx) = 0;

  virtual void enterWhileStatement(SCCompilerParser::WhileStatementContext *ctx) = 0;
  virtual void exitWhileStatement(SCCompilerParser::WhileStatementContext *ctx) = 0;

  virtual void enterDoWhileStatement(SCCompilerParser::DoWhileStatementContext *ctx) = 0;
  virtual void exitDoWhileStatement(SCCompilerParser::DoWhileStatementContext *ctx) = 0;

  virtual void enterReturnStatement(SCCompilerParser::ReturnStatementContext *ctx) = 0;
  virtual void exitReturnStatement(SCCompilerParser::ReturnStatementContext *ctx) = 0;

  virtual void enterContinue(SCCompilerParser::ContinueContext *ctx) = 0;
  virtual void exitContinue(SCCompilerParser::ContinueContext *ctx) = 0;

  virtual void enterBreak(SCCompilerParser::BreakContext *ctx) = 0;
  virtual void exitBreak(SCCompilerParser::BreakContext *ctx) = 0;

  virtual void enterFuncCallStatement(SCCompilerParser::FuncCallStatementContext *ctx) = 0;
  virtual void exitFuncCallStatement(SCCompilerParser::FuncCallStatementContext *ctx) = 0;

  virtual void enterExplicitTypeConversion(SCCompilerParser::ExplicitTypeConversionContext *ctx) = 0;
  virtual void exitExplicitTypeConversion(SCCompilerParser::ExplicitTypeConversionContext *ctx) = 0;

  virtual void enterPrefixAOPExpr(SCCompilerParser::PrefixAOPExprContext *ctx) = 0;
  virtual void exitPrefixAOPExpr(SCCompilerParser::PrefixAOPExprContext *ctx) = 0;

  virtual void enterParenthesisExpr(SCCompilerParser::ParenthesisExprContext *ctx) = 0;
  virtual void exitParenthesisExpr(SCCompilerParser::ParenthesisExprContext *ctx) = 0;

  virtual void enterLogicalNotOPExpr(SCCompilerParser::LogicalNotOPExprContext *ctx) = 0;
  virtual void exitLogicalNotOPExpr(SCCompilerParser::LogicalNotOPExprContext *ctx) = 0;

  virtual void enterLiteralExpr(SCCompilerParser::LiteralExprContext *ctx) = 0;
  virtual void exitLiteralExpr(SCCompilerParser::LiteralExprContext *ctx) = 0;

  virtual void enterCompExpr(SCCompilerParser::CompExprContext *ctx) = 0;
  virtual void exitCompExpr(SCCompilerParser::CompExprContext *ctx) = 0;

  virtual void enterAOPExpr(SCCompilerParser::AOPExprContext *ctx) = 0;
  virtual void exitAOPExpr(SCCompilerParser::AOPExprContext *ctx) = 0;

  virtual void enterUnaryExpr(SCCompilerParser::UnaryExprContext *ctx) = 0;
  virtual void exitUnaryExpr(SCCompilerParser::UnaryExprContext *ctx) = 0;

  virtual void enterLogicalOPExpr(SCCompilerParser::LogicalOPExprContext *ctx) = 0;
  virtual void exitLogicalOPExpr(SCCompilerParser::LogicalOPExprContext *ctx) = 0;

  virtual void enterFuncCallExpr(SCCompilerParser::FuncCallExprContext *ctx) = 0;
  virtual void exitFuncCallExpr(SCCompilerParser::FuncCallExprContext *ctx) = 0;

  virtual void enterExprList(SCCompilerParser::ExprListContext *ctx) = 0;
  virtual void exitExprList(SCCompilerParser::ExprListContext *ctx) = 0;

  virtual void enterAssignment(SCCompilerParser::AssignmentContext *ctx) = 0;
  virtual void exitAssignment(SCCompilerParser::AssignmentContext *ctx) = 0;

  virtual void enterForStatement(SCCompilerParser::ForStatementContext *ctx) = 0;
  virtual void exitForStatement(SCCompilerParser::ForStatementContext *ctx) = 0;

  virtual void enterForVarDecl(SCCompilerParser::ForVarDeclContext *ctx) = 0;
  virtual void exitForVarDecl(SCCompilerParser::ForVarDeclContext *ctx) = 0;

  virtual void enterForCondition(SCCompilerParser::ForConditionContext *ctx) = 0;
  virtual void exitForCondition(SCCompilerParser::ForConditionContext *ctx) = 0;

  virtual void enterForIncrements(SCCompilerParser::ForIncrementsContext *ctx) = 0;
  virtual void exitForIncrements(SCCompilerParser::ForIncrementsContext *ctx) = 0;

  virtual void enterForInc(SCCompilerParser::ForIncContext *ctx) = 0;
  virtual void exitForInc(SCCompilerParser::ForIncContext *ctx) = 0;


};


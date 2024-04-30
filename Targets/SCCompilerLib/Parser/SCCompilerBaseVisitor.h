
// Generated from ./Targets/SCCompilerLib/Parser/SCCompiler.g4 by ANTLR 4.13.1

#pragma once


#include "antlr4-runtime.h"
#include "SCCompilerVisitor.h"


/**
 * This class provides an empty implementation of SCCompilerVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class  SCCompilerBaseVisitor : public SCCompilerVisitor {
public:

  virtual std::any visitProgram(SCCompilerParser::ProgramContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitVarDecl(SCCompilerParser::VarDeclContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitVarInit(SCCompilerParser::VarInitContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitType(SCCompilerParser::TypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFuncDeclaration(SCCompilerParser::FuncDeclarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFormalParameters(SCCompilerParser::FormalParametersContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFuncArgDeclaration(SCCompilerParser::FuncArgDeclarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBlock(SCCompilerParser::BlockContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBlockStatement(SCCompilerParser::BlockStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitVarDeclStatement(SCCompilerParser::VarDeclStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitIfStatement(SCCompilerParser::IfStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitIgnore(SCCompilerParser::IgnoreContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitWhileStatement(SCCompilerParser::WhileStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitDoWhileStatement(SCCompilerParser::DoWhileStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitReturnStatement(SCCompilerParser::ReturnStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitContinue(SCCompilerParser::ContinueContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBreak(SCCompilerParser::BreakContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFuncCallStatement(SCCompilerParser::FuncCallStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitExplicitTypeConversion(SCCompilerParser::ExplicitTypeConversionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPrefixAOPExpr(SCCompilerParser::PrefixAOPExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitParenthesisExpr(SCCompilerParser::ParenthesisExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLogicalNotOPExpr(SCCompilerParser::LogicalNotOPExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLiteralExpr(SCCompilerParser::LiteralExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCompExpr(SCCompilerParser::CompExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAOPExpr(SCCompilerParser::AOPExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitUnaryExpr(SCCompilerParser::UnaryExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLogicalOPExpr(SCCompilerParser::LogicalOPExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFuncCallExpr(SCCompilerParser::FuncCallExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitExprList(SCCompilerParser::ExprListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAssignment(SCCompilerParser::AssignmentContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitForStatement(SCCompilerParser::ForStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitForVarDecl(SCCompilerParser::ForVarDeclContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitForCondition(SCCompilerParser::ForConditionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitForIncrements(SCCompilerParser::ForIncrementsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitForInc(SCCompilerParser::ForIncContext *ctx) override {
    return visitChildren(ctx);
  }


};


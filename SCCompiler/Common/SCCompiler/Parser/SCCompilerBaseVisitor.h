
// Generated from ./Common/SCCompiler/Parser/SCCompiler.g4 by ANTLR 4.7.1

#pragma once


#include "antlr4-runtime.h"
#include "SCCompilerVisitor.h"


/**
 * This class provides an empty implementation of SCCompilerVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class  SCCompilerBaseVisitor : public SCCompilerVisitor {
public:

  virtual antlrcpp::Any visitProgram(SCCompilerParser::ProgramContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitVarDecl(SCCompilerParser::VarDeclContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitType(SCCompilerParser::TypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitFuncDeclaration(SCCompilerParser::FuncDeclarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitFormalParameters(SCCompilerParser::FormalParametersContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitFuncArgDeclaration(SCCompilerParser::FuncArgDeclarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitBlock(SCCompilerParser::BlockContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitBlockStatement(SCCompilerParser::BlockStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitVarDeclStatement(SCCompilerParser::VarDeclStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitReturnStatement(SCCompilerParser::ReturnStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitAssignmentStatement(SCCompilerParser::AssignmentStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitFuncCallStatement(SCCompilerParser::FuncCallStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitExprList(SCCompilerParser::ExprListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitExplicitTypeConversion(SCCompilerParser::ExplicitTypeConversionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitParenthesisExpr(SCCompilerParser::ParenthesisExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitLiteralExpr(SCCompilerParser::LiteralExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitAOPExpr(SCCompilerParser::AOPExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitFuncCallExpr(SCCompilerParser::FuncCallExprContext *ctx) override {
    return visitChildren(ctx);
  }


};


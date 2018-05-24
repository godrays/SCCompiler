
// Generated from ./Common/SCCompiler/Parser/SCCompiler.g4 by ANTLR 4.7.1

#pragma once


#include "antlr4-runtime.h"
#include "SCCompilerListener.h"


/**
 * This class provides an empty implementation of SCCompilerListener,
 * which can be extended to create a listener which only needs to handle a subset
 * of the available methods.
 */
class  SCCompilerBaseListener : public SCCompilerListener {
public:

  virtual void enterProgram(SCCompilerParser::ProgramContext * /*ctx*/) override { }
  virtual void exitProgram(SCCompilerParser::ProgramContext * /*ctx*/) override { }

  virtual void enterVarDecl(SCCompilerParser::VarDeclContext * /*ctx*/) override { }
  virtual void exitVarDecl(SCCompilerParser::VarDeclContext * /*ctx*/) override { }

  virtual void enterType(SCCompilerParser::TypeContext * /*ctx*/) override { }
  virtual void exitType(SCCompilerParser::TypeContext * /*ctx*/) override { }

  virtual void enterFuncDeclaration(SCCompilerParser::FuncDeclarationContext * /*ctx*/) override { }
  virtual void exitFuncDeclaration(SCCompilerParser::FuncDeclarationContext * /*ctx*/) override { }

  virtual void enterFormalParameters(SCCompilerParser::FormalParametersContext * /*ctx*/) override { }
  virtual void exitFormalParameters(SCCompilerParser::FormalParametersContext * /*ctx*/) override { }

  virtual void enterFuncArgDeclaration(SCCompilerParser::FuncArgDeclarationContext * /*ctx*/) override { }
  virtual void exitFuncArgDeclaration(SCCompilerParser::FuncArgDeclarationContext * /*ctx*/) override { }

  virtual void enterBlock(SCCompilerParser::BlockContext * /*ctx*/) override { }
  virtual void exitBlock(SCCompilerParser::BlockContext * /*ctx*/) override { }

  virtual void enterBlockStatement(SCCompilerParser::BlockStatementContext * /*ctx*/) override { }
  virtual void exitBlockStatement(SCCompilerParser::BlockStatementContext * /*ctx*/) override { }

  virtual void enterVarDeclStatement(SCCompilerParser::VarDeclStatementContext * /*ctx*/) override { }
  virtual void exitVarDeclStatement(SCCompilerParser::VarDeclStatementContext * /*ctx*/) override { }

  virtual void enterIfStatement(SCCompilerParser::IfStatementContext * /*ctx*/) override { }
  virtual void exitIfStatement(SCCompilerParser::IfStatementContext * /*ctx*/) override { }

  virtual void enterReturnStatement(SCCompilerParser::ReturnStatementContext * /*ctx*/) override { }
  virtual void exitReturnStatement(SCCompilerParser::ReturnStatementContext * /*ctx*/) override { }

  virtual void enterAssignmentStatement(SCCompilerParser::AssignmentStatementContext * /*ctx*/) override { }
  virtual void exitAssignmentStatement(SCCompilerParser::AssignmentStatementContext * /*ctx*/) override { }

  virtual void enterFuncCallStatement(SCCompilerParser::FuncCallStatementContext * /*ctx*/) override { }
  virtual void exitFuncCallStatement(SCCompilerParser::FuncCallStatementContext * /*ctx*/) override { }

  virtual void enterExprList(SCCompilerParser::ExprListContext * /*ctx*/) override { }
  virtual void exitExprList(SCCompilerParser::ExprListContext * /*ctx*/) override { }

  virtual void enterExplicitTypeConversion(SCCompilerParser::ExplicitTypeConversionContext * /*ctx*/) override { }
  virtual void exitExplicitTypeConversion(SCCompilerParser::ExplicitTypeConversionContext * /*ctx*/) override { }

  virtual void enterParenthesisExpr(SCCompilerParser::ParenthesisExprContext * /*ctx*/) override { }
  virtual void exitParenthesisExpr(SCCompilerParser::ParenthesisExprContext * /*ctx*/) override { }

  virtual void enterLogicalNotExpr(SCCompilerParser::LogicalNotExprContext * /*ctx*/) override { }
  virtual void exitLogicalNotExpr(SCCompilerParser::LogicalNotExprContext * /*ctx*/) override { }

  virtual void enterLiteralExpr(SCCompilerParser::LiteralExprContext * /*ctx*/) override { }
  virtual void exitLiteralExpr(SCCompilerParser::LiteralExprContext * /*ctx*/) override { }

  virtual void enterCompExpr(SCCompilerParser::CompExprContext * /*ctx*/) override { }
  virtual void exitCompExpr(SCCompilerParser::CompExprContext * /*ctx*/) override { }

  virtual void enterAOPExpr(SCCompilerParser::AOPExprContext * /*ctx*/) override { }
  virtual void exitAOPExpr(SCCompilerParser::AOPExprContext * /*ctx*/) override { }

  virtual void enterUnaryExpr(SCCompilerParser::UnaryExprContext * /*ctx*/) override { }
  virtual void exitUnaryExpr(SCCompilerParser::UnaryExprContext * /*ctx*/) override { }

  virtual void enterFuncCallExpr(SCCompilerParser::FuncCallExprContext * /*ctx*/) override { }
  virtual void exitFuncCallExpr(SCCompilerParser::FuncCallExprContext * /*ctx*/) override { }


  virtual void enterEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void exitEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void visitTerminal(antlr4::tree::TerminalNode * /*node*/) override { }
  virtual void visitErrorNode(antlr4::tree::ErrorNode * /*node*/) override { }

};


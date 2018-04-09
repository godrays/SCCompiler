
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

  virtual void enterFunctionDecl(SCCompilerParser::FunctionDeclContext * /*ctx*/) override { }
  virtual void exitFunctionDecl(SCCompilerParser::FunctionDeclContext * /*ctx*/) override { }

  virtual void enterFormalParameters(SCCompilerParser::FormalParametersContext * /*ctx*/) override { }
  virtual void exitFormalParameters(SCCompilerParser::FormalParametersContext * /*ctx*/) override { }

  virtual void enterFormalParameter(SCCompilerParser::FormalParameterContext * /*ctx*/) override { }
  virtual void exitFormalParameter(SCCompilerParser::FormalParameterContext * /*ctx*/) override { }

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

  virtual void enterArrayIndexExpr(SCCompilerParser::ArrayIndexExprContext * /*ctx*/) override { }
  virtual void exitArrayIndexExpr(SCCompilerParser::ArrayIndexExprContext * /*ctx*/) override { }

  virtual void enterBoolNotExpr(SCCompilerParser::BoolNotExprContext * /*ctx*/) override { }
  virtual void exitBoolNotExpr(SCCompilerParser::BoolNotExprContext * /*ctx*/) override { }

  virtual void enterMulDivExpr(SCCompilerParser::MulDivExprContext * /*ctx*/) override { }
  virtual void exitMulDivExpr(SCCompilerParser::MulDivExprContext * /*ctx*/) override { }

  virtual void enterNumberExpr(SCCompilerParser::NumberExprContext * /*ctx*/) override { }
  virtual void exitNumberExpr(SCCompilerParser::NumberExprContext * /*ctx*/) override { }

  virtual void enterVarRefExpr(SCCompilerParser::VarRefExprContext * /*ctx*/) override { }
  virtual void exitVarRefExpr(SCCompilerParser::VarRefExprContext * /*ctx*/) override { }

  virtual void enterUnaryNegationExpr(SCCompilerParser::UnaryNegationExprContext * /*ctx*/) override { }
  virtual void exitUnaryNegationExpr(SCCompilerParser::UnaryNegationExprContext * /*ctx*/) override { }

  virtual void enterPlusMinusExpr(SCCompilerParser::PlusMinusExprContext * /*ctx*/) override { }
  virtual void exitPlusMinusExpr(SCCompilerParser::PlusMinusExprContext * /*ctx*/) override { }

  virtual void enterCompExpr(SCCompilerParser::CompExprContext * /*ctx*/) override { }
  virtual void exitCompExpr(SCCompilerParser::CompExprContext * /*ctx*/) override { }

  virtual void enterParanthesisExpr(SCCompilerParser::ParanthesisExprContext * /*ctx*/) override { }
  virtual void exitParanthesisExpr(SCCompilerParser::ParanthesisExprContext * /*ctx*/) override { }

  virtual void enterFuncCallExpr(SCCompilerParser::FuncCallExprContext * /*ctx*/) override { }
  virtual void exitFuncCallExpr(SCCompilerParser::FuncCallExprContext * /*ctx*/) override { }

  virtual void enterNumber(SCCompilerParser::NumberContext * /*ctx*/) override { }
  virtual void exitNumber(SCCompilerParser::NumberContext * /*ctx*/) override { }


  virtual void enterEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void exitEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void visitTerminal(antlr4::tree::TerminalNode * /*node*/) override { }
  virtual void visitErrorNode(antlr4::tree::ErrorNode * /*node*/) override { }

};


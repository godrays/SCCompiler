
// Generated from ./Common/Parser/DemoCompiler.g4 by ANTLR 4.7.1

#pragma once


#include "antlr4-runtime.h"
#include "DemoCompilerListener.h"


/**
 * This class provides an empty implementation of DemoCompilerListener,
 * which can be extended to create a listener which only needs to handle a subset
 * of the available methods.
 */
class  DemoCompilerBaseListener : public DemoCompilerListener {
public:

  virtual void enterProgram(DemoCompilerParser::ProgramContext * /*ctx*/) override { }
  virtual void exitProgram(DemoCompilerParser::ProgramContext * /*ctx*/) override { }

  virtual void enterLine(DemoCompilerParser::LineContext * /*ctx*/) override { }
  virtual void exitLine(DemoCompilerParser::LineContext * /*ctx*/) override { }

  virtual void enterName(DemoCompilerParser::NameContext * /*ctx*/) override { }
  virtual void exitName(DemoCompilerParser::NameContext * /*ctx*/) override { }


  virtual void enterEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void exitEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void visitTerminal(antlr4::tree::TerminalNode * /*node*/) override { }
  virtual void visitErrorNode(antlr4::tree::ErrorNode * /*node*/) override { }

};


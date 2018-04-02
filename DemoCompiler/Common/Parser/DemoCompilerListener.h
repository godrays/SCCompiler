
// Generated from ./Common/Parser/DemoCompiler.g4 by ANTLR 4.7.1

#pragma once


#include "antlr4-runtime.h"
#include "DemoCompilerParser.h"


/**
 * This interface defines an abstract listener for a parse tree produced by DemoCompilerParser.
 */
class  DemoCompilerListener : public antlr4::tree::ParseTreeListener {
public:

  virtual void enterProgram(DemoCompilerParser::ProgramContext *ctx) = 0;
  virtual void exitProgram(DemoCompilerParser::ProgramContext *ctx) = 0;

  virtual void enterLine(DemoCompilerParser::LineContext *ctx) = 0;
  virtual void exitLine(DemoCompilerParser::LineContext *ctx) = 0;

  virtual void enterName(DemoCompilerParser::NameContext *ctx) = 0;
  virtual void exitName(DemoCompilerParser::NameContext *ctx) = 0;


};


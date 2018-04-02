
// Generated from ./Common/Parser/DemoCompiler.g4 by ANTLR 4.7.1

#pragma once


#include "antlr4-runtime.h"
#include "DemoCompilerVisitor.h"


/**
 * This class provides an empty implementation of DemoCompilerVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class  DemoCompilerBaseVisitor : public DemoCompilerVisitor {
public:

  virtual antlrcpp::Any visitProgram(DemoCompilerParser::ProgramContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitLine(DemoCompilerParser::LineContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitName(DemoCompilerParser::NameContext *ctx) override {
    return visitChildren(ctx);
  }


};


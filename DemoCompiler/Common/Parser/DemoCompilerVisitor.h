
// Generated from ./Common/Parser/DemoCompiler.g4 by ANTLR 4.7.1

#pragma once


#include "antlr4-runtime.h"
#include "DemoCompilerParser.h"



/**
 * This class defines an abstract visitor for a parse tree
 * produced by DemoCompilerParser.
 */
class  DemoCompilerVisitor : public antlr4::tree::AbstractParseTreeVisitor {
public:

  /**
   * Visit parse trees produced by DemoCompilerParser.
   */
    virtual antlrcpp::Any visitProgram(DemoCompilerParser::ProgramContext *context) = 0;

    virtual antlrcpp::Any visitLine(DemoCompilerParser::LineContext *context) = 0;

    virtual antlrcpp::Any visitName(DemoCompilerParser::NameContext *context) = 0;


};


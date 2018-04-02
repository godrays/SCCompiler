//
//  ParseTreeVisitor.cpp
//  DemoCompilerApp
//
//  Created by Arkin Terli on 4/1/18.
//  Copyright © 2018 Arkin Terli. All rights reserved.
//

#include "ParseTreeVisitor.hpp"


antlrcpp::Any ParseTreeVisitor::visitProgram(DemoCompilerParser::ProgramContext *ctx)
{
    return visitChildren(ctx);
}


antlrcpp::Any ParseTreeVisitor::visitLine(DemoCompilerParser::LineContext *ctx)
{
    return visitChildren(ctx);
}


antlrcpp::Any ParseTreeVisitor::visitName(DemoCompilerParser::NameContext *ctx)
{
    return visitChildren(ctx);
}

//
//  ParseTreeVisitor.hpp
//  DemoCompilerApp
//
//  Created by Arkin Terli on 4/1/18.
//  Copyright © 2018 Arkin Terli. All rights reserved.
//

#pragma once

#include "DemoCompilerBaseVisitor.h"


class  ParseTreeVisitor : public DemoCompilerBaseVisitor
{
public:
    
    antlrcpp::Any visitProgram(DemoCompilerParser::ProgramContext *ctx) override;
    
    antlrcpp::Any visitLine(DemoCompilerParser::LineContext *ctx) override;
    
    antlrcpp::Any visitName(DemoCompilerParser::NameContext *ctx) override;

};

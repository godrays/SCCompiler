//
//  ParseTreeListener.hpp
//  DemoCompilerApp
//
//  Created by Arkin Terli on 4/1/18.
//  Copyright © 2018 Arkin Terli. All rights reserved.
//

#pragma once

#include "DemoCompilerBaseListener.h"


class  ParseTreeListener : public DemoCompilerBaseListener
{
public:
    
    void enterProgram(DemoCompilerParser::ProgramContext *ctx) override;
    void exitProgram(DemoCompilerParser::ProgramContext *ctx) override;
    
    void enterLine(DemoCompilerParser::LineContext *ctx) override;
    void exitLine(DemoCompilerParser::LineContext *ctx) override;
    
    void enterName(DemoCompilerParser::NameContext *ctx) override;
    void exitName(DemoCompilerParser::NameContext *ctx) override;
};


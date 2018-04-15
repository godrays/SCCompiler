//
//  MyListen.hpp
//  SCCompilerApp
//
//  Created by Arkin Terli on 4/8/18.
//  Copyright © 2018 Arkin Terli. All rights reserved.
//

#pragma once

#include "SCCompilerBaseVisitor.h"


class  MyVisitor : public SCCompilerBaseVisitor
{
public:

    antlrcpp::Any visitPlusMinusExpr(SCCompilerParser::PlusMinusExprContext * ctx)
    {
        // Get Arithmetic Operator Type
        std::cout << ctx->children[1]->getText() << std::endl;
        
        return visitChildren(ctx);
    }

    antlrcpp::Any visitLiteralExpr(SCCompilerParser::LiteralExprContext * ctx)
    { 
        //PrintContext("L", ctx);

        return visitChildren(ctx);
    }

    antlrcpp::Any visitAssignmentStatement(SCCompilerParser::AssignmentStatementContext * ctx)
    {
        //PrintContext("A", ctx);
        return visitChildren(ctx);
    }

    antlrcpp::Any visitFuncDeclaration(SCCompilerParser::FuncDeclarationContext * ctx)
    {
        // Get all rules.
        auto type = ctx->type();
        auto ID = ctx->ID();
        auto formalParams = ctx->formalParameters();
        auto block = ctx->block();

        std::cout << "isType   : " << std::dec << (type != nullptr)           << std::endl;
        std::cout << "isID     : " << std::dec << (ID != nullptr)             << std::endl;
        std::cout << "isFParams: " << std::dec << (formalParams != nullptr)   << std::endl;
        std::cout << "isBlock  : " << std::dec << (block != nullptr)          << std::endl;
        std::cout << "ID Type  : " << std::dec << ctx->ID()->getSymbol()->getType()  << std::endl;

        return visitChildren(ctx);
    }

    antlrcpp::Any visitFuncArgDeclaration(SCCompilerParser::FuncArgDeclarationContext * ctx)
    {
        PrintContext("FAD", ctx);

        return visitChildren(ctx);
    }

    void PrintContext(std::string id, antlr4::ParserRuleContext * ctx)
    {
        auto rules = ctx->getRuleContexts<antlr4::ParserRuleContext>();
        auto size = rules.size();
        
        if (size > 0)
            std::cout   << id << "(" << std::dec << size << "): ";
        
        for (int i=0; i<size; ++i)
        {
            std::cout
            << "Text: " << rules[i]->getText() << " "
            << "Type: " << std::dec << rules[i]->getStart()->getType() << " - ";
        }
        
        if (size > 0)
            std::cout << std::endl;
    }


    void PrintChilds(std::string id, antlr4::ParserRuleContext * ctx)
    {
        auto rules = ctx->children;
        auto size = rules.size();
        
        if (size > 0)
            std::cout   << id << "(" << std::dec << size << "): ";
        
        for (int i=0; i<size; ++i)
        {
            std::cout
            << "Text: " << rules[i]->getText() << " "
            << "R: " << std::dec << dynamic_cast<antlr4::RuleContext *>(rules[i])  << " "
            << "T: " << std::dec << dynamic_cast<antlr4::tree::TerminalNode *>(rules[i])  << " ";
            //<< "Type: " << std::dec << rules[0]->getStart()->getType() << " - ";
        }
        
        if (size > 0)
            std::cout << std::endl;
    }


    void PrintTerminalNodes(std::string id, antlr4::ParserRuleContext * ctx)
    {
        auto rules = ctx->getRuleContexts<antlr4::ParserRuleContext>();
        auto size = rules.size();
        
        if (size > 0)
            std::cout   << id << "(" << std::dec << size << "): ";
        
        for (int i=0; i<size; ++i)
        {
            std::cout
            << "Text: " << rules[i]->getText() << " "
            << "Type: " << std::dec << rules[i]->getStart()->getType() << " - ";
        }
        
        if (size > 0)
            std::cout << std::endl;
    }
};


/*
class  MyVisitor : public SCCompilerBaseVisitor
{
public:
    antlrcpp::Any visitLiteralExpr(SCCompilerParser::LiteralExprContext * ctx)
    {
        switch (ctx->lit->getType())
        {
            case SCCompilerParser::FLOAT:
                std::cout << "FLOAT: " << ctx->lit->getText() << std::endl;
                break;
                
            case SCCompilerParser::INT:
                std::cout << "INT: " << ctx->lit->getText() << std::endl;
                break;
                
            default:
                std::cout << "???" << std::endl;
                break;
        }
        
        return visitChildren(ctx);
    }
};
*/


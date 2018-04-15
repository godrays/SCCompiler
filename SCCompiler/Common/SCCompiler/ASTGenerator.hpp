//
//  ASTGenerator.hpp
//
//  Created by Arkin Terli on 4/11/18.
//  Copyright © 2018 Arkin Terli. All rights reserved.
//

#pragma once

#include <stack>

#include "SCCompilerBaseVisitor.h"
#include "AST.hpp"


namespace SCCompiler
{

    class  ASTGenerator : public SCCompilerBaseVisitor
    {
    public:
        // Contructor.
        ASTGenerator() { }

        // Destructor.
        virtual ~ASTGenerator() { }

        // Return AST Node.
        AST::Node *   GetAST()    { return m_rootNode; }

        AST::Type     ToASTType(std::string);

        antlrcpp::Any  visitProgram(SCCompilerParser::ProgramContext *ctx) final;

        antlrcpp::Any  visitVarDecl(SCCompilerParser::VarDeclContext *ctx) final;

        antlrcpp::Any  visitFuncDeclaration(SCCompilerParser::FuncDeclarationContext *ctx) final;

        antlrcpp::Any  visitFuncArgDeclaration(SCCompilerParser::FuncArgDeclarationContext *ctx) final;

        antlrcpp::Any  visitBlock(SCCompilerParser::BlockContext *ctx) final;

        antlrcpp::Any  visitReturnStatement(SCCompilerParser::ReturnStatementContext *ctx) final;

        antlrcpp::Any  visitAssignmentStatement(SCCompilerParser::AssignmentStatementContext *ctx) final;

        antlrcpp::Any  visitLiteralExpr(SCCompilerParser::LiteralExprContext *ctx) final;

        antlrcpp::Any  visitMulDivExpr(SCCompilerParser::MulDivExprContext *ctx) final;

        antlrcpp::Any  visitPlusMinusExpr(SCCompilerParser::PlusMinusExprContext *ctx) final;

        antlrcpp::Any  visitFuncCallExpr(SCCompilerParser::FuncCallExprContext *ctx) final;

    protected:
        AST::Node *   m_rootNode = nullptr;
        std::stack<AST::Node *>  m_currentNodeStack;
    };

}

//
//  SCCompiler.cpp
//
//  Created by Arkin Terli on 4/10/18.
//  Copyright © 2018 Arkin Terli. All rights reserved.
//

#include <string>
#include <iostream>
#include <istream>
#include <sstream>

#include "antlr4-runtime.h"
#include "SCCompilerLexer.h"
#include "SCCompilerParser.h"

#include "Symbols.hpp"
#include "AST.hpp"
#include "ASTVisualizer.hpp"
#include "ASTGenerator.hpp"
#include "SymbolDefPass.hpp"
#include "SemanticPass.hpp"
#include "Exceptions.hpp"
#include "Compiler.hpp"


using namespace antlr4;


#pragma mark - Class ParserErrorListener.

class ParserErrorListener : public antlr4::BaseErrorListener
{
public:
    void syntaxError(Recognizer *recognizer, Token * offendingSymbol, size_t line, size_t charPositionInLine,
      const std::string &msg, std::exception_ptr e) override final
    {
        std::stringstream strStream;
        strStream << "Syntax Error - line " << line << ": " << charPositionInLine << " " << msg;
        m_message = strStream.str();
    }

    std::string GetErrorMessage() const     { return m_message; }

private:
    std::string  m_message;
};


#pragma mark - Compiler Implementations.


SCCompiler::CompileResult SCCompiler::Compiler::CompileFromFile(std::string filename)
{
    // Open test code source file.
    std::ifstream sourceCodeFile(filename);

    if (sourceCodeFile.is_open())
    {
        auto compileResult = Compile(sourceCodeFile);
        sourceCodeFile.close();
        return compileResult;
    }

    m_errorMessage = "Source code file not found.";
    return SCCompiler::CompileResult::rCompileResultCompileError;
}


SCCompiler::CompileResult SCCompiler::Compiler::CompileFromMemory(std::string sourceCode)
{
    std::istringstream sourceStream(sourceCode);
    
    return Compile(sourceStream);
}


SCCompiler::CompileResult SCCompiler::Compiler::Compile(std::istream & sourceStream)
{
    // Error listener for parser.
    ParserErrorListener  parserErrorListener;

    try
    {
        ANTLRInputStream    input(sourceStream);

        // Do lexical analysis and generate tokens.
        SCCompilerLexer   lexer(&input);
        // Remove default error listener and add ParserErrorListener.
        lexer.removeErrorListeners();
        lexer.addErrorListener(&parserErrorListener);
        
        // Create a stream of tokens.
        CommonTokenStream   tokenStream(&lexer);

        // Parse token stream, which is syntax analysis.
        // Parser makes sure tokens are in right order while generating a parser tree (AST).
        SCCompilerParser parser(&tokenStream);
        // Remove default error listener and add ParserErrorListener.
        parser.removeErrorListeners();
        parser.addErrorListener(&parserErrorListener);

        // Generate tree by calling the first parser rule in grammar.
        tree::ParseTree *  parseTree = parser.program();

        // Stop if there is a syntax error.
        if (lexer.getNumberOfSyntaxErrors() > 0 || parser.getNumberOfSyntaxErrors() > 0)
        {
            m_errorMessage = parserErrorListener.GetErrorMessage();
            return SCCompiler::CompileResult::rCompileResultSyntaxError;
        }

        // Generate AST from Parse Tree.
        ASTGenerator astGenVisitor;
        astGenVisitor.visit(parseTree);
        auto ast = astGenVisitor.GetAST();

        // DEBUG ONLY -----------------
        // Generate Graphviz DOT file to visualize AST.
        ASTVisualizer   astVisualizer;
        astVisualizer.GenerateDOTFile(ast, "/Users/arkin/Projects/Compiler/SCCompiler/ast.dot");
        // DEBUG ONLY -----------------

        // PASS: Create scope tree and define symbols by visiting AST nodes.
        //       After this pass, each ast node and symbos will have access to their related scope node (symbol table).
        SymbolDefPass  symDefPass;
        auto scopeTree = symDefPass.CreateScopeTree(ast);

        // PASS: Perform semantic anaylsis by visiting AST nodes.
        //       Semantic anaylsis: Resolving Symbols, Typecheking, Type Promotion, Semantic Validation.
        SemanticPass  semanticAnalysisPass;
        semanticAnalysisPass.SemanticCheck(ast);

        delete scopeTree;
        delete ast;
    }
    catch (SemanticErrorException & e)
    {
        m_errorMessage = e.what();
        return SCCompiler::CompileResult::rCompileResultSemanticError;
    }
    catch (CompileErrorException & e)
    {
        m_errorMessage = e.what();
        return SCCompiler::CompileResult::rCompileResultCompileError;
    }
    catch (std::exception & e)
    {
        m_errorMessage = e.what();
        return SCCompiler::CompileResult::rCompileResultCompileError;
    }

    return SCCompiler::CompileResult::rCompileResultOk;
}


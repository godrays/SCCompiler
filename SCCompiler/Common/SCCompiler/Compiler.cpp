//
//  SCC.cpp
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
#include "CodeGenPass.hpp"
#include "Exceptions.hpp"
#include "JITEngine.hpp"
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


SCC::SCModule * SCC::Compiler::CompileFromFile(std::string filename, SCC::SCCompileResult & compileResult)
{
    // Open test code source file.
    std::ifstream sourceCodeFile(filename);

    if (sourceCodeFile.is_open())
    {
        auto scModule = Compile(sourceCodeFile, compileResult);
        sourceCodeFile.close();
        return scModule;
    }

    m_errorMessage = "Source code file not found.";
    compileResult = SCC::SCCompileResult::rSCCompileResultCompileError;
    return nullptr;
}


SCC::SCModule * SCC::Compiler::CompileFromMemory(std::string sourceCode, SCC::SCCompileResult & compileResult)
{
    std::istringstream sourceStream(sourceCode);
    
    return Compile(sourceStream, compileResult);
}


SCC::SCModule * SCC::Compiler::Compile(std::istream & sourceStream, SCC::SCCompileResult & compileResult)
{
    // Error listener for parser.
    ParserErrorListener  parserErrorListener;
    SCModule * scModule = nullptr;
    
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
            compileResult = SCC::SCCompileResult::rSCCompileResultSyntaxError;
            return nullptr;
        }

        // Generate AST from Parse Tree.
        ASTGenerator astGenVisitor;
        astGenVisitor.visit(parseTree);
        auto ast = astGenVisitor.GetAST();

        // DEBUG ONLY -----------------
        // Generate Graphviz DOT file to visualize AST.
        ASTVisualizer   astVisualizer;
        astVisualizer.GenerateDOTFile(ast, "/Users/arkin/Projects/Compiler/SCC/ast.dot");
        // DEBUG ONLY -----------------

        // PASS: Create scope tree and define symbols by visiting AST nodes.
        //       After this pass, each ast node and symbols will have access to their related scope node (symbol table).
        SymbolDefPass  symDefPass;
        auto scopeTree = symDefPass.CreateScopeTree(ast);

        // PASS: Perform semantic analysis by visiting AST nodes.
        //       Semantic anaylsis: Resolving Symbols, Typecheking, Type Promotion, Semantic Validation.
        SemanticPass  semanticAnalysisPass;
        semanticAnalysisPass.SemanticCheck(ast);

        // PASS: Perform code generation by visiting AST nodes and create program execution module: SCModule.
        CodeGenPass codeGenerationPass;
        scModule = codeGenerationPass.GenerateCode(ast);

        delete scopeTree;
        delete ast;
    }
    catch (SemanticErrorException & e)
    {
        m_errorMessage = e.what();
        compileResult = SCC::SCCompileResult::rSCCompileResultSemanticError;
        return nullptr;
    }
    catch (CompileErrorException & e)
    {
        m_errorMessage = e.what();
        compileResult = SCC::SCCompileResult::rSCCompileResultCompileError;
        return nullptr;
    }
    catch (std::exception & e)
    {
        m_errorMessage = e.what();
        compileResult = SCC::SCCompileResult::rSCCompileResultCompileError;
        return nullptr;
    }

    compileResult = SCC::SCCompileResult::rSCCompileResultOk;
    return scModule;
}


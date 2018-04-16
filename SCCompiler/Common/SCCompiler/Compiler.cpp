//
//  SCCompiler.cpp
//
//  Created by Arkin Terli on 4/10/18.
//  Copyright © 2018 Arkin Terli. All rights reserved.
//

#include <iostream>
#include <sstream>

#include "antlr4-runtime.h"
#include "SCCompilerLexer.h"
#include "SCCompilerParser.h"

#include "ASTVisualizer.hpp"
#include "ASTGenerator.hpp"
#include "SymbolDefPass.hpp"
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


SCCompiler::CompileResult SCCompiler::Compiler::Compile(std::string filename)
{
    // Error listener for parser.
    ParserErrorListener  parserErrorListener;

    try
    {
        // Open test code source file.
        std::ifstream testCodeFile(filename);
        
        if (testCodeFile.is_open())
        {
            //ANTLRInputStream    input("int x=5; int main() { float i=5; return 0; }\n");
            ANTLRInputStream    input(testCodeFile);

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
        
            // Generate Graphviz DOT file to visualize AST.
            ASTVisualizer   astVisualizer;
            astVisualizer.GenerateDOTFile(ast, "/Users/arkin/Projects/Compiler/SCCompiler/ast.dot");

            // PASS: Create scope tree by visiting AST nodes and defining symbols.
            SymbolDefPass  symDefPass;
            symDefPass.CreateScopeTree(ast);

            testCodeFile.close();
        }
        else
        {
            std::cerr << "ERROR: Test code file could not found." << std::endl;
            return SCCompiler::CompileResult::rCompileResultCompileError;
        }
    }
    catch (SemanticErrorException & e)
    {
        m_errorMessage = e.what();
        return SCCompiler::CompileResult::rCompileResultSemanticError;
    }
    catch (CompileErrorException & e)
    {
        m_errorMessage = e.what();
        return SCCompiler::CompileResult::rCompileResultSemanticError;
    }
    catch (std::exception & e)
    {
        m_errorMessage = e.what();
        return SCCompiler::CompileResult::rCompileResultCompileError;
    }

    return SCCompiler::CompileResult::rCompileResultOk;
}


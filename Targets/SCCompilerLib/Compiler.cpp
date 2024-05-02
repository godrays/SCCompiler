//
//  Created by Arkin Terli on 4/10/18.
//  Copyright © 2018-Present, Arkin Terli. All rights reserved.
//

// Project includes
#include "Compiler.hpp"
#include "ASTGenerator.hpp"
#include "CodeGenPass.hpp"
#include "Exceptions.hpp"
#include "JITEngine.hpp"
#include "SemanticPass.hpp"
#include "SymbolDefPass.hpp"
#include <Parser/SCCompilerLexer.h>
#include <Parser/SCCompilerParser.h>
// External includes
#include <antlr4-runtime.h>
// System includes
#include <string>
#include <istream>


using namespace antlr4;


#pragma mark - Class ParserErrorListener.

class ParserErrorListener : public antlr4::BaseErrorListener
{
public:
    void syntaxError(Recognizer *recognizer, Token * offendingSymbol, size_t line, size_t charPositionInLine,
      const std::string &msg, std::exception_ptr e) final
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

scc::SCModule * scc::Compiler::CompileFromFile(std::string filename, scc::SCCompileResult & compileResult)
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
    compileResult = scc::SCCompileResult::kSCCompileResultCompileError;
    return nullptr;
}


scc::SCModule * scc::Compiler::CompileFromMemory(std::string sourceCode, scc::SCCompileResult & compileResult)
{
    std::istringstream sourceStream(sourceCode);
    
    return Compile(sourceStream, compileResult);
}


scc::SCModule * scc::Compiler::Compile(std::istream & sourceStream, scc::SCCompileResult & compileResult)
{
    // Error listener for the parser.
    ParserErrorListener  parserErrorListener;
    SCModule * scModule{nullptr};

    try
    {
        ANTLRInputStream    input(sourceStream);

        // Perform lexical analysis and generate tokens.
        SCCompilerLexer   lexer(&input);
        // Remove the default error listener and add ParserErrorListener.
        lexer.removeErrorListeners();
        lexer.addErrorListener(&parserErrorListener);

        // Create a stream of tokens.
        CommonTokenStream   tokenStream(&lexer);

        // Parse the token stream, which is syntax analysis.
        // The parser makes sure tokens are in the right order while generating a parser tree (AST).
        SCCompilerParser parser(&tokenStream);
        // Remove the default error listener and add ParserErrorListener.
        parser.removeErrorListeners();
        parser.addErrorListener(&parserErrorListener);

        // Generate a tree by calling the first parser rule in the grammar.
        tree::ParseTree *  parseTree = parser.program();

        // Stop if there is a syntax error.
        if (lexer.getNumberOfSyntaxErrors() > 0 || parser.getNumberOfSyntaxErrors() > 0)
        {
            m_errorMessage = parserErrorListener.GetErrorMessage();
            compileResult = scc::SCCompileResult::kSCCompileResultSyntaxError;
            return nullptr;
        }

        // Generate an AST from the Parse Tree.
        ASTGenerator astGenVisitor;
        astGenVisitor.visit(parseTree);
        auto ast = astGenVisitor.GetAST();

        // DEBUG ONLY -----------------
        // Generate a Graphviz DOT file to visualize the AST.
        //ASTVisualizer astVisualizer;
        //astVisualizer.GenerateDOTFile(ast, "ast.dot");
        // DEBUG ONLY -----------------

        // PASS: Create a scope tree and define symbols by visiting AST nodes.
        //       After this pass, each AST node and symbol will have access to its related scope node (symbol table).
        SymbolDefPass  symDefPass{};
        auto scopeTree = symDefPass.CreateScopeTree(ast);

        // PASS: Perform semantic analysis by visiting AST nodes.
        //       Semantic analysis: Resolving Symbols, Type checking, Type Promotion, Semantic Validation.
        SemanticPass  semanticAnalysisPass;
        semanticAnalysisPass.SemanticCheck(ast);

        // PASS: Perform code generation by visiting AST nodes and create a program execution module: SCModule.
        CodeGenPass codeGenerationPass;
        scModule = codeGenerationPass.GenerateCode(ast);

        // Initialize global variables.
        if (scModule)
        {
            scModule->Reset();
        }

        delete scopeTree;
        delete ast;
    }
    catch (SemanticErrorException & e)
    {
        m_errorMessage = e.what();
        compileResult = scc::SCCompileResult::kSCCompileResultSemanticError;
        return nullptr;
    }
    catch (CompileErrorException & e)
    {
        m_errorMessage = e.what();
        compileResult = scc::SCCompileResult::kSCCompileResultCompileError;
        return nullptr;
    }
    catch (std::exception & e)
    {
        m_errorMessage = e.what();
        compileResult = scc::SCCompileResult::kSCCompileResultCompileError;
        return nullptr;
    }

    compileResult = scc::SCCompileResult::kSCCompileResultOk;
    return scModule;
}

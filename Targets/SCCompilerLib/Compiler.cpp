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
#include <memory>
#include <string>
#include <istream>


using namespace antlr4;


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

    std::string getErrorMessage() const     { return m_message; }

private:
    std::string  m_message;
};


std::unique_ptr<scc::SCModule> scc::Compiler::compileFromFile(std::string filename,
                                                              scc::SCCompileResult & compileResult)
{
    // Open test code source file.
    std::ifstream sourceCodeFile(filename);

    if (sourceCodeFile.is_open())
    {
        auto scModule = compile(sourceCodeFile, compileResult);
        sourceCodeFile.close();
        return scModule;
    }

    m_errorMessage = "Source code file not found.";
    compileResult = scc::SCCompileResult::kCompileError;
    return nullptr;
}


std::unique_ptr<scc::SCModule> scc::Compiler::compileFromMemory(std::string sourceCode,
                                                                scc::SCCompileResult & compileResult)
{
    std::istringstream sourceStream(sourceCode);
    
    return compile(sourceStream, compileResult);
}


std::unique_ptr<scc::SCModule> scc::Compiler::compile(std::istream & sourceStream,
                                                      scc::SCCompileResult & compileResult)
{
    // Error listener for the parser.
    ParserErrorListener  parserErrorListener;
    std::unique_ptr<SCModule> scModule;

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
            m_errorMessage = parserErrorListener.getErrorMessage();
            compileResult = scc::SCCompileResult::kSyntaxError;
            return nullptr;
        }

        // Generate an AST from the Parse Tree.
        ASTGenerator astGenVisitor;
        astGenVisitor.visit(parseTree);
        auto ast = astGenVisitor.takeAST();

        // DEBUG ONLY -----------------
        // Generate a Graphviz DOT file to visualize the AST.
        //ASTVisualizer astVisualizer;
        //astVisualizer.GenerateDOTFile(ast, "ast.dot");
        // DEBUG ONLY -----------------

        // PASS: Create a scope tree and define symbols by visiting AST nodes.
        //       After this pass, each AST node and symbol will have access to its related scope node (symbol table).
        SymbolDefPass  symDefPass{};
        auto scopeTree = symDefPass.createScopeTree(ast.get());

        // PASS: Perform semantic analysis by visiting AST nodes.
        //       Semantic analysis: Resolving Symbols, Type checking, Type Promotion, Semantic Validation.
        SemanticPass  semanticAnalysisPass;
        semanticAnalysisPass.semanticCheck(ast.get());

        // PASS: Perform code generation by visiting AST nodes and create a program execution module: SCModule.
        CodeGenPass codeGenerationPass;
        scModule = codeGenerationPass.generateCode(ast.get());

        // Initialize global variables.
        if (scModule)
        {
            scModule->reset();
        }

    }
    catch (SemanticErrorException & e)
    {
        m_errorMessage = e.what();
        compileResult = scc::SCCompileResult::kSemanticError;
        return nullptr;
    }
    catch (CompileErrorException & e)
    {
        m_errorMessage = e.what();
        compileResult = scc::SCCompileResult::kCompileError;
        return nullptr;
    }
    catch (std::exception & e)
    {
        m_errorMessage = e.what();
        compileResult = scc::SCCompileResult::kCompileError;
        return nullptr;
    }

    compileResult = scc::SCCompileResult::kOk;
    return scModule;
}

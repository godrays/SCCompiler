//
//  SCCompiler.cpp
//
//  Created by Arkin Terli on 4/10/18.
//  Copyright © 2018 Arkin Terli. All rights reserved.
//

#include <iostream>

#include "antlr4-runtime.h"
#include "SCCompilerLexer.h"
#include "SCCompilerParser.h"

#include "MyVisitor.hpp"

#include "ASTVisualizer.hpp"
#include "ASTGenerator.hpp"
#include "Compiler.hpp"

using namespace antlr4;


#pragma mark - Compiler Implementations

bool SCCompiler::Compiler::Compile(std::string filename)
{
    // Open test code source file.
    std::ifstream testCodeFile(filename);
    
    if (testCodeFile.is_open())
    {
        //ANTLRInputStream    input("int x=5; int main() { float i=5; return 0; }\n");
        ANTLRInputStream    input(testCodeFile);

        // Do lexical analysis and generate tokens.
        SCCompilerLexer   lexer(&input);
        // Create a stream of tokens.
        CommonTokenStream   tokenStream(&lexer);
        
        // Print all identified tokens.
        tokenStream.fill();

        // Print all tokens
        /*
        for (auto token : tokenStream.getTokens())
        {
            std::cout << token->toString() << std::endl;
        }
        */
        // Parse token stream, which is syntax analysis.
        // Parser makes sure tokens are in rigt order while generating a parser tree (AST).
        SCCompilerParser parser(&tokenStream);
        
        // Generate tree by calling the first parser rule in grammar.
        tree::ParseTree*  parseTree = parser.program();

        // Print all tokens.
        //std::cout << parseTree->toStringTree(&parser) << std::endl;
        
        // FIRST PASS - Generate symbol table by using listener to resolve symbol issues.
        //MyListener listener;
        //tree::ParseTreeWalker::DEFAULT.walk(&listener, parseTree);
        
        // SECOND PASS - Generate code by using visitor.
        // In this phase, you can build your AST to mitigate complexity for your code generator or interpreter.
        // A special AST may help building a better code generator or a language transformer (i.e. From Java to C#)
        // If you use LLVM for code generation, default ANTLR's visitor implementation should be enough.
        //MyVisitor visitor;
        //visitor.visit(parseTree);
        
        // Generate AST from Parse Tree.
        ASTGenerator astGenVisitor;
        astGenVisitor.visit(parseTree);
        auto ast = astGenVisitor.GetAST();
        
        // Generate Graphviz DOT file to to visualize AST.
        ASTVisualizer   astVisualizer;
        astVisualizer.GenerateDOTFile(ast, "/Users/arkin/Projects/Compiler/SCCompiler/ast.dot");

        testCodeFile.close();
    }
    else
    {
        std::cout << "ERROR: Test code file could not found." << std::endl;
        return false;
    }

    return true;
}

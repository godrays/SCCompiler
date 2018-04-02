//
//  main.cpp
//  DemoCompiler
//
//  Created by Arkin Terli on 3/31/18.
//  Copyright © 2018 Arkin Terli. All rights reserved.
//

#include <iostream>

#include "antlr4-runtime.h"
#include "DemoCompilerLexer.h"
#include "DemoCompilerParser.h"

#include "ParseTreeListener.hpp"
#include "ParseTreeVisitor.hpp"

using namespace antlr4;


int main(int , const char **)
{
    // Open test code source file.
    std::ifstream testCodeFile("DemoCompilerTestCode.src");
    
    if (testCodeFile.is_open())
    {
        //ANTLRInputStream    input("Arkin\n Terli \n");
        ANTLRInputStream    input(testCodeFile);

        // Do lexical analysis and generate tokens/token stream.
        DemoCompilerLexer   lexer(&input);
        CommonTokenStream   tokens(&lexer);
        
        // Print all identified tokens.
        tokens.fill();
        for (auto token : tokens.getTokens())
        {
            std::cout << token->toString() << std::endl;
        }
        
        // Parse token stream, which is symantic analysis.
        // Parser makes sure tokens are in rigt order while generating a parser tree (AST).
        DemoCompilerParser parser(&tokens);
        
        // Generate tree by calling the first parser rule in grammar.
        tree::ParseTree*  parseTree = parser.program();
        // Print all tokens.
        std::cout << parseTree->toStringTree(&parser) << std::endl;
        
        // FIRST PASS - Generate symbol table by using listener to resolve symbol issues.
        ParseTreeListener listener;
        tree::ParseTreeWalker::DEFAULT.walk(&listener, parseTree);
        
        // SECOND PASS - Generate code by using visitor.
        // In this phase, you can build your AST to mitigate complexity for your code generator or interpreter.
        // A special AST may help building a better code generator or a language transformer (i.e. From Java to C#)
        // If you use LLVM for code generation, default ANTLR's visitor implementation should be enough.
        ParseTreeVisitor visitor;
        visitor.visit(parseTree);

        testCodeFile.close();
    } else
    {
        std::cout << "ERROR: Test code file could not found." << std::endl;
    }
    
    return 0;
}

//
//  ASTVisualizer.hpp
//
//  Created by Arkin Terli on 4/13/18.
//  Copyright © 2018 Arkin Terli. All rights reserved.
//

#pragma once

#include <fstream>

#include "AST.hpp"


namespace SCCompiler
{
    
    #pragma mark - Class ASTVisualizer

    class  ASTVisualizer
    {
    public:
        // Contructor.
        ASTVisualizer() { }

        // Destructor.
        virtual ~ASTVisualizer() { }

        // Genearates DOT file from AST tree and outputs to a file.
        void GenerateDOTFile(AST::Node * node, std::string filename);

    protected:
        // Visits node to genearte Graphviz DOT file for visualization.
        void Visit(AST::Node * node);
    
        // Output string for a node
        void OutputConfig(AST::Node * node, const std::string & nodeConfig);

        // Output variable declaration node string.
        void OutputConfigVariableDecl(AST::Node * node);

        // Output function declaration node string.
        void OutputConfigFuncDecl(AST::Node * node);

    private:
        // Output file.
        std::ofstream   m_outputFile;
    };
    
}

//
//  ASTVisualizer.hpp
//
//  Created by Arkin Terli on 4/13/18.
//  Copyright © 2018-Present, Arkin Terli. All rights reserved.
//

#pragma once

// Project includes
// External includes
// System includes
#include <fstream>


namespace scc
{

// Forward declaration.
namespace ast
{
    class Node;
}


#pragma mark - Class ASTVisualizer

class  ASTVisualizer
{
public:
    // Constructor.
    ASTVisualizer() = default;

    // Destructor.
    virtual ~ASTVisualizer() = default;

    // Generates DOT file from AST tree and outputs to a file.
    void GenerateDOTFile(ast::Node * node, const std::string& filename);

protected:
    // Visits node to generate Graphviz DOT file for visualization.
    void Visit(ast::Node * node);

    // Output string for a node
    void OutputConfig(ast::Node * node, const std::string & nodeConfig);

    // Output variable declaration node string.
    void OutputConfigVariableDecl(ast::Node * node);

    // Output function declaration node string.
    void OutputConfigFuncDecl(ast::Node * node);

private:
    // Output file.
    std::ofstream   m_outputFile;
};
    
}

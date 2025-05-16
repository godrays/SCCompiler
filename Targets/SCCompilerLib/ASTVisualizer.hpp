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


class  ASTVisualizer
{
public:
    // Constructor.
    ASTVisualizer() = default;

    // Destructor.
    virtual ~ASTVisualizer() = default;

    // Generates DOT file from AST tree and outputs to a file.
    void generateDOTFile(ast::Node * node, const std::string& filename);

protected:
    // Visits node to generate Graphviz DOT file for visualization.
    void visit(ast::Node * node);

    // Output string for a node
    void outputConfig(ast::Node * node, const std::string & nodeConfig);

    // Output variable declaration node string.
    void outputConfigVariableDecl(ast::Node * node);

    // Output function declaration node string.
    void outputConfigFuncDecl(ast::Node * node);

private:
    std::ofstream   m_outputFile;       // Output file.
};
    
}

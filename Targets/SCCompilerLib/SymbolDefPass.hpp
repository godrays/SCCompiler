//
//  Created by Arkin Terli on 4/15/18.
//  Copyright © 2018-Present, Arkin Terli. All rights reserved.
//

#pragma once

// Project includes
#include "AST.hpp"
// External includes
// System includes
#include <memory>


namespace scc
{

// Forward declaration.
class ScopeNode;

// Forward declaration.
namespace ast
{
    class Node;
    class NodeVariableDeclaration;
    class NodeFunctionDeclaration;
    class NodeBlock;
}


class  SymbolDefPass
{
public:
    // Default constructor.
    SymbolDefPass() = default;

    // Creates a scope tree and defines symbols based on the AST nodes.
    std::unique_ptr<ScopeNode> createScopeTree(ast::Node * node);

private:
    // Visits nodes to create scopes and define symbols.
    void visit(ast::Node * node);

    // Visits node's children.
    void visitChildren(ast::Node * node);

    void visitVariableDeclaration(ast::NodeVariableDeclaration * node);

    void visitFunctionDeclaration(ast::NodeFunctionDeclaration * node);

    void visitForStatement(ast::NodeForStatement * node);

    void visitBlock(ast::NodeBlock * node);

    void visitFunctionCall(ast::NodeFunctionCall * node);

    void visitLiteral(ast::NodeLiteral * node);

private:
    ScopeNode *  m_currentScope{nullptr};       // Stores the current scope.
};

}

//
//  Created by Arkin Terli on 4/15/18.
//  Copyright © 2018-Present, Arkin Terli. All rights reserved.
//

#pragma once

// Project includes
#include "AST.hpp"
// External includes
// System includes


namespace scc
{

// Forward declaration.
class ScopeNode;

// Forward declaration.
namespace ast
{
    class Node;
    class NodeVarDeclaration;
    class NodeFuncDeclaration;
    class NodeBlock;
}


class  SymbolDefPass
{
public:
    // Default constructor.
    SymbolDefPass() = default;

    // Creates a scope tree and defines symbols based on the AST nodes.
    ScopeNode * createScopeTree(ast::Node * node);

private:
    // Visits nodes to create scopes and define symbols.
    void visit(ast::Node * node);

    // Visits node's children.
    void visitChildren(ast::Node * node);

    void visitVariableDeclaration(ast::NodeVarDeclaration * node);

    void visitFunctionDeclaration(ast::NodeFuncDeclaration * node);

    void visitForStatement(ast::NodeForStatement * node);

    void visitBlock(ast::NodeBlock * node);

    void visitFunctionCall(ast::NodeFuncCall * node);

    void visitLiteral(ast::NodeLiteral * node);

private:
    // Stores the current scope.
    ScopeNode *  m_currentScope{nullptr};
};

}

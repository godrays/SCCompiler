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


#pragma mark - Class SymbolDefPass

class  SymbolDefPass
{
public:
    // Default constructor.
    SymbolDefPass() = default;

    // Creates a scope tree and defines symbols based on the AST nodes.
    ScopeNode * CreateScopeTree(ast::Node * node);

private:
    // Visits nodes to create scopes and define symbols.
    void Visit(ast::Node * node);

    // Visits node's children.
    void VisitChildren(ast::Node * node);

    void VisitVariableDeclaration(ast::NodeVarDeclaration * node);

    void VisitFunctionDeclaration(ast::NodeFuncDeclaration * node);

    void VisitForStatement(ast::NodeForStatement * node);

    void VisitBlock(ast::NodeBlock * node);

    void VisitFunctionCall(ast::NodeFuncCall * node);

    void VisitLiteral(ast::NodeLiteral * node);

private:
    // Stores the current scope.
    ScopeNode *  m_currentScope{nullptr};
};

}

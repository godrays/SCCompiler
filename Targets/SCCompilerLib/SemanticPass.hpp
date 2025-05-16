//
//  Created by Arkin Terli on 4/16/18.
//  Copyright © 2018-Present, Arkin Terli. All rights reserved.
//

#pragma once

// Project includes
#include "AST.hpp"
#include "Types.hpp"
// External includes
// System includes


namespace scc
{

// Forward declaration.
namespace ast
{
    class Node;
    class NodeProgram;
    class NodeVarDeclaration;
    class NodeFuncDeclaration;
    class NodeBlock;
    class NodeIfStatement;
    class NodeForStatement;
    class NodeFor;
    class NodeWhileStatement;
    class NodeDoWhileStatement;
    class NodeReturnStatement;
    class NodeContinue;
    class NodeBreak;
    class NodeLogicalOP;
    class NodeFuncCall;
    class NodeAssignment;
    class NodeAOP;
    class NodeLiteral;
    class NodeExplicitTypeConversion;
    class NodeUnaryOP;
}


class  SemanticPass
{
public:
    // Perform semantic analysis.
    void SemanticCheck(ast::Node * node);

private:
    // Visits all node children.
    void visitChildren(ast::Node * node);

    // visit nodes to create scopes and define symbols.
    Type visit(ast::Node * node);

    void visitProgram(ast::NodeProgram * node);

    void visitVariableDeclaration(ast::NodeVarDeclaration * node);

    void visitFunctionDeclaration(ast::NodeFuncDeclaration * node);

    void visitBlock(ast::NodeBlock * node);

    void visitIfStatement(ast::NodeIfStatement * node);

    void visitForStatement(ast::NodeForStatement * node);

    void visitWhileStatement(ast::NodeWhileStatement * node);

    void visitDoWhileStatement(ast::NodeDoWhileStatement * node);

    void visitReturnStatement(ast::NodeReturnStatement * node);

    void visitContinue(ast::NodeContinue * node);

    void visitBreak(ast::NodeBreak * node);

    Type visitFunctionCall(ast::NodeFuncCall * node);

    Type visitAssignment(ast::NodeAssignment * node);

    Type visitExplicitTypeConversion(ast::NodeExplicitTypeConversion * node);

    Type visitLogicalOP(ast::NodeLogicalOP * node);

    Type visitPrefixAOP(ast::NodePrefixAOP * node);

    Type visitAOP(ast::NodeAOP * node);

    Type visitNodeUnaryOP(ast::NodeUnaryOP * node);

    Type visitLiteral(ast::NodeLiteral * node);

    Type visitCompOP(ast::NodeCompOP * node);
};

}

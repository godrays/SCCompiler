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
    class NodeVariableDeclaration;
    class NodeFunctionDeclaration;
    class NodeBlock;
    class NodeIfStatement;
    class NodeForStatement;
    class NodeFor;
    class NodeWhileStatement;
    class NodeDoWhileStatement;
    class NodeReturnStatement;
    class NodeContinue;
    class NodeBreak;
    class NodeLogicalOperator;
    class NodeFunctionCall;
    class NodeAssignment;
    class NodeArithmeticOperator;
    class NodeLiteral;
    class NodeExplicitTypeConversion;
    class NodeUnaryOperator;
}


class  SemanticPass
{
public:
    // Perform semantic analysis.
    void semanticCheck(ast::Node * node);

private:
    // Visits all node children.
    void visitChildren(ast::Node * node);

    // visit nodes to create scopes and define symbols.
    Type visit(ast::Node * node);

    void visitProgram(ast::NodeProgram * node);

    void visitVariableDeclaration(ast::NodeVariableDeclaration * node);

    void visitFunctionDeclaration(ast::NodeFunctionDeclaration * node);

    void visitBlock(ast::NodeBlock * node);

    void visitIfStatement(ast::NodeIfStatement * node);

    void visitForStatement(ast::NodeForStatement * node);

    void visitWhileStatement(ast::NodeWhileStatement * node);

    void visitDoWhileStatement(ast::NodeDoWhileStatement * node);

    void visitReturnStatement(ast::NodeReturnStatement * node);

    void visitContinue(ast::NodeContinue * node);

    void visitBreak(ast::NodeBreak * node);

    Type visitFunctionCall(ast::NodeFunctionCall * node);

    Type visitAssignment(ast::NodeAssignment * node);

    Type visitExplicitTypeConversion(ast::NodeExplicitTypeConversion * node);

    Type visitLogicalOperator(ast::NodeLogicalOperator * node);

    Type visitPrefixArithmeticOperator(ast::NodePrefixArithmeticOperator * node);

    Type visitArithmeticOperator(ast::NodeArithmeticOperator * node);

    Type visitUnaryOperator(ast::NodeUnaryOperator * node);

    Type visitLiteral(ast::NodeLiteral * node);

    Type visitComparisonOperator(ast::NodeComparisonOperator * node);
};

}

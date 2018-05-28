//
//  SemanticPass.hpp
//
//  Created by Arkin Terli on 4/16/18.
//  Copyright © 2018 Arkin Terli. All rights reserved.
//


#pragma once

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
        class NodeFuncCall;
        class NodeAssignment;
        class NodeAOP;
        class NodeLiteral;
        class NodeExplicitTypeConversion;
        class NodeUnaryOP;
    }


    #pragma mark - Class SemanticPass

    class  SemanticPass
    {
    public:
        // Perform semantic analysis on nodes AST.
        void SemanticCheck(ast::Node * node);

    private:
        // Visits all node childs.
        void VisitChilds(ast::Node * node);

        // Visits nodes to create scopes and define symbols.
        Type Visit(ast::Node * node);

        void VisitProgram(ast::NodeProgram * node);

        void VisitVariableDeclaration(ast::NodeVarDeclaration * node);

        void VisitFunctionDeclaration(ast::NodeFuncDeclaration * node);

        void VisitBlock(ast::NodeBlock * node);

        void VisitIfStatement(ast::NodeIfStatement * node);

        void VisitForStatement(ast::NodeForStatement * node);

        void VisitWhileStatement(ast::NodeWhileStatement * node);

        void VisitDoWhileStatement(ast::NodeDoWhileStatement * node);

        void VisitReturnStatement(ast::NodeReturnStatement * node);

        void VisitContinue(ast::NodeContinue * node);

        void VisitBreak(ast::NodeBreak * node);

        Type VisitFunctionCall(ast::NodeFuncCall * node);
        
        Type VisitAssignment(ast::NodeAssignment * node);

        Type VisitExplicitTypeConversion(ast::NodeExplicitTypeConversion * node);

        Type VisitLogicalNotOP(ast::NodeLogicalNotOP * node);

        Type VisitAOP(ast::NodeAOP * node);

        Type VisitNodeUnaryOP(ast::NodeUnaryOP * node);

        Type VisitLiteral(ast::NodeLiteral * node);

        Type VisitCompOP(ast::NodeCompOP * node);
   };

}

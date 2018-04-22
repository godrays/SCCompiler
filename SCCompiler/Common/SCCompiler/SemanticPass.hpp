//
//  SemanticPass.hpp
//
//  Created by Arkin Terli on 4/16/18.
//  Copyright © 2018 Arkin Terli. All rights reserved.
//


#pragma once

namespace SCCompiler
{
    // Forward declaration.
    namespace AST
    {
        class Node;
        class NodeProgram;
        class NodeVarDeclaration;
        class NodeFuncDeclaration;
        class NodeBlock;
        class NodeReturnStatement;
        class NodeFuncCall;
        class NodeAssignment;
        class NodeAOP;
        class NodeLiteral;
    }

    #pragma mark - Class SemanticPass

    class  SemanticPass
    {
    public:
        // Perform semantic analysis on nodes AST.
        void SemanticCheck(AST::Node * node);

    private:
        // Visits all node childs.
        void VisitChilds(AST::Node * node);

        // Visits nodes to create scopes and define symbols.
        Type Visit(AST::Node * node);

        void VisitProgram(AST::NodeProgram * node);

        void VisitVariableDeclaration(AST::NodeVarDeclaration * node);

        void VisitFunctionDeclaration(AST::NodeFuncDeclaration * node);

        void VisitBlock(AST::NodeBlock * node);

        void VisitReturnStatement(AST::NodeReturnStatement * node);

        Type VisitFunctionCall(AST::NodeFuncCall * node);
        
        Type VisitAssignment(AST::NodeAssignment * node);

        Type VisitAOP(AST::NodeAOP * node);

        Type VisitLiteral(AST::NodeLiteral * node);
   };

}

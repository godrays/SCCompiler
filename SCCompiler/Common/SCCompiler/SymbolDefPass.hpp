//
//  SymbolDefPass.hpp
//
//  Created by Arkin Terli on 4/15/18.
//  Copyright © 2018 Arkin Terli. All rights reserved.
//

#pragma once


namespace SCCompiler
{
    // Fordward declaration.
    class ScopeNode;

    // Fordward declaration.
    namespace AST
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
        // Creates a scope tree and defines symbols based on the AST nodes.
        ScopeNode * CreateScopeTree(AST::Node * node);

    private:
        // Visits nodes to create scopes and define symbols.
        void Visit(AST::Node * node);

        // Visits node childs.
        void VisitChilds(AST::Node * node);
        
        void VisitVariableDeclaration(AST::NodeVarDeclaration * node);

        void VisitFunctionDeclaration(AST::NodeFuncDeclaration * node);

        void VisitBlock(AST::NodeBlock * node);

    private:
        // Stores current scope.
        ScopeNode *  m_currentScope;
    };

}

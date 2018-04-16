//
//  SymbolDefPass.hpp
//
//  Created by Arkin Terli on 4/15/18.
//  Copyright © 2018 Arkin Terli. All rights reserved.
//

#pragma once

#include "AST.hpp"


namespace SCCompiler
{
    
    class ScopeNode;
    
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

    private:
        ScopeNode *  m_currentScope;
    };
    
}

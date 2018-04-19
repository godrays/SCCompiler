//
//  SemanticPass.cpp
//
//  Created by Arkin Terli on 4/16/18.
//  Copyright © 2018 Arkin Terli. All rights reserved.
//

#include <cassert>
#include <sstream>

#include "Symbols.hpp"
#include "SemanticPass.hpp"
#include "Exceptions.hpp"

using namespace SCCompiler;


#pragma mark - SemanticPass Implementations.


void SemanticPass::SemanticCheck(AST::Node * node)
{
    // Do symbol resolution, type checking, type promotion and validation.
    // Anything about the code which may not makes sense should be caught in this pass.
    // No error should be left to code geneartion pass.
    
    // Semantic Analysis Process In Visit Methods:
    // 1. Resolve symbol names. (Means check if var, func etc.. names are defined).
    // 2. Check do type promotion and check type equivalence.
    // 3. Do semantic validation.

    Visit(node);
}


void SemanticPass::VisitChilds(AST::Node * node)
{
    // Visit node children.
    for (size_t index=0; index<node->ChildCount(); ++index)
    {
        Visit(node->GetChild(index));
    }
}


Type SemanticPass::Visit(AST::Node * node)
{
    switch(node->GetNodeType())
    {
        case AST::NodeType::tNodeTypeProgram:
            VisitProgram(dynamic_cast<AST::NodeProgram *>(node));
            break;

        case AST::NodeType::tNodeTypeVariableDeclaration:
            VisitVariableDeclaration(dynamic_cast<AST::NodeVarDeclaration *>(node));
            break;

        case AST::NodeType::tNodeTypeFunctionDeclaration:
            VisitFunctionDeclaration(dynamic_cast<AST::NodeFuncDeclaration *>(node));
            break;

        case AST::NodeType::tNodeTypeBlock:
            VisitBlock(dynamic_cast<AST::NodeBlock *>(node));
            break;

        case AST::NodeType::tNodeTypeReturnStatement:
            VisitReturnStatement(dynamic_cast<AST::NodeReturnStatement *>(node));
            break;

        case AST::NodeType::tNodeTypeFuncCall:
            VisitFunctionCall(dynamic_cast<AST::NodeFuncCall *>(node));
            break;

        case AST::NodeType::tNodeTypeAssignment:
            VisitAssignment(dynamic_cast<AST::NodeAssignment *>(node));
            break;

        case AST::NodeType::tNodeTypeAOPMul:
        case AST::NodeType::tNodeTypeAOPDiv:
        case AST::NodeType::tNodeTypeAOPAdd:
        case AST::NodeType::tNodeTypeAOPSub:
            return VisitAOP(dynamic_cast<AST::NodeAOP *>(node));
            break;

        case AST::NodeType::tNodeTypeLiteralFloat:
        case AST::NodeType::tNodeTypeLiteralInt32:
        case AST::NodeType::tNodeTypeLiteralBool:
        case AST::NodeType::tNodeTypeLiteralID:
            return VisitLiteral(dynamic_cast<AST::NodeLiteral *>(node));
            break;

        default:
            assert(false && "Unknown node type in SemanticPass.");
            break;
    }

    return Type::tTypeUnknown;
}


void SemanticPass::VisitProgram(AST::NodeProgram * node)
{
    // Visit childs
    VisitChilds(node);
}


void SemanticPass::VisitVariableDeclaration(AST::NodeVarDeclaration * node)
{
    // Visit childs
    VisitChilds(node);
}


void SemanticPass::VisitFunctionDeclaration(AST::NodeFuncDeclaration * node)
{
    // Visit childs
    VisitChilds(node);
}


void SemanticPass::VisitBlock(AST::NodeBlock * node)
{
    // Visit childs
    VisitChilds(node);
}


void SemanticPass::VisitReturnStatement(AST::NodeReturnStatement * node)
{
    // Visit childs
    VisitChilds(node);
}


void SemanticPass::VisitFunctionCall(AST::NodeFuncCall * node)
{
    // Visit childs
    VisitChilds(node);
}


void SemanticPass::VisitAssignment(AST::NodeAssignment * node)
{
    // Visit childs
    VisitChilds(node);
}


Type SemanticPass::VisitAOP(AST::NodeAOP * node)
{
    // Arithmetic operation requires at least two operand.
    // Node must have two child nodes.
    assert(node->ChildCount() == 2);

    // Type Check
    auto leftOperandType = Visit(node->GetChild(0));
    auto rightOperandType = Visit(node->GetChild(1));
    auto promotedType = TypeChecker::Promote(leftOperandType, rightOperandType);
    
    if (leftOperandType != rightOperandType && promotedType == Type::tTypeUnknown)
    {
        std::stringstream   message;
        message << "Arithmetic operation type mismatch at line: " << node->GetSourceCodeLine() << std::endl;
        throw SemanticErrorException( message.str());
    }

    return promotedType;
}


Type SemanticPass::VisitLiteral(AST::NodeLiteral * node)
{
    Type literalType = Type::tTypeUnknown;
    
    switch (node->GetNodeType())
    {
        case AST::NodeType::tNodeTypeLiteralFloat:
        literalType = Type::tTypeFloat;
        break;
        
        case AST::NodeType::tNodeTypeLiteralInt32:
        literalType = Type::tTypeInt;
        break;
        
        case AST::NodeType::tNodeTypeLiteralBool:
        literalType = Type::tTypeBool;
        break;
        
        case AST::NodeType::tNodeTypeLiteralID:
        {
            // Resolve variable name. It has to be defined before it's used.
            auto scope = node->GetScope();
            auto symbol = scope->ResolveSymbol(node->GetValue());
            if (!symbol)
            {
                throw SemanticErrorException("Use of undeclared identifier: " + node->GetValue());
            }
            literalType = symbol->GetType();
        }
        break;
        
        default:
            assert(false && "Unknown node type in SemanticPass::VisitLiteral");
        break;
    }

    // This node should have no children.
    assert(node->ChildCount() == 0);

    // Return type of literal then parent node can do type check if necessary.
    return literalType;
}

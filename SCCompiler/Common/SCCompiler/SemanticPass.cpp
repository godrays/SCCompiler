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
            return VisitFunctionCall(dynamic_cast<AST::NodeFuncCall *>(node));
            break;

        case AST::NodeType::tNodeTypeAssignment:
            return VisitAssignment(dynamic_cast<AST::NodeAssignment *>(node));
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
    auto funcReturnType = node->GetReturnType();

    // Function return type can't be unknown.
    assert(funcReturnType != Type::tTypeUnknown);

    // Rule: Function must have at least one return statement if it returns a value.
    if (funcReturnType != Type::tTypeVoid)
    {
        // This search could be done faster by marking function declaration nodes when
        // visiting return statement nodes. Must keep AST nodes as simple as possible.
        if (node->FindClosestChildNode(AST::NodeType::tNodeTypeReturnStatement) == nullptr)
        {
            std::stringstream   message;
            message << "Line: " << node->GetSourceCodeLine() << " - " << node->GetFuncName()
                    << " must have at least one return statement." << std::endl;
            throw SemanticErrorException(message.str());
        }
    }

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
    assert(node->ChildCount() < 2);

    // Find belonging function declaration parent node.
    auto funcDeclNode = dynamic_cast<AST::NodeFuncDeclaration *>(node->FindClosestParentNode(AST::NodeType::tNodeTypeFunctionDeclaration));
    assert(funcDeclNode != nullptr);

    auto scope = funcDeclNode->GetScope();
    auto funcSymbol = scope->ResolveSymbol(funcDeclNode->GetFuncName());
    
    // Rule: Void function should not return a value.
    if (funcSymbol->GetType() == Type::tTypeVoid && node->ChildCount() == 1)
    {
        std::stringstream   message;
        message << "Line: " << node->GetSourceCodeLine() << " - Void function "
                << funcSymbol->GetName() << " shoud not return a value." << std::endl;
        throw SemanticErrorException(message.str());
    }
    else
    // Rule: Non-Void function should return a value.
    if (funcSymbol->GetType() != Type::tTypeVoid && node->ChildCount() == 0)
    {
        std::stringstream   message;
        message << "Line: " << node->GetSourceCodeLine() << " - Non-void function "
                << funcSymbol->GetName() << " shoud return a value." << std::endl;
        throw SemanticErrorException(message.str());
    }
    
    // Rule: Return value type should match function return type.
    if (node->ChildCount() == 1)
    {
        auto returnExpr = node->GetChild(0);
        auto returnExprType = Visit(returnExpr);

        if (funcSymbol->GetType() != returnExprType)
        {
            std::stringstream   message;
            message << "Line: " << returnExpr->GetSourceCodeLine() << " - Return value type does not match "
                    << funcSymbol->GetName() << " return type." << std::endl;
            throw SemanticErrorException(message.str());
        }
    }
}


Type SemanticPass::VisitFunctionCall(AST::NodeFuncCall * node)
{
    // Rule: Function name must resolve (must defined).
    auto scope = node->GetScope();
    auto symbol = static_cast<FunctionSymbol *>(scope->ResolveSymbol(node->GetFuncName()));
    if (!symbol)
    {
        std::stringstream   message;
        message << "Line: " << node->GetSourceCodeLine() << " - Use of undeclared identifier: " << node->GetFuncName() << std::endl;
        throw SemanticErrorException(message.str());
    }
    auto funcReturnType = symbol->GetType();

    // Each node child is one parameter of function call.
    // Rule: Number of parameters declared and number of parameters used must match.
    if (node->ChildCount() != symbol->ArgumentCount())
    {
        std::stringstream   message;
        message << "Line: " << node->GetSourceCodeLine() << " - No matching function to call: " << node->GetFuncName() << std::endl;
        throw SemanticErrorException(message.str());
    }

    // Rule: Function argument type must match with the expression (parameter) type.
    //       All parameters passed to a function are expressions.
    for (size_t index=0; index < node->ChildCount(); ++index)
    {
        // Parameter passed to function.
        auto paramExprType = Visit(node->GetChild(index));
        // Function argument is declared when func is declaration.
        auto argumentType = symbol->GetArgumentSymbol(index)->GetType();

        if (paramExprType != argumentType)
        {
            std::stringstream   message;
            message << "Line: " << node->GetSourceCodeLine() << " - No matching function to call: " << node->GetFuncName() << std::endl;
            throw SemanticErrorException( message.str());
        }
    }

    return funcReturnType;
}


Type SemanticPass::VisitAssignment(AST::NodeAssignment * node)
{
    // Rule: Assignment operation requires two operands.
    // Node must have two child nodes.
    assert(node->ChildCount() == 2);

    // Rule: Left and right expression type must match.
    auto leftOperandType = Visit(node->GetChild(0));
    auto rightOperandType = Visit(node->GetChild(1));
    
    if (leftOperandType != rightOperandType)
    {
        std::stringstream   message;
        message << "Line: " << node->GetSourceCodeLine() << " - Assignment type mismatch." << std::endl;
        throw SemanticErrorException( message.str());
    }

    return leftOperandType;
}


Type SemanticPass::VisitAOP(AST::NodeAOP * node)
{
    // Rule: Arithmetic operation requires two operands.
    // Node must have two child nodes.
    assert(node->ChildCount() == 2);

    // Rule: Left and right expression type must match.
    auto leftOperandType = Visit(node->GetChild(0));
    auto rightOperandType = Visit(node->GetChild(1));
    auto promotedType = TypeChecker::Promote(leftOperandType, rightOperandType);
    
    if (leftOperandType != rightOperandType && promotedType == Type::tTypeUnknown)
    {
        std::stringstream   message;
        message << "Line: " << node->GetSourceCodeLine() << " - Arithmetic operation type mismatch." << std::endl;
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
            // Rule: Resolve variable name. It has to be defined before it's used.
            auto scope = node->GetScope();
            auto symbol = scope->ResolveSymbol(node->GetValue());
            if (!symbol)
            {
                std::stringstream   message;
                message << "Line: " << node->GetSourceCodeLine() << " - Use of undeclared identifier: " << node->GetValue() << std::endl;
                throw SemanticErrorException(message.str());
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

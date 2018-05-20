//
//  SemanticPass.cpp
//
//  Created by Arkin Terli on 4/16/18.
//  Copyright © 2018 Arkin Terli. All rights reserved.
//

#include <cassert>
#include <sstream>

#include "Symbols.hpp"
#include "AST.hpp"
#include "SemanticPass.hpp"
#include "Exceptions.hpp"

using namespace scc;


#pragma mark - SemanticPass Implementations.

void SemanticPass::SemanticCheck(ast::Node * node)
{
    // Do symbol resolution, type checking, type promotion and validation.
    // Anything about the code which may not makes sense should be caught in this pass.
    // No error should be left to code geneartion pass.
    
    // Semantic Analysis Process In Visit Methods:
    // 1. Check do type promotion and check type equivalence.
    // 2. Do semantic validation.

    Visit(node);
}


void SemanticPass::VisitChilds(ast::Node * node)
{
    // Visit node children.
    for (size_t index=0; index<node->ChildCount(); ++index)
    {
        Visit(node->GetChild(index));
    }
}


Type SemanticPass::Visit(ast::Node * node)
{
    switch(node->GetNodeType())
    {
        case ast::NodeType::kNodeTypeProgram:
            VisitProgram(dynamic_cast<ast::NodeProgram *>(node));
            break;

        case ast::NodeType::kNodeTypeVariableDeclaration:
            VisitVariableDeclaration(dynamic_cast<ast::NodeVarDeclaration *>(node));
            break;

        case ast::NodeType::kNodeTypeFunctionDeclaration:
            VisitFunctionDeclaration(dynamic_cast<ast::NodeFuncDeclaration *>(node));
            break;

        case ast::NodeType::kNodeTypeBlock:
            VisitBlock(dynamic_cast<ast::NodeBlock *>(node));
            break;

        case ast::NodeType::kNodeTypeReturnStatement:
            VisitReturnStatement(dynamic_cast<ast::NodeReturnStatement *>(node));
            break;

        case ast::NodeType::kNodeTypeFuncCall:
            return VisitFunctionCall(dynamic_cast<ast::NodeFuncCall *>(node));
            break;

        case ast::NodeType::kNodeTypeAssignment:
            return VisitAssignment(dynamic_cast<ast::NodeAssignment *>(node));
            break;

        case ast::NodeType::kNodeTypeAOPMul:
        case ast::NodeType::kNodeTypeAOPDiv:
        case ast::NodeType::kNodeTypeAOPAdd:
        case ast::NodeType::kNodeTypeAOPSub:
            return VisitAOP(dynamic_cast<ast::NodeAOP *>(node));
            break;

        case ast::NodeType::kNodeTypeLiteralFloat:
        case ast::NodeType::kNodeTypeLiteralInt32:
        case ast::NodeType::kNodeTypeLiteralBool:
        case ast::NodeType::kNodeTypeLiteralID:
            return VisitLiteral(dynamic_cast<ast::NodeLiteral *>(node));
            break;

        default:
            assert(false && "Unknown node type in SemanticPass.");
            break;
    }

    return Type::kTypeUnknown;
}


void SemanticPass::VisitProgram(ast::NodeProgram * node)
{
    // Visit childs
    VisitChilds(node);
}


void SemanticPass::VisitVariableDeclaration(ast::NodeVarDeclaration * node)
{
    auto childCount = node->ChildCount();

    assert(childCount < 2);

    // Rule: If variable is initialized then variable type and right expression type must match.
    if (childCount == 1)
    {
        // Rule: right expression (initializer) type must match.
        auto rightExprType = Visit(node->GetChild(0));
        
        if (node->GetVarType() != rightExprType)
        {
            std::stringstream   message;
            message << "Line: " << node->GetChild(0)->GetSourceCodeLine() << " - Assignment type mismatch." << std::endl;
            throw SemanticErrorException(message.str());
        }

        return;
    }

    // Otherwise, just visit childs.
    VisitChilds(node);
}


void SemanticPass::VisitFunctionDeclaration(ast::NodeFuncDeclaration * node)
{
    auto funcReturnType = node->GetReturnType();

    // Function return type can't be unknown.
    assert(funcReturnType != Type::kTypeUnknown);

    // Rule: Function must have at least one return statement if it returns a value.
    if (funcReturnType != Type::kTypeVoid)
    {
        // This search could be done faster by marking function declaration nodes when
        // visiting return statement nodes. Must keep AST nodes as simple as possible.
        if (node->FindClosestChildNode(ast::NodeType::kNodeTypeReturnStatement) == nullptr)
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


void SemanticPass::VisitBlock(ast::NodeBlock * node)
{
    // Visit childs
    VisitChilds(node);
}


void SemanticPass::VisitReturnStatement(ast::NodeReturnStatement * node)
{
    assert(node->ChildCount() < 2);

    // Find belonging function declaration parent node.
    auto funcDeclNode = dynamic_cast<ast::NodeFuncDeclaration *>(node->FindClosestParentNode(ast::NodeType::kNodeTypeFunctionDeclaration));
    assert(funcDeclNode != nullptr);

    auto scope = funcDeclNode->GetScope();
    auto funcSymbol = scope->ResolveSymbol(funcDeclNode->GetFuncName());
    
    // Rule: Void function should not return a value.
    if (funcSymbol->GetType() == Type::kTypeVoid && node->ChildCount() == 1)
    {
        std::stringstream   message;
        message << "Line: " << node->GetSourceCodeLine() << " - Void function "
                << funcSymbol->GetName() << " shoud not return a value." << std::endl;
        throw SemanticErrorException(message.str());
    }
    else
    // Rule: Non-Void function should return a value.
    if (funcSymbol->GetType() != Type::kTypeVoid && node->ChildCount() == 0)
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


Type SemanticPass::VisitFunctionCall(ast::NodeFuncCall * node)
{
    auto scope = node->GetScope();
    auto symbol = static_cast<FunctionSymbol *>(scope->ResolveSymbol(node->GetFuncName()));
    assert(symbol && "Use of undeclared identifier.");
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


Type SemanticPass::VisitAssignment(ast::NodeAssignment * node)
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


Type SemanticPass::VisitAOP(ast::NodeAOP * node)
{
    // Rule: Arithmetic operation requires two operands.
    // Node must have two child nodes.
    assert(node->ChildCount() == 2);

    // Rule: Left and right expression type must match.
    auto leftOperandType = Visit(node->GetChild(0));
    auto rightOperandType = Visit(node->GetChild(1));
    auto promotedType = TypeChecker::Promote(leftOperandType, rightOperandType);
    
    if (leftOperandType != rightOperandType && promotedType == Type::kTypeUnknown)
    {
        std::stringstream   message;
        message << "Line: " << node->GetSourceCodeLine() << " - Arithmetic operation type mismatch." << std::endl;
        throw SemanticErrorException( message.str());
    }

    return promotedType;
}


Type SemanticPass::VisitLiteral(ast::NodeLiteral * node)
{
    Type literalType = Type::kTypeUnknown;
    
    switch (node->GetNodeType())
    {
        case ast::NodeType::kNodeTypeLiteralFloat:
        literalType = Type::kTypeFloat;
        break;
        
        case ast::NodeType::kNodeTypeLiteralInt32:
        literalType = Type::kTypeInt;
        break;
        
        case ast::NodeType::kNodeTypeLiteralBool:
        literalType = Type::kTypeBool;
        break;
        
        case ast::NodeType::kNodeTypeLiteralID:
        {
            // Rule: Resolve variable name. It has to be defined before it's used.
            auto scope = node->GetScope();
            auto symbol = scope->ResolveSymbol(node->GetValue());
            assert(symbol && "Use of undeclared identifier");
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

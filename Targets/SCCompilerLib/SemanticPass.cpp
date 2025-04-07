//
//  Created by Arkin Terli on 4/16/18.
//  Copyright © 2018-Present, Arkin Terli. All rights reserved.
//

// Project includes
#include "SemanticPass.hpp"
#include "AST.hpp"
#include "Exceptions.hpp"
#include "Symbols.hpp"
#include "Utils.hpp"
// External includes
// System includes
#include <cassert>


using namespace scc;


void SemanticPass::SemanticCheck(ast::Node * node)
{
    // Do symbol resolution, type checking, type promotion and validation.
    // Anything about the code which may not make sense should be caught in this pass.
    // No errors should be left for the code generation pass.

    // Semantic Analysis Process In Visit Methods:
    // 1. Check, do type promotion, and check type equivalence.
    // 2. Do semantic validation.

    Visit(node);
}


void SemanticPass::VisitChildren(ast::Node * node)
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

        case ast::NodeType::kNodeTypeIfStatement:
            VisitIfStatement(dynamic_cast<ast::NodeIfStatement *>(node));
            break;

        case ast::NodeType::kNodeTypeForStatement:
            VisitForStatement(dynamic_cast<ast::NodeForStatement *>(node));
            break;

        case ast::NodeType::kNodeTypeForVarDecl:
        case ast::NodeType::kNodeTypeForCondition:
        case ast::NodeType::kNodeTypeForIncrement:
            // These are just sub-statement / grouping nodes. Nothing to do with them.
            VisitChildren(node);
            break;

        case ast::NodeType::kNodeTypeWhileStatement:
            VisitWhileStatement(dynamic_cast<ast::NodeWhileStatement *>(node));
            break;

        case ast::NodeType::kNodeTypeDoWhileStatement:
            VisitDoWhileStatement(dynamic_cast<ast::NodeDoWhileStatement *>(node));
            break;

        case ast::NodeType::kNodeTypeReturnStatement:
            VisitReturnStatement(dynamic_cast<ast::NodeReturnStatement *>(node));
            break;

        case ast::NodeType::kNodeTypeContinue:
            VisitContinue(dynamic_cast<ast::NodeContinue *>(node));
            break;

        case ast::NodeType::kNodeTypeBreak:
            VisitBreak(dynamic_cast<ast::NodeBreak *>(node));
            break;

        case ast::NodeType::kNodeTypeFuncCall:
            return VisitFunctionCall(dynamic_cast<ast::NodeFuncCall *>(node));
            break;

        case ast::NodeType::kNodeTypeAssignment:
            return VisitAssignment(dynamic_cast<ast::NodeAssignment *>(node));
            break;

        case ast::NodeType::kNodeTypeExplicitTypeConversion:
            return VisitExplicitTypeConversion(dynamic_cast<ast::NodeExplicitTypeConversion *>(node));
            break;

        case ast::NodeType::kNodeTypeLogicalNotOP:
        case ast::NodeType::kNodeTypeLogicalAndOP:
        case ast::NodeType::kNodeTypeLogicalOrOP:
            return VisitLogicalOP(dynamic_cast<ast::NodeLogicalOP *>(node));
            break;

        case ast::NodeType::kNodeTypeCompOPEQ:
        case ast::NodeType::kNodeTypeCompOPNEQ:
        case ast::NodeType::kNodeTypeCompOPLE:
        case ast::NodeType::kNodeTypeCompOPGE:
        case ast::NodeType::kNodeTypeCompOPL:
        case ast::NodeType::kNodeTypeCompOPG:
            return VisitCompOP(dynamic_cast<ast::NodeCompOP *>(node));
            break;

        case ast::NodeType::kNodeTypePrefixIncAOP:
        case ast::NodeType::kNodeTypePrefixDecAOP:
            return VisitPrefixAOP(dynamic_cast<ast::NodePrefixAOP *>(node));
            break;

        case ast::NodeType::kNodeTypeAOPMul:
        case ast::NodeType::kNodeTypeAOPDiv:
        case ast::NodeType::kNodeTypeAOPAdd:
        case ast::NodeType::kNodeTypeAOPSub:
            return VisitAOP(dynamic_cast<ast::NodeAOP *>(node));
            break;

        case ast::NodeType::kNodeTypeUOPPlus:
        case ast::NodeType::kNodeTypeUOPMinus:
            return VisitNodeUnaryOP(dynamic_cast<ast::NodeUnaryOP *>(node));
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
    VisitChildren(node);
}


void SemanticPass::VisitVariableDeclaration(ast::NodeVarDeclaration * node)
{
    auto childCount = node->ChildCount();

    assert(childCount < 2);

    // Rule: If a variable is initialized, then the variable type and right expression type must match.
    if (childCount == 1)
    {
        // Rule: The right expression (initializer) type must match.
        auto rightExprType = Visit(node->GetChild(0));

        throw_if(node->GetVarType() != rightExprType,
                 SemanticErrorException("Line: ", node->GetChild(0)->GetSourceCodeLine(), " - Assignment type mismatch."));

        return;
    }

    VisitChildren(node);
}


void SemanticPass::VisitFunctionDeclaration(ast::NodeFuncDeclaration * node)
{
    auto funcReturnType = node->GetReturnType();

    // A function's return type can't be unknown.
    assert(funcReturnType != Type::kTypeUnknown);

    // Rule: A function must have at least one return statement if it returns a value.
    if (funcReturnType != Type::kTypeVoid)
    {
        // This search could be done faster by marking function declaration nodes when
        // visiting return statement nodes. AST nodes must be kept as simple as possible.
        throw_if(node->FindClosestChildNode(ast::NodeType::kNodeTypeReturnStatement) == nullptr,
                 SemanticErrorException("Line: ", node->GetSourceCodeLine(), " - ", node->GetFuncName(),
                                        " must have at least one return statement."));
    }

    VisitChildren(node);
}


void SemanticPass::VisitBlock(ast::NodeBlock * node)
{
    VisitChildren(node);
}


void SemanticPass::VisitIfStatement(ast::NodeIfStatement * node)
{
    // Requires a maximum of three children: ConditionExpr, Then Statement, Else Statement
    assert(node->ChildCount() < 4);
    VisitChildren(node);
}


void SemanticPass::VisitForStatement(ast::NodeForStatement * node)
{
    // There must be a forVarDec, ForCond, ForInc, and a Statement
    assert(node->ChildCount() == 4);

    auto forConditionNode = node->GetChild(1);
    throw_if(forConditionNode->ChildCount() > 0 && Visit(forConditionNode->GetChild(0)) != Type::kTypeBool,
             SemanticErrorException("Line: ", node->GetSourceCodeLine(), " - For comparison type mismatch."));

    VisitChildren(node);
}


void SemanticPass::VisitWhileStatement(ast::NodeWhileStatement * node)
{
    // There must be a condition expr and body.
    assert(node->ChildCount() == 2);

    auto conditionNode = node->GetChild(0);
    throw_if(Visit(conditionNode) != Type::kTypeBool,
             SemanticErrorException("Line: ", node->GetSourceCodeLine(), " - While comparison type mismatch."));

    // Visit the body statement children.
    auto bodyNode = node->GetChild(1);
    Visit(bodyNode);
}


void SemanticPass::VisitDoWhileStatement(ast::NodeDoWhileStatement * node)
{
    // There must be a condition expr and body.
    assert(node->ChildCount() == 2);

    auto conditionNode = node->GetChild(1);
    throw_if(Visit(conditionNode) != Type::kTypeBool,
             SemanticErrorException("Line: ", node->GetSourceCodeLine(), " - Do While comparison type mismatch."));

    // Visit the body statement children.
    auto bodyNode = node->GetChild(1);
    Visit(bodyNode);
}


void SemanticPass::VisitReturnStatement(ast::NodeReturnStatement * node)
{
    assert(node->ChildCount() < 2);

    // Find the belonging function declaration parent node.
    auto funcDeclNode = dynamic_cast<ast::NodeFuncDeclaration *>(node->FindClosestParentNode({ast::NodeType::kNodeTypeFunctionDeclaration}));
    assert(funcDeclNode != nullptr);

    auto scope = funcDeclNode->GetScope();
    auto funcSymbol = scope->ResolveSymbol(funcDeclNode->GetFuncName());

    // Rule: A void function should not return a value.
    throw_if(funcSymbol->GetType() == Type::kTypeVoid && node->ChildCount() == 1,
             SemanticErrorException("Line: ", node->GetSourceCodeLine(), " - Void function ", funcSymbol->GetName(),
                                    " should not return a value."));

    // Rule: A non-void function should return a value.
    throw_if(funcSymbol->GetType() != Type::kTypeVoid && node->ChildCount() == 0,
             SemanticErrorException("Line: ", node->GetSourceCodeLine(), " - Non-void function ", funcSymbol->GetName(),
                                    " should return a value."));

    // Rule: The return value type should match the function return type.
    if (node->ChildCount() == 1)
    {
        auto returnExpr = node->GetChild(0);
        auto returnExprType = Visit(returnExpr);

        throw_if(funcSymbol->GetType() != returnExprType,
                 SemanticErrorException("Line: ", returnExpr->GetSourceCodeLine(), " - Return value type does not match ",
                                        funcSymbol->GetName(), " return type."));
    }
}


void SemanticPass::VisitContinue(ast::NodeContinue * node)
{
    auto loopNode = node->FindClosestParentNode({ast::NodeType::kNodeTypeForStatement,
                                                 ast::NodeType::kNodeTypeWhileStatement});

    throw_if(loopNode == nullptr,
             SemanticErrorException("Line: ", node->GetSourceCodeLine(), " - The 'continue' statement is allowed only in loops."));

    assert(node->ChildCount() == 0 && "The continue statement node must have zero children!");
}


void SemanticPass::VisitBreak(ast::NodeBreak * node)
{
    auto loopNode = node->FindClosestParentNode({ast::NodeType::kNodeTypeForStatement,
                                                 ast::NodeType::kNodeTypeWhileStatement});

    throw_if(loopNode == nullptr,
             SemanticErrorException("Line: ", node->GetSourceCodeLine(), " - The 'break' statement is allowed only in loops."));

    assert(node->ChildCount() == 0 && "The break statement node must have zero children!");
}


Type SemanticPass::VisitFunctionCall(ast::NodeFuncCall * node)
{
    auto scope = node->GetScope();
    auto symbol = static_cast<FunctionSymbol *>(scope->ResolveSymbol(node->GetFuncName()));
    assert(symbol && "Use of an undeclared identifier.");
    auto funcReturnType = symbol->GetType();

    // Each node child is one parameter of the function call.
    // Rule: The number of parameters declared and the number of parameters used must match.
    throw_if(node->ChildCount() != symbol->ArgumentCount(),
             SemanticErrorException("Line: ", node->GetSourceCodeLine(), " - No matching function to call: ",
                                    node->GetFuncName()));

    // Rule: The function argument type must match the expression (parameter) type.
    //       All parameters passed to a function are expressions.
    for (size_t index=0; index < node->ChildCount(); ++index)
    {
        // Parameter passed to the function.
        auto paramExprType = Visit(node->GetChild(index));
        // The function argument is declared when the function is declared.
        auto argumentType = symbol->GetArgumentSymbol(index)->GetType();

        throw_if(paramExprType != argumentType,
                 SemanticErrorException("Line: ", node->GetSourceCodeLine(), " - No matching function to call: ",
                                        node->GetFuncName()));
    }

    return funcReturnType;
}


Type SemanticPass::VisitAssignment(ast::NodeAssignment * node)
{
    // Rule: An assignment operation requires two operands.
    // The node must have two child nodes.
    assert(node->ChildCount() == 2);

    // Rule: The left and right expression types must match.
    auto leftOperandType = Visit(node->GetChild(0));
    auto rightOperandType = Visit(node->GetChild(1));

    throw_if(leftOperandType != rightOperandType,
             SemanticErrorException("Line: ", node->GetSourceCodeLine(), " - Assignment type mismatch."));

    return leftOperandType;
}


Type SemanticPass::VisitExplicitTypeConversion(ast::NodeExplicitTypeConversion * node)
{
    Visit(node->GetChild(0));

    return node->GetConversionType();
}


Type SemanticPass::VisitLogicalOP(ast::NodeLogicalOP * node)
{
    auto nodeType = node->GetNodeType();

    // The Not Operator requires only a single expression, so it requires special treatment.
    if (nodeType == ast::NodeType::kNodeTypeLogicalNotOP)
    {
        assert(node->ChildCount() == 1);
        return Visit(node->GetChild(0));
    }

    // Handle the rest of the other types of operators which require left and right expressions.
    auto leftOperandType  = Visit(node->GetChild(0));
    auto rightOperandType = Visit(node->GetChild(1));

    throw_if (leftOperandType != rightOperandType,
              SemanticErrorException("Line: ", node->GetSourceCodeLine(), " - Logical operation type mismatch."));

    return leftOperandType;
}


Type SemanticPass::VisitPrefixAOP(ast::NodePrefixAOP * node)
{
    auto rightOperandType = Visit(node->GetChild(0));

    throw_if(node->GetChild(0)->GetNodeType() != ast::NodeType::kNodeTypeLiteralID,
             SemanticErrorException("Line: ", node->GetSourceCodeLine(), " - Prefix arithmetic operation is not allowed."));

    throw_if(rightOperandType != Type::kTypeFloat && rightOperandType != Type::kTypeInt,
             SemanticErrorException("Line: ", node->GetSourceCodeLine(), " - Arithmetic operation type mismatch."));

    return rightOperandType;
}


Type SemanticPass::VisitAOP(ast::NodeAOP * node)
{
    // Rule: An arithmetic operation requires two operands.
    // The node must have two child nodes.
    assert(node->ChildCount() == 2);

    // Rule: The left and right expression types must match.
    auto leftOperandType = Visit(node->GetChild(0));
    auto rightOperandType = Visit(node->GetChild(1));

    throw_if(leftOperandType != rightOperandType,
             SemanticErrorException("Line: ", node->GetSourceCodeLine(), " - Arithmetic operation type mismatch."));

    return leftOperandType;
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
                // Rule: Resolve the variable name. It has to be defined before it's used.
                auto scope = node->GetScope();
                auto symbol = scope->ResolveSymbol(node->GetValue());
                assert(symbol && "Use of an undeclared identifier");
                literalType = symbol->GetType();
            }
            break;

        default:
            assert(false && "Unknown node type in SemanticPass::VisitLiteral");
            break;
    }

    // This node should have no children.
    assert(node->ChildCount() == 0);

    // Return the type of literal so the parent node can perform a type check if necessary.
    return literalType;
}


Type SemanticPass::VisitNodeUnaryOP(ast::NodeUnaryOP * node)
{
    // The node must have one child node.
    assert(node->ChildCount() == 1);

    auto rightOperandType = Visit(node->GetChild(0));

    throw_if(rightOperandType != Type::kTypeFloat && rightOperandType != Type::kTypeInt,
             SemanticErrorException("Line: ", node->GetSourceCodeLine(), " - Unary operation type mismatch."));

    // Return the type of the right expr value.
    return rightOperandType;
}


Type SemanticPass::VisitCompOP(ast::NodeCompOP * node)
{
    // Rule: A comparison operation requires two operands.
    // The node must have two child nodes.
    assert(node->ChildCount() == 2);

    // Rule: The left and right expression types must match.
    auto leftOperandType = Visit(node->GetChild(0));
    auto rightOperandType = Visit(node->GetChild(1));

    throw_if(leftOperandType != rightOperandType,
             SemanticErrorException("Line: ", node->GetSourceCodeLine(), " - Comparison operation type mismatch."));

    // The comparison result type is always bool type.
    return Type::kTypeBool;
}

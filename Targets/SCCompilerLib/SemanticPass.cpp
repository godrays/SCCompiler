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

    // Semantic Analysis Process In visit Methods:
    // 1. Check, do type promotion, and check type equivalence.
    // 2. Do semantic validation.

    visit(node);
}


void SemanticPass::visitChildren(ast::Node * node)
{
    // visit node children.
    for (size_t index=0; index<node->childCount(); ++index)
    {
        visit(node->getChild(index));
    }
}


Type SemanticPass::visit(ast::Node * node)
{
    switch(node->getNodeType())
    {
        case ast::NodeType::kNodeTypeProgram:
            visitProgram(dynamic_cast<ast::NodeProgram *>(node));
            break;

        case ast::NodeType::kNodeTypeVariableDeclaration:
            visitVariableDeclaration(dynamic_cast<ast::NodeVarDeclaration *>(node));
            break;

        case ast::NodeType::kNodeTypeFunctionDeclaration:
            visitFunctionDeclaration(dynamic_cast<ast::NodeFuncDeclaration *>(node));
            break;

        case ast::NodeType::kNodeTypeBlock:
            visitBlock(dynamic_cast<ast::NodeBlock *>(node));
            break;

        case ast::NodeType::kNodeTypeIfStatement:
            visitIfStatement(dynamic_cast<ast::NodeIfStatement *>(node));
            break;

        case ast::NodeType::kNodeTypeForStatement:
            visitForStatement(dynamic_cast<ast::NodeForStatement *>(node));
            break;

        case ast::NodeType::kNodeTypeForVarDecl:
        case ast::NodeType::kNodeTypeForCondition:
        case ast::NodeType::kNodeTypeForIncrement:
            // These are just sub-statement / grouping nodes. Nothing to do with them.
            visitChildren(node);
            break;

        case ast::NodeType::kNodeTypeWhileStatement:
            visitWhileStatement(dynamic_cast<ast::NodeWhileStatement *>(node));
            break;

        case ast::NodeType::kNodeTypeDoWhileStatement:
            visitDoWhileStatement(dynamic_cast<ast::NodeDoWhileStatement *>(node));
            break;

        case ast::NodeType::kNodeTypeReturnStatement:
            visitReturnStatement(dynamic_cast<ast::NodeReturnStatement *>(node));
            break;

        case ast::NodeType::kNodeTypeContinue:
            visitContinue(dynamic_cast<ast::NodeContinue *>(node));
            break;

        case ast::NodeType::kNodeTypeBreak:
            visitBreak(dynamic_cast<ast::NodeBreak *>(node));
            break;

        case ast::NodeType::kNodeTypeFuncCall:
            return visitFunctionCall(dynamic_cast<ast::NodeFuncCall *>(node));
            break;

        case ast::NodeType::kNodeTypeAssignment:
            return visitAssignment(dynamic_cast<ast::NodeAssignment *>(node));
            break;

        case ast::NodeType::kNodeTypeExplicitTypeConversion:
            return visitExplicitTypeConversion(dynamic_cast<ast::NodeExplicitTypeConversion *>(node));
            break;

        case ast::NodeType::kNodeTypeLogicalNotOP:
        case ast::NodeType::kNodeTypeLogicalAndOP:
        case ast::NodeType::kNodeTypeLogicalOrOP:
            return visitLogicalOP(dynamic_cast<ast::NodeLogicalOP *>(node));
            break;

        case ast::NodeType::kNodeTypeCompOPEQ:
        case ast::NodeType::kNodeTypeCompOPNEQ:
        case ast::NodeType::kNodeTypeCompOPLE:
        case ast::NodeType::kNodeTypeCompOPGE:
        case ast::NodeType::kNodeTypeCompOPL:
        case ast::NodeType::kNodeTypeCompOPG:
            return visitCompOP(dynamic_cast<ast::NodeCompOP *>(node));
            break;

        case ast::NodeType::kNodeTypePrefixIncAOP:
        case ast::NodeType::kNodeTypePrefixDecAOP:
            return visitPrefixAOP(dynamic_cast<ast::NodePrefixAOP *>(node));
            break;

        case ast::NodeType::kNodeTypeAOPMul:
        case ast::NodeType::kNodeTypeAOPDiv:
        case ast::NodeType::kNodeTypeAOPAdd:
        case ast::NodeType::kNodeTypeAOPSub:
            return visitAOP(dynamic_cast<ast::NodeAOP *>(node));
            break;

        case ast::NodeType::kNodeTypeUOPPlus:
        case ast::NodeType::kNodeTypeUOPMinus:
            return visitNodeUnaryOP(dynamic_cast<ast::NodeUnaryOP *>(node));
            break;

        case ast::NodeType::kNodeTypeLiteralFloat:
        case ast::NodeType::kNodeTypeLiteralInt32:
        case ast::NodeType::kNodeTypeLiteralBool:
        case ast::NodeType::kNodeTypeLiteralID:
            return visitLiteral(dynamic_cast<ast::NodeLiteral *>(node));
            break;

        default:
            assert(false && "Unknown node type in SemanticPass.");
            break;
    }

    return Type::kTypeUnknown;
}


void SemanticPass::visitProgram(ast::NodeProgram * node)
{
    visitChildren(node);
}


void SemanticPass::visitVariableDeclaration(ast::NodeVarDeclaration * node)
{
    auto childCount = node->childCount();

    assert(childCount < 2);

    // Rule: If a variable is initialized, then the variable type and right expression type must match.
    if (childCount == 1)
    {
        // Rule: The right expression (initializer) type must match.
        auto rightExprType = visit(node->getChild(0));

        throw_if(node->GetVarType() != rightExprType,
                 SemanticErrorException("Line: ", node->getChild(0)->getSourceCodeLine(), " - Assignment type mismatch."));

        return;
    }

    visitChildren(node);
}


void SemanticPass::visitFunctionDeclaration(ast::NodeFuncDeclaration * node)
{
    auto funcReturnType = node->GetReturnType();

    // A function's return type can't be unknown.
    assert(funcReturnType != Type::kTypeUnknown);

    // Rule: A function must have at least one return statement if it returns a value.
    if (funcReturnType != Type::kTypeVoid)
    {
        // This search could be done faster by marking function declaration nodes when
        // visiting return statement nodes. AST nodes must be kept as simple as possible.
        throw_if(node->findClosestChildNode(ast::NodeType::kNodeTypeReturnStatement) == nullptr,
                 SemanticErrorException("Line: ", node->getSourceCodeLine(), " - ", node->GetFuncName(),
                                        " must have at least one return statement."));
    }

    visitChildren(node);
}


void SemanticPass::visitBlock(ast::NodeBlock * node)
{
    visitChildren(node);
}


void SemanticPass::visitIfStatement(ast::NodeIfStatement * node)
{
    // Requires a maximum of three children: ConditionExpr, Then Statement, Else Statement
    assert(node->childCount() < 4);
    visitChildren(node);
}


void SemanticPass::visitForStatement(ast::NodeForStatement * node)
{
    // There must be a forVarDec, ForCond, ForInc, and a Statement
    assert(node->childCount() == 4);

    auto forConditionNode = node->getChild(1);
    throw_if(forConditionNode->childCount() > 0 && visit(forConditionNode->getChild(0)) != Type::kTypeBool,
             SemanticErrorException("Line: ", node->getSourceCodeLine(), " - For comparison type mismatch."));

    visitChildren(node);
}


void SemanticPass::visitWhileStatement(ast::NodeWhileStatement * node)
{
    // There must be a condition expr and body.
    assert(node->childCount() == 2);

    auto conditionNode = node->getChild(0);
    throw_if(visit(conditionNode) != Type::kTypeBool,
             SemanticErrorException("Line: ", node->getSourceCodeLine(), " - While comparison type mismatch."));

    // visit the body statement children.
    auto bodyNode = node->getChild(1);
    visit(bodyNode);
}


void SemanticPass::visitDoWhileStatement(ast::NodeDoWhileStatement * node)
{
    // There must be a condition expr and body.
    assert(node->childCount() == 2);

    auto conditionNode = node->getChild(1);
    throw_if(visit(conditionNode) != Type::kTypeBool,
             SemanticErrorException("Line: ", node->getSourceCodeLine(), " - Do While comparison type mismatch."));

    // visit the body statement children.
    auto bodyNode = node->getChild(1);
    visit(bodyNode);
}


void SemanticPass::visitReturnStatement(ast::NodeReturnStatement * node)
{
    assert(node->childCount() < 2);

    // Find the belonging function declaration parent node.
    auto funcDeclNode = dynamic_cast<ast::NodeFuncDeclaration *>(node->findClosestParentNode({ast::NodeType::kNodeTypeFunctionDeclaration}));
    assert(funcDeclNode != nullptr);

    auto scope = funcDeclNode->getScope();
    auto funcSymbol = scope->resolveSymbol(funcDeclNode->GetFuncName());

    // Rule: A void function should not return a value.
    throw_if(funcSymbol->getType() == Type::kTypeVoid && node->childCount() == 1,
             SemanticErrorException("Line: ", node->getSourceCodeLine(), " - Void function ", funcSymbol->getName(),
                                    " should not return a value."));

    // Rule: A non-void function should return a value.
    throw_if(funcSymbol->getType() != Type::kTypeVoid && node->childCount() == 0,
             SemanticErrorException("Line: ", node->getSourceCodeLine(), " - Non-void function ", funcSymbol->getName(),
                                    " should return a value."));

    // Rule: The return value type should match the function return type.
    if (node->childCount() == 1)
    {
        auto returnExpr = node->getChild(0);
        auto returnExprType = visit(returnExpr);

        throw_if(funcSymbol->getType() != returnExprType,
                 SemanticErrorException("Line: ", returnExpr->getSourceCodeLine(), " - Return value type does not match ",
                                        funcSymbol->getName(), " return type."));
    }
}


void SemanticPass::visitContinue(ast::NodeContinue * node)
{
    auto loopNode = node->findClosestParentNode({ast::NodeType::kNodeTypeForStatement,
                                                 ast::NodeType::kNodeTypeWhileStatement});

    throw_if(loopNode == nullptr,
             SemanticErrorException("Line: ", node->getSourceCodeLine(), " - The 'continue' statement is allowed only in loops."));

    assert(node->childCount() == 0 && "The continue statement node must have zero children!");
}


void SemanticPass::visitBreak(ast::NodeBreak * node)
{
    auto loopNode = node->findClosestParentNode({ast::NodeType::kNodeTypeForStatement,
                                                 ast::NodeType::kNodeTypeWhileStatement});

    throw_if(loopNode == nullptr,
             SemanticErrorException("Line: ", node->getSourceCodeLine(), " - The 'break' statement is allowed only in loops."));

    assert(node->childCount() == 0 && "The break statement node must have zero children!");
}


Type SemanticPass::visitFunctionCall(ast::NodeFuncCall * node)
{
    auto scope = node->getScope();
    auto symbol = static_cast<FunctionSymbol *>(scope->resolveSymbol(node->GetFuncName()));
    assert(symbol && "Use of an undeclared identifier.");
    auto funcReturnType = symbol->getType();

    // Each node child is one parameter of the function call.
    // Rule: The number of parameters declared and the number of parameters used must match.
    throw_if(node->childCount() != symbol->argumentCount(),
             SemanticErrorException("Line: ", node->getSourceCodeLine(), " - No matching function to call: ",
                                    node->GetFuncName()));

    // Rule: The function argument type must match the expression (parameter) type.
    //       All parameters passed to a function are expressions.
    for (size_t index=0; index < node->childCount(); ++index)
    {
        // Parameter passed to the function.
        auto paramExprType = visit(node->getChild(index));
        // The function argument is declared when the function is declared.
        auto argumentType = symbol->getArgumentSymbol(index)->getType();

        throw_if(paramExprType != argumentType,
                 SemanticErrorException("Line: ", node->getSourceCodeLine(), " - No matching function to call: ",
                                        node->GetFuncName()));
    }

    return funcReturnType;
}


Type SemanticPass::visitAssignment(ast::NodeAssignment * node)
{
    // Rule: An assignment operation requires two operands.
    // The node must have two child nodes.
    assert(node->childCount() == 2);

    // Rule: The left and right expression types must match.
    auto leftOperandType = visit(node->getChild(0));
    auto rightOperandType = visit(node->getChild(1));

    throw_if(leftOperandType != rightOperandType,
             SemanticErrorException("Line: ", node->getSourceCodeLine(), " - Assignment type mismatch."));

    return leftOperandType;
}


Type SemanticPass::visitExplicitTypeConversion(ast::NodeExplicitTypeConversion * node)
{
    visit(node->getChild(0));

    return node->GetConversionType();
}


Type SemanticPass::visitLogicalOP(ast::NodeLogicalOP * node)
{
    auto nodeType = node->getNodeType();

    // The Not Operator requires only a single expression, so it requires special treatment.
    if (nodeType == ast::NodeType::kNodeTypeLogicalNotOP)
    {
        assert(node->childCount() == 1);
        return visit(node->getChild(0));
    }

    // Handle the rest of the other types of operators which require left and right expressions.
    auto leftOperandType  = visit(node->getChild(0));
    auto rightOperandType = visit(node->getChild(1));

    throw_if (leftOperandType != rightOperandType,
              SemanticErrorException("Line: ", node->getSourceCodeLine(), " - Logical operation type mismatch."));

    return leftOperandType;
}


Type SemanticPass::visitPrefixAOP(ast::NodePrefixAOP * node)
{
    auto rightOperandType = visit(node->getChild(0));

    throw_if(node->getChild(0)->getNodeType() != ast::NodeType::kNodeTypeLiteralID,
             SemanticErrorException("Line: ", node->getSourceCodeLine(), " - Prefix arithmetic operation is not allowed."));

    throw_if(rightOperandType != Type::kTypeFloat && rightOperandType != Type::kTypeInt,
             SemanticErrorException("Line: ", node->getSourceCodeLine(), " - Arithmetic operation type mismatch."));

    return rightOperandType;
}


Type SemanticPass::visitAOP(ast::NodeAOP * node)
{
    // Rule: An arithmetic operation requires two operands.
    // The node must have two child nodes.
    assert(node->childCount() == 2);

    // Rule: The left and right expression types must match.
    auto leftOperandType = visit(node->getChild(0));
    auto rightOperandType = visit(node->getChild(1));

    throw_if(leftOperandType != rightOperandType,
             SemanticErrorException("Line: ", node->getSourceCodeLine(), " - Arithmetic operation type mismatch."));

    return leftOperandType;
}


Type SemanticPass::visitLiteral(ast::NodeLiteral * node)
{
    Type literalType = Type::kTypeUnknown;

    switch (node->getNodeType())
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
                auto scope = node->getScope();
                auto symbol = scope->resolveSymbol(node->GetValue());
                assert(symbol && "Use of an undeclared identifier");
                literalType = symbol->getType();
            }
            break;

        default:
            assert(false && "Unknown node type in SemanticPass::visitLiteral");
            break;
    }

    // This node should have no children.
    assert(node->childCount() == 0);

    // Return the type of literal so the parent node can perform a type check if necessary.
    return literalType;
}


Type SemanticPass::visitNodeUnaryOP(ast::NodeUnaryOP * node)
{
    // The node must have one child node.
    assert(node->childCount() == 1);

    auto rightOperandType = visit(node->getChild(0));

    throw_if(rightOperandType != Type::kTypeFloat && rightOperandType != Type::kTypeInt,
             SemanticErrorException("Line: ", node->getSourceCodeLine(), " - Unary operation type mismatch."));

    // Return the type of the right expr value.
    return rightOperandType;
}


Type SemanticPass::visitCompOP(ast::NodeCompOP * node)
{
    // Rule: A comparison operation requires two operands.
    // The node must have two child nodes.
    assert(node->childCount() == 2);

    // Rule: The left and right expression types must match.
    auto leftOperandType = visit(node->getChild(0));
    auto rightOperandType = visit(node->getChild(1));

    throw_if(leftOperandType != rightOperandType,
             SemanticErrorException("Line: ", node->getSourceCodeLine(), " - Comparison operation type mismatch."));

    // The comparison result type is always bool type.
    return Type::kTypeBool;
}

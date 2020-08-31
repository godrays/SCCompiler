//
//  SemanticPass.cpp
//
//  Created by Arkin Terli on 4/16/18.
//  Copyright © 2018-Present, Arkin Terli. All rights reserved.
//

#include "SemanticPass.hpp"

#include <cassert>
#include <sstream>

#include "AST.hpp"
#include "Exceptions.hpp"
#include "Symbols.hpp"


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

        case ast::NodeType::kNodeTypeIfStatement:
            VisitIfStatement(dynamic_cast<ast::NodeIfStatement *>(node));
            break;

        case ast::NodeType::kNodeTypeForStatement:
            VisitForStatement(dynamic_cast<ast::NodeForStatement *>(node));
            break;

        case ast::NodeType::kNodeTypeForVarDecl:
        case ast::NodeType::kNodeTypeForCondition:
        case ast::NodeType::kNodeTypeForIncrement:
            // These are just sub-statement / grouping nodes. Nothing to do with.
            VisitChilds(node);
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


void SemanticPass::VisitIfStatement(ast::NodeIfStatement * node)
{
    // Requires max three childs: ConditionExpr, Then Statement, Else Statement
    assert(node->ChildCount() < 4);

    // Visit childs
    VisitChilds(node);
}


void SemanticPass::VisitForStatement(ast::NodeForStatement * node)
{
    // There must be forVarDec, ForCond, ForInc and a Statement
    assert(node->ChildCount() == 4);
    
    auto forConditionNode = node->GetChild(1);
    if (forConditionNode->ChildCount() > 0 && Visit(forConditionNode->GetChild(0)) != Type::kTypeBool)
    {
        std::stringstream   message;
        message << "Line: " << node->GetSourceCodeLine() << " - For comparison type mismatch." << std::endl;
        throw SemanticErrorException(message.str());
    }
    // Visit childs
    VisitChilds(node);
}


void SemanticPass::VisitWhileStatement(ast::NodeWhileStatement * node)
{
    // There must be condition expr and body.
    assert(node->ChildCount() == 2);
    
    auto conditionNode = node->GetChild(0);
    if (Visit(conditionNode) != Type::kTypeBool)
    {
        std::stringstream   message;
        message << "Line: " << node->GetSourceCodeLine() << " - While comparison type mismatch." << std::endl;
        throw SemanticErrorException(message.str());
    }

    // Visit body statement childs.
    auto bodyNode = node->GetChild(1);
    Visit(bodyNode);
}


void SemanticPass::VisitDoWhileStatement(ast::NodeDoWhileStatement * node)
{
    // There must be condition expr and body.
    assert(node->ChildCount() == 2);
    
    auto conditionNode = node->GetChild(1);
    if (Visit(conditionNode) != Type::kTypeBool)
    {
        std::stringstream   message;
        message << "Line: " << node->GetSourceCodeLine() << " - Do While comparison type mismatch." << std::endl;
        throw SemanticErrorException(message.str());
    }

    // Visit body statement childs.
    auto bodyNode = node->GetChild(1);
    Visit(bodyNode);
}


void SemanticPass::VisitReturnStatement(ast::NodeReturnStatement * node)
{
    assert(node->ChildCount() < 2);

    // Find belonging function declaration parent node.
    auto funcDeclNode = dynamic_cast<ast::NodeFuncDeclaration *>(node->FindClosestParentNode({ast::NodeType::kNodeTypeFunctionDeclaration}));
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


void SemanticPass::VisitContinue(ast::NodeContinue * node)
{
    auto loopNode = node->FindClosestParentNode({ast::NodeType::kNodeTypeForStatement,
                                                 ast::NodeType::kNodeTypeWhileStatement});
    
    if (loopNode == nullptr)
    {
        std::stringstream   message;
        message << "Line: " << node->GetSourceCodeLine() << " - 'continue' statement is allowed only in loops." << std::endl;
        throw SemanticErrorException(message.str());
    }
    
    assert(node->ChildCount() == 0 && "continue statement node must have zero child!");
}


void SemanticPass::VisitBreak(ast::NodeBreak * node)
{
    auto loopNode = node->FindClosestParentNode({ast::NodeType::kNodeTypeForStatement,
                                                 ast::NodeType::kNodeTypeWhileStatement});

    if (loopNode == nullptr)
    {
        std::stringstream   message;
        message << "Line: " << node->GetSourceCodeLine() << " - 'break' statement is allowed only in loops." << std::endl;
        throw SemanticErrorException(message.str());
    }
    
    assert(node->ChildCount() == 0 && "break statement node must have zero child!");
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


Type SemanticPass::VisitExplicitTypeConversion(ast::NodeExplicitTypeConversion * node)
{
    Visit(node->GetChild(0));
    
    return node->GetConversionType();
}


Type SemanticPass::VisitLogicalOP(ast::NodeLogicalOP * node)
{
    auto nodeType = node->GetNodeType();

    // Not Operator requires only a single expression so it requires special treatment.
    if (nodeType == ast::NodeType::kNodeTypeLogicalNotOP)
    {
        assert(node->ChildCount() == 1);
        return Visit(node->GetChild(0));
    }

    // Handle rest of the other type of operators which requires left and right expressions.
    auto leftOperandType  = Visit(node->GetChild(0));
    auto rightOperandType = Visit(node->GetChild(1));
    
    if (leftOperandType != rightOperandType)
    {
        std::stringstream   message;
        message << "Line: " << node->GetSourceCodeLine() << " - Logical operation type mismatch." << std::endl;
        throw SemanticErrorException( message.str());
    }

    return leftOperandType;
}


Type SemanticPass::VisitPrefixAOP(ast::NodePrefixAOP * node)
{
    auto rightOperandType = Visit(node->GetChild(0));
    
    if (node->GetChild(0)->GetNodeType() != ast::NodeType::kNodeTypeLiteralID)
    {
        std::stringstream   message;
        message << "Line: " << node->GetSourceCodeLine() << " - Prefix arithmetic operation is not allowed." << std::endl;
        throw SemanticErrorException( message.str());
    }

    if (rightOperandType != Type::kTypeFloat && rightOperandType != Type::kTypeInt)
    {
        std::stringstream   message;
        message << "Line: " << node->GetSourceCodeLine() << " - Arithmetic operation type mismatch." << std::endl;
        throw SemanticErrorException( message.str());
    }

    return rightOperandType;
}


Type SemanticPass::VisitAOP(ast::NodeAOP * node)
{
    // Rule: Arithmetic operation requires two operands.
    // Node must have two child nodes.
    assert(node->ChildCount() == 2);

    // Rule: Left and right expression type must match.
    auto leftOperandType = Visit(node->GetChild(0));
    auto rightOperandType = Visit(node->GetChild(1));
    
    if (leftOperandType != rightOperandType)
    {
        std::stringstream   message;
        message << "Line: " << node->GetSourceCodeLine() << " - Arithmetic operation type mismatch." << std::endl;
        throw SemanticErrorException( message.str());
    }

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


Type SemanticPass::VisitNodeUnaryOP(ast::NodeUnaryOP * node)
{
    // Node must have two child nodes.
    assert(node->ChildCount() == 1);

    auto rightOperandType = Visit(node->GetChild(0));
    
    if (rightOperandType != Type::kTypeFloat &&
        rightOperandType != Type::kTypeInt)
    {
        std::stringstream   message;
        message << "Line: " << node->GetSourceCodeLine() << " - Unary operation type mismatch." << std::endl;
        throw SemanticErrorException( message.str());
    }

    // Return type of right expr value.
    return rightOperandType;
}


Type SemanticPass::VisitCompOP(ast::NodeCompOP * node)
{
    // Rule: Comparison operation requires two operands.
    // Node must have two child nodes.
    assert(node->ChildCount() == 2);

    // Rule: Left and right expression type must match.
    auto leftOperandType = Visit(node->GetChild(0));
    auto rightOperandType = Visit(node->GetChild(1));
    
    if (leftOperandType != rightOperandType)
    {
        std::stringstream   message;
        message << "Line: " << node->GetSourceCodeLine() << " - Comparison operation type mismatch." << std::endl;
        throw SemanticErrorException( message.str());
    }

    // Comparison result type is always bool type.
    return Type::kTypeBool;
}

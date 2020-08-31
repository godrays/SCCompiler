//
//  AST.cpp
//
//  Created by Arkin Terli on 4/10/18.
//  Copyright © 2018-Present, Arkin Terli. All rights reserved.
//

#include "AST.hpp"

#include <cassert>
#include <utility>


using namespace scc;


#pragma mark - FuncArg Implementation

ast::FuncArg::FuncArg(Type type, std::string name) : m_type(type), m_name(std::move(name))
{

}


Type ast::FuncArg::GetType()
{
    return m_type;
}


std::string ast::FuncArg::GetName()
{
    return m_name;
}


#pragma mark - Node Implementation


ast::Node::Node(NodeType nodeType) : m_nodeType(nodeType)
{

}


ast::Node::~Node()
{
    DeleteChilds();
}


void ast::Node::DeleteChilds()
{
    // Delete all childs.
    for (auto child : m_childs)
    {
        delete child;
    }

    m_childs.clear();
}


void ast::Node::AddChild(ast::Node * childNode)
{
    m_childs.emplace_back(childNode);
}


size_t ast::Node::ChildCount()
{
    return m_childs.size();
}


ast::Node * ast::Node::GetChild(size_t index)
{
    assert(index < m_childs.size());
    return m_childs[index];
}


void ast::Node::SetParent(ast::Node * parentNode)
{
    m_parent = parentNode;
}


ast::Node * ast::Node::GetParent()
{
    return m_parent;
}

ast::NodeType  ast::Node::GetNodeType()
{
    return m_nodeType;
}

void ast::Node::SetSourceCodeLine(size_t lineNumber)
{
    m_lineNumber = lineNumber;
}

size_t ast::Node::GetSourceCodeLine() const
{
    return m_lineNumber;
}


std::string ast::Node::GetNodeTypeInString(ast::NodeType nodeType)
{
    std::string typeInString;

    switch (nodeType)
    {
        case ast::NodeType::kNodeTypeProgram:
        typeInString = "tNodeTypeProgram";
        break;

        case ast::NodeType::kNodeTypeAOPAdd:
        typeInString = "tNodeTypeAOPAdd";
        break;

        case ast::NodeType::kNodeTypeAOPDiv:
        typeInString = "tNodeTypeAOPDiv";
        break;

        case ast::NodeType::kNodeTypeAOPMul:
        typeInString = "tNodeTypeAOPMul";
        break;

        case ast::NodeType::kNodeTypeAOPSub:
        typeInString = "tNodeTypeAOPSub";
        break;

        case ast::NodeType::kNodeTypeAssignment:
        typeInString = "tNodeTypeAssignment";
        break;

        case ast::NodeType::kNodeTypeBlock:
        typeInString = "tNodeTypeBlock";
        break;

        case ast::NodeType::kNodeTypeFuncCall:
        typeInString = "tNodeTypeFuncCall";
        break;

        case ast::NodeType::kNodeTypeFunctionDeclaration:
        typeInString = "tNodeTypeFunctionDeclaration";
        break;

        case ast::NodeType::kNodeTypeIfStatement:
        typeInString = "tNodeTypeIfStatement";
        break;

        case ast::NodeType::kNodeTypeForStatement:
        typeInString = "tNodeTypeForStatement";
        break;

        case ast::NodeType::kNodeTypeForVarDecl:
        typeInString = "kNodeTypeForVarDecl";
        break;

        case ast::NodeType::kNodeTypeForCondition:
        typeInString = "kNodeTypeForCondition";
        break;

        case ast::NodeType::kNodeTypeForIncrement:
        typeInString = "kNodeTypeForIncrement";
        break;

        case ast::NodeType::kNodeTypeWhileStatement:
        typeInString = "tNodeTypeWhileStatement";
        break;

        case ast::NodeType::kNodeTypeDoWhileStatement:
        typeInString = "tNodeTypeDoWhileStatement";
        break;

        case ast::NodeType::kNodeTypeLiteralBool:
        typeInString = "tNodeTypeLiteralBool";
        break;

        case ast::NodeType::kNodeTypeLiteralFloat:
        typeInString = "tNodeTypeLiteralFloat";
        break;

        case ast::NodeType::kNodeTypeLiteralID:
        typeInString = "tNodeTypeLiteralID";
        break;

        case ast::NodeType::kNodeTypeLiteralInt32:
        typeInString = "tNodeTypeLiteralInt32";
        break;

        case ast::NodeType::kNodeTypeReturnStatement:
        typeInString = "tNodeTypeReturnStatement";
        break;

        case ast::NodeType::kNodeTypeContinue:
        typeInString = "kNodeTypeContinue";
        break;

        case ast::NodeType::kNodeTypeBreak:
        typeInString = "kNodeTypeBreak";
        break;

        case ast::NodeType::kNodeTypeUnknown:
        typeInString = "tNodeTypeReturnStatement";
        break;

        case ast::NodeType::kNodeTypeVariableDeclaration:
        typeInString = "tNodeTypeVariableDeclaration";
        break;

        case ast::NodeType::kNodeTypeExplicitTypeConversion:
        typeInString = "kNodeTypeExplicitTypeConversion";
        break;

        case ast::NodeType::kNodeTypeLogicalNotOP:
        typeInString = "kNodeTypeLogicalNotOP";
        break;

        case ast::NodeType::kNodeTypeLogicalAndOP:
        typeInString = "kNodeTypeLogicalAndOP";
        break;

        case ast::NodeType::kNodeTypeLogicalOrOP:
        typeInString = "kNodeTypeLogicalOrOP";
        break;

        case ast::NodeType::kNodeTypeUOPPlus:
        typeInString = "kNodeTypeUOPPlus";
        break;

        case ast::NodeType::kNodeTypeUOPMinus:
        typeInString = "kNodeTypeUOPMinus";
        break;

        case ast::NodeType::kNodeTypeCompOPEQ:
        typeInString = "kNodeTypeCompOPEQ";
        break;

        case ast::NodeType::kNodeTypeCompOPNEQ:
        typeInString = "kNodeTypeCompOPNEQ";
        break;

        case ast::NodeType::kNodeTypeCompOPLE:
        typeInString = "kNodeTypeCompOPLE";
        break;

        case ast::NodeType::kNodeTypeCompOPGE:
        typeInString = "kNodeTypeCompOPGE";
        break;

        case ast::NodeType::kNodeTypeCompOPL:
        typeInString = "kNodeTypeCompOPL";
        break;

        case ast::NodeType::kNodeTypeCompOPG:
        typeInString = "kNodeTypeCompOPG";
        break;

        default:
        assert(false && "Unknown node type in Node::GetNodeTypeInString()");
        break;
    }

    return typeInString;
}


ast::Node * ast::Node::FindClosestParentNode(const std::vector<ast::NodeType> & nodeTypes)
{
    // If node type matches one of the given type then return it.
    for (auto nodeType : nodeTypes)
    {
        if (m_nodeType == nodeType)
        {
            return this;
        }
    }

    if ( m_parent != nullptr )
    {
        return m_parent->FindClosestParentNode(nodeTypes);
    }

    return nullptr;
}


ast::Node * ast::Node::FindClosestChildNode(ast::NodeType nodeType)
{
    if (m_nodeType == nodeType)
    {
        return this;
    }

    for (const auto & m_child : m_childs)
    {
        auto foundNode = m_child->FindClosestChildNode(nodeType);

        if (foundNode)
        {
            return foundNode;
        }
    }

    return nullptr;
}


void ast::Node::SetScope(ScopeNode * scope)
{
    m_scope = scope;
}


ScopeNode * ast::Node::GetScope()
{
    return m_scope;
}


#pragma mark - NodeProgram Implementation

ast::NodeProgram::NodeProgram()
{
    m_nodeType = kNodeTypeProgram;
}


ast::NodeProgram::~NodeProgram()
{
    DeleteChilds();
}


#pragma mark - NodeVarDeclaration Implementation

ast::NodeVarDeclaration::NodeVarDeclaration(Type type, std::string varName) : ast::Node(kNodeTypeVariableDeclaration)
{
    m_varType = type;
    m_varName = std::move(varName);
}


ast::NodeVarDeclaration::~NodeVarDeclaration()
{
    DeleteChilds();
}


Type ast::NodeVarDeclaration::GetVarType()
{
    return m_varType;
}


std::string ast::NodeVarDeclaration::GetVarName()
{
    return m_varName;
}


#pragma mark - NodeFuncDeclaration Implementation

ast::NodeFuncDeclaration::NodeFuncDeclaration(Type returnType, std::string funcName) : ast::Node(kNodeTypeFunctionDeclaration)
{
    m_returnType = returnType;
    m_funcName = std::move(funcName);
}


ast::NodeFuncDeclaration::~NodeFuncDeclaration()
{
    DeleteChilds();
}


std::string ast::NodeFuncDeclaration::GetFuncName()
{
    return m_funcName;
}


Type ast::NodeFuncDeclaration::GetReturnType()
{
    return m_returnType;
}


void ast::NodeFuncDeclaration::AddArgument(const ast::FuncArg & argument)
{
    m_argumentList.emplace_back(argument);
}


std::vector<ast::FuncArg> ast::NodeFuncDeclaration::GetArguments()
{
    return m_argumentList;
}


#pragma mark - NodeIfStatement Implementation

ast::NodeIfStatement::NodeIfStatement() : ast::Node(kNodeTypeIfStatement)
{

}


ast::NodeIfStatement::~NodeIfStatement()
{
    DeleteChilds();
}


#pragma mark - NodeForStatement Implementation

ast::NodeForStatement::NodeForStatement() : ast::Node(kNodeTypeForStatement)
{

}


ast::NodeForStatement::~NodeForStatement()
{
    DeleteChilds();
}


#pragma mark - NodeFor Implementation

ast::NodeFor::NodeFor(ast::NodeType nodeType) : Node(nodeType)
{

}


ast::NodeFor::~NodeFor()
{
    DeleteChilds();
}


#pragma mark - NodeWhileStatement Implementation

ast::NodeWhileStatement::NodeWhileStatement() : ast::Node(kNodeTypeWhileStatement)
{

}


ast::NodeWhileStatement::~NodeWhileStatement()
{
    DeleteChilds();
}


#pragma mark - NodeDoWhileStatement Implementation

ast::NodeDoWhileStatement::NodeDoWhileStatement() : ast::Node(kNodeTypeDoWhileStatement)
{

}


ast::NodeDoWhileStatement::~NodeDoWhileStatement()
{
    DeleteChilds();
}


#pragma mark - NodeReturnStatement Implementation

ast::NodeReturnStatement::NodeReturnStatement() : ast::Node(kNodeTypeReturnStatement)
{

}


ast::NodeReturnStatement::~NodeReturnStatement()
{
    DeleteChilds();
}


#pragma mark - NodeContinue Implementation

ast::NodeContinue::NodeContinue() : ast::Node(kNodeTypeContinue)
{

}


ast::NodeContinue::~NodeContinue()
{
    DeleteChilds();
}


#pragma mark - NodeBreak Implementation

ast::NodeBreak::NodeBreak() : ast::Node(kNodeTypeBreak)
{

}


ast::NodeBreak::~NodeBreak()
{
    DeleteChilds();
}


#pragma mark - NodeFuncCall Implementation

ast::NodeFuncCall::NodeFuncCall(std::string funcName)  : ast::Node(kNodeTypeFuncCall)
{
    m_funcName = std::move(funcName);
}

ast::NodeFuncCall::~NodeFuncCall()
{
    DeleteChilds();
}

std::string ast::NodeFuncCall::GetFuncName()
{
    return m_funcName;
}


#pragma mark - NodeBlock Implementation

ast::NodeBlock::NodeBlock()
{
    m_nodeType = kNodeTypeBlock;
}


// Destructor.
ast::NodeBlock::~NodeBlock()
{
    DeleteChilds();
}


#pragma mark - NodeAssignment Implementation

ast::NodeAssignment::NodeAssignment() : Node(kNodeTypeAssignment)
{

}


ast::NodeAssignment::~NodeAssignment()
{
    DeleteChilds();
}


#pragma mark - NodeExplicitTypeConversion Implementation

ast::NodeExplicitTypeConversion::NodeExplicitTypeConversion(Type conversionType) :
    Node(kNodeTypeExplicitTypeConversion),
    m_conversionType(conversionType)
{

}


Type ast::NodeExplicitTypeConversion::GetConversionType()
{
    return m_conversionType;
}


ast::NodeExplicitTypeConversion::~NodeExplicitTypeConversion()
{
    DeleteChilds();
}


#pragma mark - NodeLogicalOP Implementation

ast::NodeLogicalOP::NodeLogicalOP(ast::NodeType nodeType) : Node(nodeType)
{
    assert(nodeType == ast::NodeType::kNodeTypeLogicalNotOP
        || nodeType == ast::NodeType::kNodeTypeLogicalAndOP
        || nodeType == ast::NodeType::kNodeTypeLogicalOrOP);
}


ast::NodeLogicalOP::~NodeLogicalOP()
{
    DeleteChilds();
}


#pragma mark - NodeUnaryOP Implementation

ast::NodeUnaryOP::NodeUnaryOP(NodeType nodeType) : Node(nodeType)
{
    assert(nodeType == ast::NodeType::kNodeTypeUOPPlus
        || nodeType == ast::NodeType::kNodeTypeUOPMinus);
}


ast::NodeUnaryOP::~NodeUnaryOP()
{
    DeleteChilds();
}


#pragma mark - NodeCompOP Implementation

ast::NodeCompOP::NodeCompOP(ast::NodeType nodeType) : ast::Node(nodeType)
{
    assert(nodeType == ast::NodeType::kNodeTypeCompOPEQ
        || nodeType == ast::NodeType::kNodeTypeCompOPNEQ
        || nodeType == ast::NodeType::kNodeTypeCompOPLE
        || nodeType == ast::NodeType::kNodeTypeCompOPGE
        || nodeType == ast::NodeType::kNodeTypeCompOPL
        || nodeType == ast::NodeType::kNodeTypeCompOPG);
}


ast::NodeCompOP::~NodeCompOP()
{
    DeleteChilds();
}


#pragma mark - NodeAOP Implementation

ast::NodeAOP::NodeAOP(ast::NodeType nodeType) : ast::Node(nodeType)
{
    assert(nodeType == ast::NodeType::kNodeTypeAOPMul
        || nodeType == ast::NodeType::kNodeTypeAOPDiv
        || nodeType == ast::NodeType::kNodeTypeAOPAdd
        || nodeType == ast::NodeType::kNodeTypeAOPSub);
}


ast::NodeAOP::~NodeAOP()
{
    DeleteChilds();
}


#pragma mark - NodePrefixAOP Implementation

ast::NodePrefixAOP::NodePrefixAOP(ast::NodeType nodeType) : ast::Node(nodeType)
{
    assert(nodeType == ast::NodeType::kNodeTypePrefixIncAOP
        || nodeType == ast::NodeType::kNodeTypePrefixDecAOP);
}


ast::NodePrefixAOP::~NodePrefixAOP()
{
    DeleteChilds();
}


#pragma mark - NodeLiteral Implementation

ast::NodeLiteral::NodeLiteral(ast::NodeType nodeType, std::string value) :
    ast::Node(nodeType),
    m_value(std::move(value))
{
    assert(nodeType == ast::NodeType::kNodeTypeLiteralFloat
        || nodeType == ast::NodeType::kNodeTypeLiteralInt32
        || nodeType == ast::NodeType::kNodeTypeLiteralBool
        || nodeType == ast::NodeType::kNodeTypeLiteralID);
}


ast::NodeLiteral::~NodeLiteral()
{
    DeleteChilds();
}


std::string ast::NodeLiteral::GetValue()
{
    return m_value;
}


#pragma mark - TypeToString Implementation

std::string ast::TypeToString(Type type)
{
    switch (type)
    {
        case kTypeFloat:
            return "float";
        break;

        case kTypeInt:
            return "int";
        break;

        case kTypeBool:
            return "bool";
        break;

        case kTypeVoid:
            return "void";
        break;

        default:
            assert(false && "Unknown type in TypeToString()");
        break;
    }
    
    return "Unknown";
}


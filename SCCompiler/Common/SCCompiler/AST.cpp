//
//  AST.cpp
//
//  Created by Arkin Terli on 4/10/18.
//  Copyright © 2018 Arkin Terli. All rights reserved.
//

#include <cassert>

#include "AST.hpp"

using namespace scc;


#pragma mark - FuncArg Implementation

ast::FuncArg::FuncArg(Type type, std::string name) : m_type(type), m_name(name)
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

ast::Node::Node()
{

}


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

size_t ast::Node::GetSourceCodeLine()
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

        case ast::NodeType::kNodeTypeUnknown:
        typeInString = "tNodeTypeReturnStatement";
        break;

        case ast::NodeType::kNodeTypeVariableDeclaration:
        typeInString = "tNodeTypeVariableDeclaration";
        break;
    
        default:
        assert(false && "Unknown node type in Node::GetNodeTypeInString()");
        break;
    }

    return typeInString;
}


ast::Node * ast::Node::FindClosestParentNode(ast::NodeType nodeType)
{
    if (m_nodeType == nodeType)
    {
        return this;
    }

    if ( m_parent != nullptr )
    {
        return m_parent->FindClosestParentNode(nodeType);
    }

    return nullptr;
}


ast::Node * ast::Node::FindClosestChildNode(ast::NodeType nodeType)
{
    if (m_nodeType == nodeType)
    {
        return this;
    }

    for (size_t index=0; index < m_childs.size(); ++index)
    {
        auto foundNode = m_childs[index]->FindClosestChildNode(nodeType);

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
    m_varName = varName;
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
    m_funcName = funcName;
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


void ast::NodeFuncDeclaration::AddArgument(ast::FuncArg argument)
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


#pragma mark - NodeReturnStatement Implementation

ast::NodeReturnStatement::NodeReturnStatement() : ast::Node(kNodeTypeReturnStatement)
{

}

// Destructor.
ast::NodeReturnStatement::~NodeReturnStatement()
{
    DeleteChilds();
}


#pragma mark - NodeFuncCall Implementation

ast::NodeFuncCall::NodeFuncCall(std::string funcName)  : ast::Node(kNodeTypeFuncCall)
{
    m_funcName = funcName;
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


#pragma mark - NodeLiteral Implementation

ast::NodeLiteral::NodeLiteral(ast::NodeType nodeType, std::string value) :
    ast::Node(nodeType),
    m_value(value)
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


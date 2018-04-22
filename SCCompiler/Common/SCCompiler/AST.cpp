//
//  AST.cpp
//
//  Created by Arkin Terli on 4/10/18.
//  Copyright © 2018 Arkin Terli. All rights reserved.
//

#include <cassert>

#include "AST.hpp"

using namespace SCCompiler;


#pragma mark - FuncArg Implementation


AST::FuncArg::FuncArg(Type type, std::string name) : m_type(type), m_name(name)
{

}


Type AST::FuncArg::GetType()
{
    return m_type;
}


std::string AST::FuncArg::GetName()
{
    return m_name;
}


#pragma mark - Node Implementation


AST::Node::Node()
{

}


AST::Node::Node(NodeType nodeType) : m_nodeType(nodeType)
{

}


AST::Node::~Node()
{
    DeleteChilds();
}


void AST::Node::DeleteChilds()
{
    // Delete all childs.
    for (auto child : m_childs)
    {
        delete child;
    }

    m_childs.clear();
}


void AST::Node::AddChild(AST::Node * childNode)
{
    m_childs.emplace_back(childNode);
}


size_t AST::Node::ChildCount()
{
    return m_childs.size();
}


AST::Node * AST::Node::GetChild(size_t index)
{
    return m_childs[index];
}


void AST::Node::SetParent(AST::Node * parentNode)
{
    m_parent = parentNode;
}


AST::Node * AST::Node::GetParent()
{
    return m_parent;
}

AST::NodeType  AST::Node::GetNodeType()
{
    return m_nodeType;
}

void AST::Node::SetSourceCodeLine(size_t lineNumber)
{
    m_lineNumber = lineNumber;
}

size_t AST::Node::GetSourceCodeLine()
{
    return m_lineNumber;
}


std::string AST::Node::GetNodeTypeInString(AST::NodeType nodeType)
{
    std::string typeInString;

    switch (nodeType)
    {
        case AST::NodeType::tNodeTypeProgram:
        typeInString = "tNodeTypeProgram";
        break;

        case AST::NodeType::tNodeTypeAOPAdd:
        typeInString = "tNodeTypeAOPAdd";
        break;

        case AST::NodeType::tNodeTypeAOPDiv:
        typeInString = "tNodeTypeAOPDiv";
        break;

        case AST::NodeType::tNodeTypeAOPMul:
        typeInString = "tNodeTypeAOPMul";
        break;

        case AST::NodeType::tNodeTypeAOPSub:
        typeInString = "tNodeTypeAOPSub";
        break;

        case AST::NodeType::tNodeTypeAssignment:
        typeInString = "tNodeTypeAssignment";
        break;

        case AST::NodeType::tNodeTypeBlock:
        typeInString = "tNodeTypeBlock";
        break;

        case AST::NodeType::tNodeTypeFuncCall:
        typeInString = "tNodeTypeFuncCall";
        break;

        case AST::NodeType::tNodeTypeFunctionDeclaration:
        typeInString = "tNodeTypeFunctionDeclaration";
        break;

        case AST::NodeType::tNodeTypeIfStatement:
        typeInString = "tNodeTypeIfStatement";
        break;

        case AST::NodeType::tNodeTypeLiteralBool:
        typeInString = "tNodeTypeLiteralBool";
        break;

        case AST::NodeType::tNodeTypeLiteralFloat:
        typeInString = "tNodeTypeLiteralFloat";
        break;

        case AST::NodeType::tNodeTypeLiteralID:
        typeInString = "tNodeTypeLiteralID";
        break;

        case AST::NodeType::tNodeTypeLiteralInt32:
        typeInString = "tNodeTypeLiteralInt32";
        break;

        case AST::NodeType::tNodeTypeReturnStatement:
        typeInString = "tNodeTypeReturnStatement";
        break;

        case AST::NodeType::tNodeTypeUnknown:
        typeInString = "tNodeTypeReturnStatement";
        break;

        case AST::NodeType::tNodeTypeVariableDeclaration:
        typeInString = "tNodeTypeVariableDeclaration";
        break;
    
        default:
        assert(false && "Unknown node type in Node::GetNodeTypeInString()");
        break;
    }

    return typeInString;
}


AST::Node * AST::Node::FindClosestParentNode(AST::NodeType nodeType)
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


AST::Node * AST::Node::FindClosestChildNode(AST::NodeType nodeType)
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


void AST::Node::SetScope(ScopeNode * scope)
{
    m_scope = scope;
}


ScopeNode * AST::Node::GetScope()
{
    return m_scope;
}


#pragma mark - NodeProgram Implementation


AST::NodeProgram::NodeProgram()
{
    m_nodeType = tNodeTypeProgram;
}


AST::NodeProgram::~NodeProgram()
{
    DeleteChilds();
}


#pragma mark - NodeVarDeclaration Implementation


AST::NodeVarDeclaration::NodeVarDeclaration(Type type, std::string varName) : AST::Node(tNodeTypeVariableDeclaration)
{
    m_varType = type;
    m_varName = varName;
}


AST::NodeVarDeclaration::~NodeVarDeclaration()
{
    DeleteChilds();
}


Type AST::NodeVarDeclaration::GetVarType()
{
    return m_varType;
}


std::string AST::NodeVarDeclaration::GetVarName()
{
    return m_varName;
}


#pragma mark - NodeFuncDeclaration Implementation


AST::NodeFuncDeclaration::NodeFuncDeclaration(Type returnType, std::string funcName) : AST::Node(tNodeTypeFunctionDeclaration)
{
    m_returnType = returnType;
    m_funcName = funcName;
}


AST::NodeFuncDeclaration::~NodeFuncDeclaration()
{
    DeleteChilds();
}


std::string AST::NodeFuncDeclaration::GetFuncName()
{
    return m_funcName;
}


Type AST::NodeFuncDeclaration::GetReturnType()
{
    return m_returnType;
}


void AST::NodeFuncDeclaration::AddArgument(AST::FuncArg argument)
{
    m_argumentList.emplace_back(argument);
}


std::vector<AST::FuncArg> AST::NodeFuncDeclaration::GetArguments()
{
    return m_argumentList;
}


#pragma mark - NodeIfStatement Implementation

AST::NodeIfStatement::NodeIfStatement() : AST::Node(tNodeTypeIfStatement)
{

}

AST::NodeIfStatement::~NodeIfStatement()
{
    DeleteChilds();
}


#pragma mark - NodeReturnStatement Implementation

AST::NodeReturnStatement::NodeReturnStatement() : AST::Node(tNodeTypeReturnStatement)
{

}

// Destructor.
AST::NodeReturnStatement::~NodeReturnStatement()
{
    DeleteChilds();
}


#pragma mark - NodeFuncCall Implementation

AST::NodeFuncCall::NodeFuncCall(std::string funcName)  : AST::Node(tNodeTypeFuncCall)
{
    m_funcName = funcName;
}

AST::NodeFuncCall::~NodeFuncCall()
{
    DeleteChilds();
}

std::string AST::NodeFuncCall::GetFuncName()
{
    return m_funcName;
}


#pragma mark - NodeBlock Implementation


AST::NodeBlock::NodeBlock()
{
    m_nodeType = tNodeTypeBlock;
}


// Destructor.
AST::NodeBlock::~NodeBlock()
{
    DeleteChilds();
}


#pragma mark - NodeAssignment Implementation


AST::NodeAssignment::NodeAssignment() : Node(tNodeTypeAssignment)
{

}


AST::NodeAssignment::~NodeAssignment()
{
    DeleteChilds();
}



#pragma mark - NodeAOP Implementation


AST::NodeAOP::NodeAOP(AST::NodeType nodeType) : AST::Node(nodeType)
{
    assert(nodeType == AST::NodeType::tNodeTypeAOPMul
        || nodeType == AST::NodeType::tNodeTypeAOPDiv
        || nodeType == AST::NodeType::tNodeTypeAOPAdd
        || nodeType == AST::NodeType::tNodeTypeAOPSub);
}


AST::NodeAOP::~NodeAOP()
{
    DeleteChilds();
}


#pragma mark - NodeLiteral Implementation


AST::NodeLiteral::NodeLiteral(AST::NodeType nodeType, std::string value) :
    AST::Node(nodeType),
    m_value(value)
{
    assert(nodeType == AST::NodeType::tNodeTypeLiteralFloat
        || nodeType == AST::NodeType::tNodeTypeLiteralInt32
        || nodeType == AST::NodeType::tNodeTypeLiteralBool
        || nodeType == AST::NodeType::tNodeTypeLiteralID);
}


AST::NodeLiteral::~NodeLiteral()
{
    DeleteChilds();
}


std::string AST::NodeLiteral::GetValue()
{
    return m_value;
}


#pragma mark - TypeToString Implementation

std::string AST::TypeToString(Type type)
{
    switch (type)
    {
        case tTypeFloat:
            return "float";
        break;

        case tTypeInt:
            return "int";
        break;

        case tTypeBool:
            return "bool";
        break;

        case tTypeVoid:
            return "void";
        break;

        default:
            assert(false && "Unknown type in TypeToString()");
        break;
    }
    
    return "Unknown";
}


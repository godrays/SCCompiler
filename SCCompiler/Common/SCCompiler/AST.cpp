//
//  AST.cpp
//
//  Created by Arkin Terli on 4/10/18.
//  Copyright © 2018 Arkin Terli. All rights reserved.
//

#include <cassert>

#include "AST.hpp"

using namespace SCCompiler;


#pragma mark - Node Implementation

AST::Node::~Node()
{
    // Delete all childs.
    for (auto child : m_childs)
    {
        delete child;
    }
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


#pragma mark - NodeAOP Implementation

AST::NodeAOP::NodeAOP(AST::NodeType nodeType) : AST::Node(nodeType)
{
    assert(nodeType == AST::NodeType::tNodeTypeAOPMul
        || nodeType == AST::NodeType::tNodeTypeAOPDiv
        || nodeType == AST::NodeType::tNodeTypeAOPAdd
        || nodeType == AST::NodeType::tNodeTypeAOPSub);
}


#pragma mark - NodeValue Implementation

AST::NodeLiteral::NodeLiteral(AST::NodeType nodeType, std::string value) :
    AST::Node(nodeType),
    m_value(value)
{
    assert(nodeType == AST::NodeType::tNodeTypeLiteralFloat
        || nodeType == AST::NodeType::tNodeTypeLiteralInt32
        || nodeType == AST::NodeType::tNodeTypeLiteralBool
        || nodeType == AST::NodeType::tNodeTypeLiteralID);
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

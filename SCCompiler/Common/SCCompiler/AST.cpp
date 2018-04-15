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

        case tTypeUserDefined:
            return "user defined";
        break;

        default:
            assert(false && "Unknown type in TypeToString()");
        break;
    }
    
    return "Unknown";
}

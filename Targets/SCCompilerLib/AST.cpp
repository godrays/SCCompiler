//
//  Created by Arkin Terli on 4/10/18.
//  Copyright © 2018-Present, Arkin Terli. All rights reserved.
//

// Project includes
#include "AST.hpp"
// External includes
// System includes
#include <cassert>
#include <utility>


using namespace scc;


ast::FuncArg::FuncArg(Type type, std::string name) : m_type(type), m_name(std::move(name))
{

}


Type ast::FuncArg::getType()
{
    return m_type;
}


std::string ast::FuncArg::getName()
{
    return m_name;
}


ast::Node::Node(NodeType nodeType) : m_nodeType(nodeType)
{

}


ast::Node::~Node()
{
    deleteChildren();
}


void ast::Node::deleteChildren()
{
    // Delete all children.
    for (auto child : m_children)
    {
        delete child;
    }

    m_children.clear();
}


void ast::Node::addChild(ast::Node * childNode)
{
    m_children.emplace_back(childNode);
}


size_t ast::Node::childCount()
{
    return m_children.size();
}


ast::Node * ast::Node::getChild(size_t index)
{
    assert(index < m_children.size());
    return m_children[index];
}


void ast::Node::setParent(ast::Node * parentNode)
{
    m_parent = parentNode;
}


ast::Node * ast::Node::getParent()
{
    return m_parent;
}

ast::NodeType  ast::Node::getNodeType()
{
    return m_nodeType;
}

void ast::Node::setSourceCodeLine(size_t lineNumber)
{
    m_lineNumber = lineNumber;
}

size_t ast::Node::getSourceCodeLine() const
{
    return m_lineNumber;
}


std::string ast::Node::getNodeTypeInString(ast::NodeType nodeType)
{
    std::string typeInString;

    switch (nodeType)
    {
        case ast::NodeType::kProgram:
            typeInString = "tNodeTypeProgram";
            break;

        case ast::NodeType::kAOPAdd:
            typeInString = "tNodeTypeAOPAdd";
            break;

        case ast::NodeType::kAOPDiv:
            typeInString = "tNodeTypeAOPDiv";
            break;

        case ast::NodeType::kAOPMul:
            typeInString = "tNodeTypeAOPMul";
            break;

        case ast::NodeType::kAOPSub:
            typeInString = "tNodeTypeAOPSub";
            break;

        case ast::NodeType::kAssignment:
            typeInString = "tNodeTypeAssignment";
            break;

        case ast::NodeType::kBlock:
            typeInString = "tNodeTypeBlock";
            break;

        case ast::NodeType::kFuncCall:
            typeInString = "tNodeTypeFuncCall";
            break;

        case ast::NodeType::kFunctionDeclaration:
            typeInString = "tNodeTypeFunctionDeclaration";
            break;

        case ast::NodeType::kIfStatement:
            typeInString = "tNodeTypeIfStatement";
            break;

        case ast::NodeType::kForStatement:
            typeInString = "tNodeTypeForStatement";
            break;

        case ast::NodeType::kForVarDecl:
            typeInString = "kForVarDecl";
            break;

        case ast::NodeType::kForCondition:
            typeInString = "kForCondition";
            break;

        case ast::NodeType::kForIncrement:
            typeInString = "kForIncrement";
            break;

        case ast::NodeType::kWhileStatement:
            typeInString = "tNodeTypeWhileStatement";
            break;

        case ast::NodeType::kDoWhileStatement:
            typeInString = "tNodeTypeDoWhileStatement";
            break;

        case ast::NodeType::kLiteralBool:
            typeInString = "tNodeTypeLiteralBool";
            break;

        case ast::NodeType::kLiteralFloat:
            typeInString = "tNodeTypeLiteralFloat";
            break;

        case ast::NodeType::kLiteralID:
            typeInString = "tNodeTypeLiteralID";
            break;

        case ast::NodeType::kLiteralInt32:
            typeInString = "tNodeTypeLiteralInt32";
            break;

        case ast::NodeType::kReturnStatement:
            typeInString = "tNodeTypeReturnStatement";
            break;

        case ast::NodeType::kContinue:
            typeInString = "kContinue";
            break;

        case ast::NodeType::kBreak:
            typeInString = "kBreak";
            break;

        case ast::NodeType::kUnknown:
            typeInString = "tNodeTypeReturnStatement";
            break;

        case ast::NodeType::kVariableDeclaration:
            typeInString = "tNodeTypeVariableDeclaration";
            break;

        case ast::NodeType::kExplicitTypeConversion:
            typeInString = "kExplicitTypeConversion";
            break;

        case ast::NodeType::kLogicalNotOP:
            typeInString = "kLogicalNotOP";
            break;

        case ast::NodeType::kLogicalAndOP:
            typeInString = "kLogicalAndOP";
            break;

        case ast::NodeType::kLogicalOrOP:
            typeInString = "kLogicalOrOP";
            break;

        case ast::NodeType::kUOPPlus:
            typeInString = "kUOPPlus";
            break;

        case ast::NodeType::kUOPMinus:
            typeInString = "kUOPMinus";
            break;

        case ast::NodeType::kCompOPEQ:
            typeInString = "kCompOPEQ";
            break;

        case ast::NodeType::kCompOPNEQ:
            typeInString = "kCompOPNEQ";
            break;

        case ast::NodeType::kCompOPLE:
            typeInString = "kCompOPLE";
            break;

        case ast::NodeType::kCompOPGE:
            typeInString = "kCompOPGE";
            break;

        case ast::NodeType::kCompOPL:
            typeInString = "kCompOPL";
            break;

        case ast::NodeType::kCompOPG:
            typeInString = "kCompOPG";
            break;

        default:
            assert(false && "Unknown node type in Node::getNodeTypeInString()");
            break;
    }

    return typeInString;
}


ast::Node * ast::Node::findClosestParentNode(const std::vector<ast::NodeType> & nodeTypes)
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
        return m_parent->findClosestParentNode(nodeTypes);
    }

    return nullptr;
}


ast::Node * ast::Node::findClosestChildNode(ast::NodeType nodeType)
{
    if (m_nodeType == nodeType)
    {
        return this;
    }

    for (const auto & m_child : m_children)
    {
        auto foundNode = m_child->findClosestChildNode(nodeType);

        if (foundNode)
        {
            return foundNode;
        }
    }

    return nullptr;
}


void ast::Node::setScope(ScopeNode * scope)
{
    m_scope = scope;
}


ScopeNode * ast::Node::getScope()
{
    return m_scope;
}


ast::NodeProgram::NodeProgram()
{
    m_nodeType = NodeType::kProgram;
}


ast::NodeProgram::~NodeProgram()
{
    deleteChildren();
}


ast::NodeVarDeclaration::NodeVarDeclaration(Type type, std::string varName) :
    ast::Node(NodeType::kVariableDeclaration)
{
    m_varType = type;
    m_varName = std::move(varName);
}


ast::NodeVarDeclaration::~NodeVarDeclaration()
{
    deleteChildren();
}


Type ast::NodeVarDeclaration::GetVarType()
{
    return m_varType;
}


std::string ast::NodeVarDeclaration::GetVarName()
{
    return m_varName;
}


ast::NodeFuncDeclaration::NodeFuncDeclaration(Type returnType, std::string funcName) :
    ast::Node(NodeType::kFunctionDeclaration)
{
    m_returnType = returnType;
    m_funcName = std::move(funcName);
}


ast::NodeFuncDeclaration::~NodeFuncDeclaration()
{
    deleteChildren();
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


ast::NodeIfStatement::NodeIfStatement() : ast::Node(NodeType::kIfStatement)
{

}


ast::NodeIfStatement::~NodeIfStatement()
{
    deleteChildren();
}


ast::NodeForStatement::NodeForStatement() : ast::Node(NodeType::kForStatement)
{

}


ast::NodeForStatement::~NodeForStatement()
{
    deleteChildren();
}


ast::NodeFor::NodeFor(ast::NodeType nodeType) : Node(nodeType)
{

}


ast::NodeFor::~NodeFor()
{
    deleteChildren();
}


ast::NodeWhileStatement::NodeWhileStatement() : ast::Node(NodeType::kWhileStatement)
{

}


ast::NodeWhileStatement::~NodeWhileStatement()
{
    deleteChildren();
}


ast::NodeDoWhileStatement::NodeDoWhileStatement() : ast::Node(NodeType::kDoWhileStatement)
{

}


ast::NodeDoWhileStatement::~NodeDoWhileStatement()
{
    deleteChildren();
}


ast::NodeReturnStatement::NodeReturnStatement() : ast::Node(NodeType::kReturnStatement)
{

}


ast::NodeReturnStatement::~NodeReturnStatement()
{
    deleteChildren();
}


ast::NodeContinue::NodeContinue() : ast::Node(NodeType::kContinue)
{

}


ast::NodeContinue::~NodeContinue()
{
    deleteChildren();
}


ast::NodeBreak::NodeBreak() : ast::Node(NodeType::kBreak)
{

}


ast::NodeBreak::~NodeBreak()
{
    deleteChildren();
}


ast::NodeFuncCall::NodeFuncCall(std::string funcName)  : ast::Node(NodeType::kFuncCall)
{
    m_funcName = std::move(funcName);
}

ast::NodeFuncCall::~NodeFuncCall()
{
    deleteChildren();
}

std::string ast::NodeFuncCall::GetFuncName()
{
    return m_funcName;
}


ast::NodeBlock::NodeBlock()
{
    m_nodeType = NodeType::kBlock;
}


// Destructor.
ast::NodeBlock::~NodeBlock()
{
    deleteChildren();
}


ast::NodeAssignment::NodeAssignment() : Node(NodeType::kAssignment)
{

}


ast::NodeAssignment::~NodeAssignment()
{
    deleteChildren();
}


ast::NodeExplicitTypeConversion::NodeExplicitTypeConversion(Type conversionType) :
    Node(NodeType::kExplicitTypeConversion),
    m_conversionType(conversionType)
{

}


Type ast::NodeExplicitTypeConversion::GetConversionType()
{
    return m_conversionType;
}


ast::NodeExplicitTypeConversion::~NodeExplicitTypeConversion()
{
    deleteChildren();
}


ast::NodeLogicalOP::NodeLogicalOP(ast::NodeType nodeType) : Node(nodeType)
{
    assert(nodeType == ast::NodeType::kLogicalNotOP
        || nodeType == ast::NodeType::kLogicalAndOP
        || nodeType == ast::NodeType::kLogicalOrOP);
}


ast::NodeLogicalOP::~NodeLogicalOP()
{
    deleteChildren();
}


ast::NodeUnaryOP::NodeUnaryOP(NodeType nodeType) : Node(nodeType)
{
    assert(nodeType == ast::NodeType::kUOPPlus
        || nodeType == ast::NodeType::kUOPMinus);
}


ast::NodeUnaryOP::~NodeUnaryOP()
{
    deleteChildren();
}


ast::NodeCompOP::NodeCompOP(ast::NodeType nodeType) : ast::Node(nodeType)
{
    assert(nodeType == ast::NodeType::kCompOPEQ
        || nodeType == ast::NodeType::kCompOPNEQ
        || nodeType == ast::NodeType::kCompOPLE
        || nodeType == ast::NodeType::kCompOPGE
        || nodeType == ast::NodeType::kCompOPL
        || nodeType == ast::NodeType::kCompOPG);
}


ast::NodeCompOP::~NodeCompOP()
{
    deleteChildren();
}


ast::NodeAOP::NodeAOP(ast::NodeType nodeType) : ast::Node(nodeType)
{
    assert(nodeType == ast::NodeType::kAOPMul
        || nodeType == ast::NodeType::kAOPDiv
        || nodeType == ast::NodeType::kAOPAdd
        || nodeType == ast::NodeType::kAOPSub);
}


ast::NodeAOP::~NodeAOP()
{
    deleteChildren();
}


ast::NodePrefixAOP::NodePrefixAOP(ast::NodeType nodeType) : ast::Node(nodeType)
{
    assert(nodeType == ast::NodeType::kPrefixIncAOP
        || nodeType == ast::NodeType::kPrefixDecAOP);
}


ast::NodePrefixAOP::~NodePrefixAOP()
{
    deleteChildren();
}


ast::NodeLiteral::NodeLiteral(ast::NodeType nodeType, std::string value) :
    ast::Node(nodeType),
    m_value(std::move(value))
{
    assert(nodeType == ast::NodeType::kLiteralFloat
        || nodeType == ast::NodeType::kLiteralInt32
        || nodeType == ast::NodeType::kLiteralBool
        || nodeType == ast::NodeType::kLiteralID);
}


ast::NodeLiteral::~NodeLiteral()
{
    deleteChildren();
}


std::string ast::NodeLiteral::GetValue()
{
    return m_value;
}


std::string ast::TypeToString(Type type)
{
    switch (type)
    {
        case kTypeFloat:
            return "float";

        case kTypeInt:
            return "int";

        case kTypeBool:
            return "bool";

        case kTypeVoid:
            return "void";

        default:
            assert(false && "Unknown type in TypeToString()");
            break;
    }
    
    return "Unknown";
}


//
//  AST.hpp
//
//  Created by Arkin Terli on 4/10/18.
//  Copyright © 2018 Arkin Terli. All rights reserved.
//

#pragma once

#include <cassert>
#include <vector>
#include <string>


namespace SCCompiler
{

namespace AST
{

    // Node types for AST tree.
    enum NodeType : uint32_t
    {
        tNodeTypeUnknown,
        tNodeTypeProgram,
        tNodeTypeVariableDeclaration,
        tNodeTypeFunctionDeclaration,
        tNodeTypeIfStatement,
        tNodeTypeReturnStatement,
        tNodeTypeFuncCall,
        tNodeTypeBlock,
        tNodeTypeAssignment,
        tNodeTypeAOPMul,
        tNodeTypeAOPDiv,
        tNodeTypeAOPAdd,
        tNodeTypeAOPSub,
        tNodeTypeLiteralFloat,
        tNodeTypeLiteralInt32,
        tNodeTypeLiteralBool,
        tNodeTypeLiteralID,
    };


    // Language types.
    enum Type : uint32_t
    {
        tTypeUnknown,
        tTypeFloat,
        tTypeInt,
        tTypeBool,
        tTypeVoid,
        tTypeUserDefined,
    };


    #pragma mark - Class FuncArg

    // Class for function argument.
    class FuncArg
    {
    public:
        // Constructor.
        FuncArg(Type type, std::string name) : m_type(type), m_name(name) { }

        // Returns argument type.
        Type GetType()   { return m_type; }

        // Returns argument name.
        std::string GetName()   { return m_name; }

    protected:
        // Stores argument type.
        Type   m_type;

        // Stores argumen name.
        std::string   m_name;
    };


    #pragma mark - Class Node

    class Node
    {
    public:
        // Constructor
        Node() { }

        // Destructor
        virtual ~Node();

        // Adds child node.
        void    AddChild(Node * childNode)      { m_childs.emplace_back(childNode); m_parent = this; }

        // Returns childs' count.
        size_t  ChildCount()                    { return m_childs.size(); }

        // Returns child at given index.
        Node *  GetChild(size_t index)          { return m_childs[index]; }

        // Sets parent node.
        void    SetParent(Node * parentNode)    {  m_parent = parentNode; }

        // Returns parent node.
        Node *  GetParent()                     {  return m_parent; }

        // Returns node type.
        NodeType  GetNodeType()                 {  return m_nodeType; }

    protected:
        Node(NodeType nodeType) : m_nodeType(nodeType) { }

        // Node Type
        NodeType    m_nodeType = tNodeTypeUnknown;

        // Points parent node.
        Node *   m_parent = nullptr;

        // Stores child nodes.
        std::vector<Node *>   m_childs;
    };


    #pragma mark - Class NodeProgram

    class NodeProgram : public Node
    {
    public:
        // Constructor.
        NodeProgram()   { m_nodeType = tNodeTypeProgram; }

        // Destructor.
        virtual ~NodeProgram() { }
    };


    #pragma mark - Class NodeVarDeclaration

    class NodeVarDeclaration : public Node
    {
    public:
        // Constructor.
        NodeVarDeclaration(Type type, std::string varName) : Node(tNodeTypeVariableDeclaration) { m_varType = type; m_varName = varName; }

        // Destructor.
        virtual ~NodeVarDeclaration() { }

        // Get var type.
        Type GetVarType()      { return m_varType; }

        // Get var name.
        std::string GetVarName()      { return m_varName; }

    protected:
        Type         m_varType = Type::tTypeUnknown;
        std::string  m_varName;
    };


    #pragma mark - Class NodeFuncDeclaration

    class NodeFuncDeclaration : public Node
    {
    public:
        // Constructor.
        NodeFuncDeclaration(Type returnType, std::string funcName) : Node(tNodeTypeFunctionDeclaration) { m_returnType = returnType; m_funcName = funcName; }

        // Destructor.
        virtual ~NodeFuncDeclaration() { }

        // Get func name.
        std::string GetFuncName()      { return m_funcName; }

        // Get return type.
        Type GetReturnType()    { return m_returnType; }

        // Add argument.
        void AddArgument(FuncArg argument)  { m_argumentList.emplace_back(argument); }

        // Return argument list.
        std::vector<FuncArg> GetArguments()  { return m_argumentList; }

    protected:
        Type   m_returnType = Type::tTypeUnknown;
        std::string   m_funcName;
        std::vector<FuncArg>   m_argumentList;
    };


    #pragma mark - Class NodeIfStatement

    class NodeIfStatement : public Node
    {
    public:
        // Constructor.
        NodeIfStatement() : Node(tNodeTypeIfStatement) { }

        // Destructor.
        ~NodeIfStatement() { }
    };


    #pragma mark - Class NodeReturnStatement

    class NodeReturnStatement : public Node
    {
    public:
        // Constructor.
        NodeReturnStatement() : Node(tNodeTypeReturnStatement) { }

        // Destructor.
        virtual ~NodeReturnStatement() { }
    };


    #pragma mark - Class NodeFuncCall

    class NodeFuncCall : public Node
    {
    public:
        // Constructor.
        NodeFuncCall(std::string funcName)  : Node(tNodeTypeFuncCall) { m_funcName = funcName; }

        // Destructor.
        virtual ~NodeFuncCall() { }

        // Returns function name.
        std::string GetFuncName()       { return m_funcName; }

    protected:
        std::string m_funcName;
    };


    #pragma mark - Class NodeBlock

    class NodeBlock : public Node
    {
    public:
        // Constructor.
        NodeBlock()   { m_nodeType = tNodeTypeBlock; }

        // Destructor.
        virtual ~NodeBlock() { }
    };


    #pragma mark - Class NodeAssignment

    class NodeAssignment : public Node
    {
    public:
        // Constructor.
        NodeAssignment() : Node(tNodeTypeAssignment) { }

        // Destructor.
        virtual ~NodeAssignment() { }
    };


    #pragma mark - Class NodeAOP

    class NodeAOP : public Node
    {
    public:
        // Constructor.
        explicit NodeAOP(NodeType nodeType);

        // Destructor.
        virtual ~NodeAOP() { }
    };


    #pragma mark - Class NodeLiteral

    class NodeLiteral : public Node
    {
    public:
        // Constructor.
        NodeLiteral(AST::NodeType nodeType, std::string value);

        // Destructor.
        virtual ~NodeLiteral() { }
        
        // Get literal value.
        std::string GetValue()      { return m_value; }
        
    protected:
        // Literal value.
        std::string m_value;
    };


    #pragma mark - Function TypeToString

    std::string TypeToString(Type type);
}

}

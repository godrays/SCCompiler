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

#include "Types.hpp"


namespace SCC
{
    // Forward declaration.
    class ScopeNode;
    
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


    #pragma mark - Class FuncArg

    // Class for function argument.
    class FuncArg
    {
    public:
        // Constructor.
        FuncArg(Type type, std::string name);

        // Returns argument type.
        Type GetType();

        // Returns argument name.
        std::string GetName();

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
        Node();

        // Destructor
        virtual ~Node();

        // Adds child node.
        void    AddChild(Node * childNode);

        // Returns childs' count.
        size_t  ChildCount();

        // Returns child at given index.
        Node *  GetChild(size_t index);

        // Sets parent node.
        void    SetParent(Node * parentNode);

        // Returns parent node.
        Node *  GetParent();

        // Returns node type.
        NodeType  GetNodeType();

        // Return node type in string.
        std::string GetNodeTypeInString(AST::NodeType nodeType);

        // Set scope.
        void SetScope(ScopeNode * scope);

        // Get scope.
        ScopeNode * GetScope();

        // Set source code line.
        void  SetSourceCodeLine(size_t lineNumber);

        // Get source code line.
        size_t  GetSourceCodeLine();

        // Finds the closest parent node with given type in path from current node to tree root node.
        Node * FindClosestParentNode(NodeType nodeType);

        // Finds the closest child node with given type in path from current node to childs.
        Node * FindClosestChildNode(NodeType nodeType);

    protected:
        Node(NodeType nodeType);

        // Delete all child nodes.
        void DeleteChilds();

        // Node Type
        NodeType    m_nodeType = tNodeTypeUnknown;

        // Points parent node.
        Node *   m_parent = nullptr;

        // Stores child nodes.
        std::vector<Node *>   m_childs;
        
        // Pointer to the scope. Each AST node should know which scope are they in.
        ScopeNode *     m_scope;
        
        // Source code line of the node.
        size_t  m_lineNumber;
    };


    #pragma mark - Class NodeProgram

    class NodeProgram : public Node
    {
    public:
        // Constructor.
        NodeProgram();

        // Destructor.
        virtual ~NodeProgram();
    };


    #pragma mark - Class NodeVarDeclaration

    class NodeVarDeclaration : public Node
    {
    public:
        // Constructor.
        NodeVarDeclaration(Type type, std::string varName);

        // Destructor.
        virtual ~NodeVarDeclaration();

        // Get var type.
        Type GetVarType();

        // Get var name.
        std::string GetVarName();

    protected:
        Type         m_varType = Type::tTypeUnknown;
        std::string  m_varName;
    };


    #pragma mark - Class NodeFuncDeclaration

    class NodeFuncDeclaration : public Node
    {
    public:
        // Constructor.
        NodeFuncDeclaration(Type returnType, std::string funcName);

        // Destructor.
        virtual ~NodeFuncDeclaration();

        // Get func name.
        std::string GetFuncName();

        // Get return type.
        Type GetReturnType();

        // Add argument.
        void AddArgument(FuncArg argument);

        // Return argument list.
        std::vector<FuncArg> GetArguments();

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
        NodeIfStatement();

        // Destructor.
        virtual ~NodeIfStatement();
    };


    #pragma mark - Class NodeReturnStatement

    class NodeReturnStatement : public Node
    {
    public:
        // Constructor.
        NodeReturnStatement();

        // Destructor.
        virtual ~NodeReturnStatement();
    };


    #pragma mark - Class NodeFuncCall

    class NodeFuncCall : public Node
    {
    public:
        // Constructor.
        NodeFuncCall(std::string funcName);

        // Destructor.
        virtual ~NodeFuncCall();

        // Returns function name.
        std::string GetFuncName();

    protected:
        std::string m_funcName;
    };


    #pragma mark - Class NodeBlock

    class NodeBlock : public Node
    {
    public:
        // Constructor.
        NodeBlock();

        // Destructor.
        virtual ~NodeBlock();
    };


    #pragma mark - Class NodeAssignment

    class NodeAssignment : public Node
    {
    public:
        // Constructor.
        NodeAssignment();

        // Destructor.
        virtual ~NodeAssignment();
    };


    #pragma mark - Class NodeAOP

    class NodeAOP : public Node
    {
    public:
        // Constructor.
        explicit NodeAOP(NodeType nodeType);

        // Destructor.
        virtual ~NodeAOP();
    };


    #pragma mark - Class NodeLiteral

    class NodeLiteral : public Node
    {
    public:
        // Constructor.
        NodeLiteral(AST::NodeType nodeType, std::string value);

        // Destructor.
        virtual ~NodeLiteral();
        
        // Get literal value.
        std::string GetValue();
        
    protected:
        // Literal value.
        std::string m_value;
    };


    #pragma mark - Function TypeToString

    std::string TypeToString(Type type);
}

}

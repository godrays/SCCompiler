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


namespace scc
{

    // Forward declaration.
    class ScopeNode;
    
namespace ast
{

    #pragma mark - Enum NodeType

    // Node types for AST tree.
    enum NodeType : uint32_t
    {
        kNodeTypeUnknown,
        kNodeTypeProgram,
        kNodeTypeVariableDeclaration,
        kNodeTypeFunctionDeclaration,
        kNodeTypeIfStatement,
        kNodeTypeForStatement,
        kNodeTypeForVarDecl,
        kNodeTypeForCondition,
        kNodeTypeForIncrement,
        kNodeTypeWhileStatement,
        kNodeTypeDoWhileStatement,
        kNodeTypeReturnStatement,
        kNodeTypeContinue,
        kNodeTypeBreak,
        kNodeTypeFuncCall,
        kNodeTypeBlock,
        kNodeTypeAssignment,
        kNodeTypeExplicitTypeConversion,
        kNodeTypeLogicalNotOP,
        kNodeTypeUOPPlus,
        kNodeTypeUOPMinus,
        kNodeTypeAOPMul,
        kNodeTypeAOPDiv,
        kNodeTypeAOPAdd,
        kNodeTypeAOPSub,
        kNodeTypeCompOPEQ,
        kNodeTypeCompOPNEQ,
        kNodeTypeCompOPLE,
        kNodeTypeCompOPGE,
        kNodeTypeCompOPL,
        kNodeTypeCompOPG,
        kNodeTypeLiteralFloat,
        kNodeTypeLiteralInt32,
        kNodeTypeLiteralBool,
        kNodeTypeLiteralID,
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
        std::string GetNodeTypeInString(ast::NodeType nodeType);

        // Set scope.
        void SetScope(ScopeNode * scope);

        // Get scope.
        ScopeNode * GetScope();

        // Set source code line.
        void  SetSourceCodeLine(size_t lineNumber);

        // Get source code line.
        size_t  GetSourceCodeLine();

        // Finds the closest parent node with given type in path from current node to tree root node.
        Node * FindClosestParentNode(const std::vector<NodeType> & nodeType);

        // Finds the closest child node with given type in path from current node to childs.
        Node * FindClosestChildNode(NodeType nodeType);

    protected:
        Node(NodeType nodeType);

        // Delete all child nodes.
        void DeleteChilds();

        // Node Type
        NodeType    m_nodeType = kNodeTypeUnknown;

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
        Type         m_varType = Type::kTypeUnknown;
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
        Type   m_returnType = Type::kTypeUnknown;
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


    #pragma mark - Class NodeForStatement

    class NodeForStatement : public Node
    {
    public:
        // Constructor.
        NodeForStatement();

        // Destructor.
        virtual ~NodeForStatement();
    };


    #pragma mark - Class NodeFor

    class NodeFor : public Node
    {
    public:
        // Constructor.
        NodeFor(ast::NodeType nodeType);

        // Destructor.
        virtual ~NodeFor();
    };


    #pragma mark - Class NodeWhileStatement

    class NodeWhileStatement : public Node
    {
    public:
        // Constructor.
        NodeWhileStatement();

        // Destructor.
        virtual ~NodeWhileStatement();
    };


    #pragma mark - Class NodeDoWhileStatement

    class NodeDoWhileStatement : public Node
    {
    public:
        // Constructor.
        NodeDoWhileStatement();

        // Destructor.
        virtual ~NodeDoWhileStatement();
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


    #pragma mark - Class NodeContinue

    class NodeContinue : public Node
    {
    public:
        // Constructor.
        NodeContinue();

        // Destructor.
        virtual ~NodeContinue();
    };


    #pragma mark - Class NodeBreak

    class NodeBreak : public Node
    {
    public:
        // Constructor.
        NodeBreak();

        // Destructor.
        virtual ~NodeBreak();
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


    #pragma mark - Class NodeExplicitTypeConversion

    class NodeExplicitTypeConversion : public Node
    {
    public:
        // Constructor.
        NodeExplicitTypeConversion(Type conversionType);

        // Destructor.
        virtual ~NodeExplicitTypeConversion();
        
        // Get explicit conversion type.
        Type GetConversionType();
        
    protected:
        // ConversionType.
        Type m_conversionType;
    };


    #pragma mark - Class NodeLogicalNotOP

    class NodeLogicalNotOP : public Node
    {
    public:
        // Constructor.
        NodeLogicalNotOP();

        // Destructor.
        virtual ~NodeLogicalNotOP();
    };


    #pragma mark - Class NodeUnaryOP

    class NodeUnaryOP : public Node
    {
    public:
        // Constructor.
        explicit NodeUnaryOP(NodeType nodeType);

        // Destructor.
        virtual ~NodeUnaryOP();
    };


    #pragma mark - Class NodeCompOP

    class NodeCompOP : public Node
    {
    public:
        // Constructor.
        explicit NodeCompOP(NodeType nodeType);

        // Destructor.
        virtual ~NodeCompOP();
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
        NodeLiteral(ast::NodeType nodeType, std::string value);

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

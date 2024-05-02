//
//  Created by Arkin Terli on 4/10/18.
//  Copyright © 2018-Present, Arkin Terli. All rights reserved.
//

#pragma once

// Project includes
#include "Types.hpp"
// External includes
// System includes
#include <cassert>
#include <string>
#include <vector>


namespace scc
{

// Forward declaration.
class ScopeNode;
    
namespace ast
{

#pragma mark - Enum NodeType

// Node types for AST tree.
enum class NodeType
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
    kNodeTypeLogicalAndOP,
    kNodeTypeLogicalOrOP,
    kNodeTypeUOPPlus,
    kNodeTypeUOPMinus,
    kNodeTypePrefixIncAOP,
    kNodeTypePrefixDecAOP,
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

    // Stores argument name.
    std::string   m_name;
};


#pragma mark - Class Node

class Node
{
public:
    // Constructor
    Node() = default;

    // Destructor
    virtual ~Node();

    // Adds child node.
    void    AddChild(Node * childNode);

    // Returns children's count.
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
    size_t  GetSourceCodeLine() const;

    // Finds the closest parent node with the given type in the path from the current node to the tree root node.
    Node * FindClosestParentNode(const std::vector<NodeType> & nodeType);

    // Finds the closest child node with the given type in the path from the current node to its children.
    Node * FindClosestChildNode(NodeType nodeType);

protected:
    explicit Node(NodeType nodeType);

    // Delete all child nodes.
    void DeleteChildren();

    // Node Type
    NodeType    m_nodeType{NodeType::kNodeTypeUnknown};

    // Points parent node.
    Node *   m_parent{nullptr};

    // Stores child nodes.
    std::vector<Node *>   m_children;

    // Pointer to the scope. Each AST node should know which scope it is in.
    ScopeNode *     m_scope{nullptr};

    // Source code line of the node.
    size_t  m_lineNumber{0};
};


#pragma mark - Class NodeProgram

class NodeProgram : public Node
{
public:
    // Constructor.
    NodeProgram();

    // Destructor.
    ~NodeProgram() override;
};


#pragma mark - Class NodeVarDeclaration

class NodeVarDeclaration : public Node
{
public:
    // Constructor.
    NodeVarDeclaration(Type type, std::string varName);

    // Destructor.
    ~NodeVarDeclaration() override;

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
    ~NodeFuncDeclaration() override;

    // Get func name.
    std::string GetFuncName();

    // Get return type.
    Type GetReturnType();

    // Add argument.
    void AddArgument(const FuncArg& argument);

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
    ~NodeIfStatement() override;
};


#pragma mark - Class NodeForStatement

class NodeForStatement : public Node
{
public:
    // Constructor.
    NodeForStatement();

    // Destructor.
    ~NodeForStatement() override;
};


#pragma mark - Class NodeFor

class NodeFor : public Node
{
public:
    // Constructor.
    explicit NodeFor(ast::NodeType nodeType);

    // Destructor.
    ~NodeFor() override;
};


#pragma mark - Class NodeWhileStatement

class NodeWhileStatement : public Node
{
public:
    // Constructor.
    NodeWhileStatement();

    // Destructor.
    ~NodeWhileStatement() override;
};


#pragma mark - Class NodeDoWhileStatement

class NodeDoWhileStatement : public Node
{
public:
    // Constructor.
    NodeDoWhileStatement();

    // Destructor.
    ~NodeDoWhileStatement() override;
};


#pragma mark - Class NodeReturnStatement

class NodeReturnStatement : public Node
{
public:
    // Constructor.
    NodeReturnStatement();

    // Destructor.
    ~NodeReturnStatement() override;
};


#pragma mark - Class NodeContinue

class NodeContinue : public Node
{
public:
    // Constructor.
    NodeContinue();

    // Destructor.
    ~NodeContinue() override;
};


#pragma mark - Class NodeBreak

class NodeBreak : public Node
{
public:
    // Constructor.
    NodeBreak();

    // Destructor.
    ~NodeBreak() override;
};


#pragma mark - Class NodeFuncCall

class NodeFuncCall : public Node
{
public:
    // Constructor.
    explicit NodeFuncCall(std::string funcName);

    // Destructor.
    ~NodeFuncCall() override;

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
    ~NodeBlock() override;
};


#pragma mark - Class NodeAssignment

class NodeAssignment : public Node
{
public:
    // Constructor.
    NodeAssignment();

    // Destructor.
    ~NodeAssignment() override;
};


#pragma mark - Class NodeExplicitTypeConversion

class NodeExplicitTypeConversion : public Node
{
public:
    // Constructor.
    explicit NodeExplicitTypeConversion(Type conversionType);

    // Destructor.
    ~NodeExplicitTypeConversion() override;

    // Get explicit conversion type.
    Type GetConversionType();

protected:
    // ConversionType.
    Type m_conversionType;
};


#pragma mark - Class NodeLogicalOP

class NodeLogicalOP : public Node
{
public:
    // Constructor.
    explicit NodeLogicalOP(ast::NodeType nodetype);

    // Destructor.
    ~NodeLogicalOP() override;
};


#pragma mark - Class NodeUnaryOP

class NodeUnaryOP : public Node
{
public:
    // Constructor.
    explicit NodeUnaryOP(NodeType nodeType);

    // Destructor.
    ~NodeUnaryOP() override;
};


#pragma mark - Class NodeCompOP

class NodeCompOP : public Node
{
public:
    // Constructor.
    explicit NodeCompOP(NodeType nodeType);

    // Destructor.
    ~NodeCompOP() override;
};


#pragma mark - Class NodePrefixAOP

class NodePrefixAOP : public Node
{
public:
    // Constructor.
    explicit NodePrefixAOP(NodeType nodeType);

    // Destructor.
    ~NodePrefixAOP() override;
};


#pragma mark - Class NodeAOP

class NodeAOP : public Node
{
public:
    // Constructor.
    explicit NodeAOP(NodeType nodeType);

    // Destructor.
    ~NodeAOP() override;
};


#pragma mark - Class NodeLiteral

class NodeLiteral : public Node
{
public:
    // Constructor.
    NodeLiteral(ast::NodeType nodeType, std::string value);

    // Destructor.
    ~NodeLiteral() override;

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

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
#include <memory>
#include <string>
#include <vector>


namespace scc
{

// Forward declaration.
class ScopeNode;
    
namespace ast
{

// Node types for AST tree.
enum class NodeType
{
    kUnknown,
    kProgram,
    kVariableDeclaration,
    kFunctionDeclaration,
    kIfStatement,
    kForStatement,
    kForVarDecl,
    kForCondition,
    kForIncrement,
    kWhileStatement,
    kDoWhileStatement,
    kReturnStatement,
    kContinue,
    kBreak,
    kFunctionCall,
    kBlock,
    kAssignment,
    kExplicitTypeConversion,
    kLogicalNotOP,
    kLogicalAndOP,
    kLogicalOrOP,
    kUOPPlus,
    kUOPMinus,
    kPrefixIncAOP,
    kPrefixDecAOP,
    kAOPMul,
    kAOPDiv,
    kAOPAdd,
    kAOPSub,
    kCompOPEQ,
    kCompOPNEQ,
    kCompOPLE,
    kCompOPGE,
    kCompOPL,
    kCompOPG,
    kLiteralFloat,
    kLiteralInt32,
    kLiteralBool,
    kLiteralID,
};


// Class for function argument.
class FunctionArgument
{
public:
    // Constructor.
    FunctionArgument(Type type, std::string name);

    // Returns argument type.
    Type getType();

    // Returns argument name.
    std::string getName();

protected:
    Type   m_type;          // Stores argument type.
    std::string   m_name;   // Stores argument name.
};


class Node
{
public:
    // Constructor
    Node() = default;

    // Destructor
    virtual ~Node();

    // Adds child node.
    void    addChild(std::unique_ptr<Node> childNode);

    // Returns children's count.
    size_t  childCount();

    // Returns child at given index.
    Node *  getChild(size_t index);

    // Sets parent node.
    void    setParent(Node * parentNode);

    // Returns parent node.
    Node *  getParent();

    // Returns node type.
    NodeType  getNodeType();

    // Return node type in string.
    std::string getNodeTypeInString(ast::NodeType nodeType);

    // Set scope.
    void setScope(ScopeNode * scope);

    // Get scope.
    ScopeNode * getScope();

    // Set source code line.
    void  setSourceCodeLine(size_t lineNumber);

    // Get source code line.
    size_t  getSourceCodeLine() const;

    // Finds the closest parent node with the given type in the path from the current node to the tree root node.
    Node * findClosestParentNode(const std::vector<NodeType> & nodeType);

    // Finds the closest child node with the given type in the path from the current node to its children.
    Node * findClosestChildNode(NodeType nodeType);

protected:
    explicit Node(NodeType nodeType);

    // Delete all child nodes.
    void deleteChildren();

    // Node Type
    NodeType    m_nodeType{NodeType::kUnknown};

    // Points parent node.
    Node *   m_parent{nullptr};

    // Stores child nodes.
    std::vector<std::unique_ptr<Node>>   m_children;

    // Pointer to the scope. Each AST node should know which scope it is in.
    ScopeNode *     m_scope{nullptr};

    // Source code line of the node.
    size_t  m_lineNumber{0};
};


class NodeProgram : public Node
{
public:
    // Constructor.
    NodeProgram();

    // Destructor.
    ~NodeProgram() override;
};


class NodeVariableDeclaration : public Node
{
public:
    // Constructor.
    NodeVariableDeclaration(Type type, std::string varName);

    // Destructor.
    ~NodeVariableDeclaration() override;

    // Get var type.
    Type getVarType();

    // Get var name.
    std::string getVarName();

protected:
    Type         m_varType = Type::kTypeUnknown;
    std::string  m_varName;
};


class NodeFunctionDeclaration : public Node
{
public:
    // Constructor.
    NodeFunctionDeclaration(Type returnType, std::string funcName);

    // Destructor.
    ~NodeFunctionDeclaration() override;

    // Get func name.
    std::string getFuncName();

    // Get return type.
    Type getReturnType();

    // Add argument.
    void addArgument(const FunctionArgument & argument);

    // Return argument list.
    std::vector<FunctionArgument> getArguments();

protected:
    Type   m_returnType = Type::kTypeUnknown;
    std::string   m_funcName;
    std::vector<FunctionArgument>   m_argumentList;
};


class NodeIfStatement : public Node
{
public:
    // Constructor.
    NodeIfStatement();

    // Destructor.
    ~NodeIfStatement() override;
};


class NodeForStatement : public Node
{
public:
    // Constructor.
    NodeForStatement();

    // Destructor.
    ~NodeForStatement() override;
};


class NodeFor : public Node
{
public:
    // Constructor.
    explicit NodeFor(ast::NodeType nodeType);

    // Destructor.
    ~NodeFor() override;
};


class NodeWhileStatement : public Node
{
public:
    // Constructor.
    NodeWhileStatement();

    // Destructor.
    ~NodeWhileStatement() override;
};


class NodeDoWhileStatement : public Node
{
public:
    // Constructor.
    NodeDoWhileStatement();

    // Destructor.
    ~NodeDoWhileStatement() override;
};


class NodeReturnStatement : public Node
{
public:
    // Constructor.
    NodeReturnStatement();

    // Destructor.
    ~NodeReturnStatement() override;
};


class NodeContinue : public Node
{
public:
    // Constructor.
    NodeContinue();

    // Destructor.
    ~NodeContinue() override;
};


class NodeBreak : public Node
{
public:
    // Constructor.
    NodeBreak();

    // Destructor.
    ~NodeBreak() override;
};


class NodeFunctionCall : public Node
{
public:
    // Constructor.
    explicit NodeFunctionCall(std::string funcName);

    // Destructor.
    ~NodeFunctionCall() override;

    // Returns function name.
    std::string getFuncName();

protected:
    std::string m_funcName;
};


class NodeBlock : public Node
{
public:
    // Constructor.
    NodeBlock();

    // Destructor.
    ~NodeBlock() override;
};


class NodeAssignment : public Node
{
public:
    // Constructor.
    NodeAssignment();

    // Destructor.
    ~NodeAssignment() override;
};


class NodeExplicitTypeConversion : public Node
{
public:
    // Constructor.
    explicit NodeExplicitTypeConversion(Type conversionType);

    // Destructor.
    ~NodeExplicitTypeConversion() override;

    // Get explicit conversion type.
    Type getConversionType();

protected:
    // ConversionType.
    Type m_conversionType;
};


class NodeLogicalOP : public Node
{
public:
    // Constructor.
    explicit NodeLogicalOP(ast::NodeType nodetype);

    // Destructor.
    ~NodeLogicalOP() override;
};


class NodeUnaryOP : public Node
{
public:
    // Constructor.
    explicit NodeUnaryOP(NodeType nodeType);

    // Destructor.
    ~NodeUnaryOP() override;
};


class NodeCompOP : public Node
{
public:
    // Constructor.
    explicit NodeCompOP(NodeType nodeType);

    // Destructor.
    ~NodeCompOP() override;
};


class NodePrefixAOP : public Node
{
public:
    // Constructor.
    explicit NodePrefixAOP(NodeType nodeType);

    // Destructor.
    ~NodePrefixAOP() override;
};


class NodeAOP : public Node
{
public:
    // Constructor.
    explicit NodeAOP(NodeType nodeType);

    // Destructor.
    ~NodeAOP() override;
};


class NodeLiteral : public Node
{
public:
    // Constructor.
    NodeLiteral(ast::NodeType nodeType, std::string value);

    // Destructor.
    ~NodeLiteral() override;

    // Get literal value.
    std::string getValue();

protected:
    // Literal value.
    std::string m_value;
};


std::string TypeToString(Type type);

}

}

//
//  Created by Arkin Terli on 4/22/18.
//  Copyright © 2018-Present, Arkin Terli. All rights reserved.
//

#pragma once

// Project includes
#include "Symbols.hpp"
// System includes
#include <memory>
#include <string>
#include <vector>


namespace llvm
{
    class BasicBlock;
    class Constant;
    class ConstantFolder;
    class Function;
    class GlobalVariable;
    class IRBuilderDefaultInserter;
    class LLVMContext;
    class Module;
    class Type;
    class Value;

    template <typename FolderTy, typename InserterTy>
    class IRBuilder;
}

namespace scc
{

class SCModule;

// Forward declaration.
namespace ast
{
    enum class NodeType : int;

    class Node;
    class NodeProgram;
    class NodeVariableDeclaration;
    class NodeFunctionDeclaration;
    class NodeIfStatement;
    class NodeForStatement;
    class NodeWhileStatement;
    class NodeDoWhileStatement;
    class NodeBlock;
    class NodeLogicalOperator;
    class NodeReturnStatement;
    class NodeContinue;
    class NodeBreak;
    class NodeFunctionCall;
    class NodeAssignment;
    class NodeExplicitTypeConversion;
    class NodePrefixArithmeticOperator;
    class NodeArithmeticOperator;
    class NodeComparisonOperator;
    class NodeUnaryOperator;
    class NodeLiteral;
}

using LLVMIRBuilder = llvm::IRBuilder<llvm::ConstantFolder, llvm::IRBuilderDefaultInserter>;


class SymbolProperty : public SymbolPropertyBase
{
public:
    // Constructors.
    SymbolProperty() = delete;
    explicit SymbolProperty(llvm::Value * value);

    // Returns pointer to llvm value.
    llvm::Value * getValue();

protected:
    // Pointer to llvm value.
    llvm::Value *  m_value;
};


class NodeBasicBlockSet final
{
public:
    // Constructor
    NodeBasicBlockSet(ast::Node * node,
                      llvm::BasicBlock * conditionBasicBlock,
                      llvm::BasicBlock * bodyBasicBlock,
                      llvm::BasicBlock * incrementBasicBlock,
                      llvm::BasicBlock * exitBasicBlock);

    // Return node.
    ast::Node * getNode();

    // Return condition basic block.
    llvm::BasicBlock * getConditionBasicBlock();

    // Return body basic block.
    llvm::BasicBlock * getBodyBasicBlock();

    // Return increment basic block.
    llvm::BasicBlock * getIncrementBasicBlock();

    // Return exit basic block.
    llvm::BasicBlock * getExitBasicBlock();

protected:
    ast::Node *  m_node;                            // AST Node.
    llvm::BasicBlock *  m_conditionBasicBlock;      // Condition basic block.
    llvm::BasicBlock *  m_bodyBasicBlock;           // Body basic block.
    llvm::BasicBlock *  m_incrementBasicBlock;      // Increment basic block.
    llvm::BasicBlock *  m_exitBasicBlock;           // Exit basic block.
};


class NodeBasicBlockSetStack final
{
public:
    // Pushes new element to stack.
    void push(std::unique_ptr<NodeBasicBlockSet> nodeBasicBlockSet);

    // Pops top element in stack.
    void pop();

    // Returns the basic block set if the node matches one of the given node types.
    NodeBasicBlockSet * getOneOfNodeTypes(const std::vector<ast::NodeType> & nodeTypes);

protected:
    // Node basic block stack. Using vector here to implement stack behavior since
    // std::stack implementation doesn't support iteration on its elements.
    std::vector<std::unique_ptr<NodeBasicBlockSet>>  m_nodeBasicBlockStack;
};


class  CodeGenPass
{
public:
    // Constructor.
    CodeGenPass();

    // Destructor.
    virtual ~CodeGenPass();

    // Performs semantic analysis on the AST nodes.
    std::unique_ptr<SCModule> generateCode(ast::Node * node);

private:
    // Visits all node children.
    void visitChildren(ast::Node * node);

    // Visits nodes to create scopes and define symbols.
    llvm::Value * visit(ast::Node * node);

    void visitProgram(ast::NodeProgram * node);

    void visitVariableDeclaration(ast::NodeVariableDeclaration * node);

    void visitFunctionDeclaration(ast::NodeFunctionDeclaration * node);

    void visitBlock(ast::NodeBlock * node);

    void visitIfStatement(ast::NodeIfStatement * node);

    void visitForStatement(ast::NodeForStatement * node);

    void visitWhileStatement(ast::NodeWhileStatement * node);

    void visitDoWhileStatement(ast::NodeDoWhileStatement * node);

    void visitReturnStatement(ast::NodeReturnStatement * node);

    void visitContinue(ast::NodeContinue * node);

    void visitBreak(ast::NodeBreak * node);

    void visitAssignment(ast::NodeAssignment * node);

    llvm::Value *  visitFunctionCall(ast::NodeFunctionCall * node);

    llvm::Value * visitExplicitTypeConversion(ast::NodeExplicitTypeConversion * node);

    llvm::Value * visitLogicalNotOperator(ast::NodeLogicalOperator * node);

    llvm::Value * visitLogicalAndOperator(ast::NodeLogicalOperator * node);

    llvm::Value * visitLogicalOrOperator(ast::NodeLogicalOperator * node);

    llvm::Value * visitPrefixArithmeticOperator(ast::NodePrefixArithmeticOperator * node);

    llvm::Value * visitArithmeticOperator(ast::NodeArithmeticOperator * node);

    llvm::Value * visitComparisonOperator(ast::NodeComparisonOperator * node);

    llvm::Value * visitUnaryOperator(ast::NodeUnaryOperator * node);

    llvm::Value * visitLiteral(ast::NodeLiteral * node);

private:
    // Creates an internal initializer function.
    void createInternalInitializerFunction();

    // Finalizes the internal initializer function.
    void finalizeInternalInitializerFunction();

    // Creates an LLVM base type (float, int, bool, etc.).
    llvm::Type * createBaseType(scc::Type type);

    // Creates an LLVM constant value.
    llvm::Constant * createConstant(scc::Type type, const std::string & value);

    // Creates a new global variable.
    llvm::GlobalVariable * createGlobalVariable(std::string name, scc::Type);

    // Creates a function.
    llvm::Function * createFunc(LLVMIRBuilder & Builder, scc::Type returnType, const std::string& Name, std::vector<llvm::Type *> & argTypes);

    // Creates a basic block.
    llvm::BasicBlock * createBasicBlock(llvm::Function * func, const std::string& name);

    // Loads the value if it is a pointer type.
    llvm::Value * loadIfPointerType(llvm::Value * value);

    // Dumps the LLVM IR of the module.
    void dumpIRCode() const;

    // Deletes unreachable blocks in the function's basic block list.
    void deleteUnreachableBasicBlocks(llvm::Function * function);

protected:
    std::unique_ptr<llvm::LLVMContext> m_context;       // LLVM context. NOTE: We need an LLVMContext per-thread context.
    std::unique_ptr<llvm::Module>  m_module;            // Stores the entire code.
    llvm::Function *  m_currentFunction{nullptr};       // Pointer to the current LLVM Function.
    llvm::Function *  m_initFunction{nullptr};          // Initializer function for global variables.
    llvm::BasicBlock *  m_initFunctionBlock{nullptr};   // Last used basic block in the initializer function.
    std::unique_ptr<LLVMIRBuilder> m_irBuilder;         // IR builder stack.
    NodeBasicBlockSetStack  m_nodeBasicBlockStack;      // Stores LLVM basic blocks.
};

}


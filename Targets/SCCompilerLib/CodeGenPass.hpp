//
//  Created by Arkin Terli on 4/22/18.
//  Copyright © 2018-Present, Arkin Terli. All rights reserved.
//

#pragma once

// Project includes
#include "AST.hpp"
#include "SCModule.hpp"
#include "Symbols.hpp"
// External includes
#include <llvm/ADT/STLExtras.h>
#include <llvm/ExecutionEngine/ExecutionEngine.h>
#include <llvm/ExecutionEngine/MCJIT.h>
#include <llvm/ExecutionEngine/GenericValue.h>
#include <llvm/IR/Argument.h>
#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Instructions.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/Verifier.h>
#include <llvm/Support/Casting.h>
#include <llvm/Support/ManagedStatic.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/Support/raw_ostream.h>
// System includes
#include <list>
#include <memory>
#include <vector>


namespace scc
{

// Forward declaration.
namespace ast
{
    class Node;
    class NodeProgram;
    class NodeVariableDeclaration;
    class NodeFunctionDeclaration;
    class NodeForStatement;
    class NodeWhileStatement;
    class NodeDoWhileStatement;
    class NodeBlock;
    class NodeLogicalOperator;
    class NodeReturnStatement;
    class NodeBreak;
    class NodeFunctionCall;
    class NodeAssignment;
    class NodePrefixArithmeticOperator;
    class NodeArithmeticOperator;
    class NodeLiteral;
}

class JITEngine;


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


class NodeBasicBlocks final
{
public:
    // Constructor
    NodeBasicBlocks(ast::Node * node,
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


class NodeBasicBlocksStack final
{
public:
    // Pushes new element to stack.
    void push(std::unique_ptr<NodeBasicBlocks> nodeBasicBlocks);

    // Pops top element in stack.
    void pop();

    // Returns NodeBasicBlocks object if node matches with given one of the node types.
    NodeBasicBlocks * getOneOfThese(const std::vector<ast::NodeType> & nodeTypes);

protected:
    // Node BasicBlock Stack. Using vector here to implement stack behavior since
    // std::stack implementation doesn't support iteration on its elements.
    std::vector<std::unique_ptr<NodeBasicBlocks>>  m_nodeBBStack;
};


class  CodeGenPass
{
public:
    // Constructor.
    CodeGenPass() = default;

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
    llvm::Function * createFunc(llvm::IRBuilder <> &Builder, scc::Type returnType, const std::string& Name, std::vector<llvm::Type *> & argTypes);

    // Creates a basic block.
    llvm::BasicBlock * createBasicBlock(llvm::Function * func, const std::string& name);

    // Loads the value if it is a pointer type.
    llvm::Value * loadIfPointerType(llvm::Value * value);

    // Dumps the LLVM IR of the module.
    void dumpIRCode() const;

    // Converts an LLVM type to a string.
    std::string debugLLVMTypeAsString(llvm::Type::TypeID typeID) const;

    // Deletes unreachable blocks in the function's basic block list.
    void deleteUnreachableBasicBlocks(llvm::Function * function);

protected:
    std::unique_ptr<llvm::LLVMContext> m_context;       // LLVM context. NOTE: We need an LLVMContext per-thread context.
    std::unique_ptr<llvm::Module>  m_module;            // Stores the entire code.
    llvm::Function *  m_currentFunction{nullptr};       // Pointer to the current LLVM Function.
    llvm::Function *  m_initFunction{nullptr};          // Initializer function for global variables.
    llvm::BasicBlock *  m_initFunctionBlock{nullptr};   // Last used basic block in the initializer function.
    std::unique_ptr<llvm::IRBuilder<>> m_irBuilder;     // IR builder stack.
    NodeBasicBlocksStack  m_nodeBBStack;                // Stores LLVM BasicBlocks.
};

}


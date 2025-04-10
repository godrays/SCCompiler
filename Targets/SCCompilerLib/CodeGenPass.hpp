//
//  Created by Arkin Terli on 4/22/18.
//  Copyright © 2018-Present, Arkin Terli. All rights reserved.
//

#pragma once

// Project includes
#include "AST.hpp"
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
#include <vector>


namespace scc
{

// Forward declaration.
namespace ast
{
    class Node;
    class NodeProgram;
    class NodeVarDeclaration;
    class NodeFuncDeclaration;
    class NodeForStatement;
    class NodeWhileStatement;
    class NodeDoWhileStatement;
    class NodeBlock;
    class NodeLogicalOP;
    class NodeReturnStatement;
    class NodeBreak;
    class NodeFuncCall;
    class NodeAssignment;
    class NodePrefixAOP;
    class NodeAOP;
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
    llvm::Value * GetValue();

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
    ast::Node * GetNode();

    // Return condition basic block.
    llvm::BasicBlock * GetConditionBasicBlock();

    // Return body basic block.
    llvm::BasicBlock * GetBodyBasicBlock();

    // Return increment basic block.
    llvm::BasicBlock * GetIncrementBasicBlock();

    // Return exit basic block.
    llvm::BasicBlock * GetExitBasicBlock();

protected:
    // AST Node.
    ast::Node *  m_node;

    // Condition basic block.
    llvm::BasicBlock *  m_conditionBasicBlock;

    // Body basic block.
    llvm::BasicBlock *  m_bodyBasicBlock;

    // Increment basic block.
    llvm::BasicBlock *  m_incrementBasicBlock;

    // Exit basic block.
    llvm::BasicBlock *  m_exitBasicBlock;
};


class NodeBasicBlocksStack final
{
public:
    // Destructor.
    ~NodeBasicBlocksStack();

    // Pushes new element to stack.
    void Push(NodeBasicBlocks * nodeBasicBlocks);

    // Pops and deletes top element in stack.
    void PopAndDelete();

    // Returns NodeBasicBlocks object if node matches with given one of the node types.
    NodeBasicBlocks * GetOneOfThese(const std::vector<ast::NodeType> & nodeTypes);

protected:
    // Node BasicBlock Stack. Using vector here to implement stack behavior since
    // std::stack implementation doesn't support iteration on its elements.
    std::vector<NodeBasicBlocks *>  m_nodeBBStack;
};


class  CodeGenPass
{
public:
    // Constructor.
    CodeGenPass() = default;

    // Destructor.
    virtual ~CodeGenPass();

    // Performs semantic analysis on the AST nodes.
    JITEngine * GenerateCode(ast::Node * node);

private:
    // Visits all node children.
    void VisitChildren(ast::Node * node);

    // Visits nodes to create scopes and define symbols.
    llvm::Value * Visit(ast::Node * node);

    void VisitProgram(ast::NodeProgram * node);

    void VisitVariableDeclaration(ast::NodeVarDeclaration * node);

    void VisitFunctionDeclaration(ast::NodeFuncDeclaration * node);

    void VisitBlock(ast::NodeBlock * node);

    void VisitIfStatement(ast::NodeIfStatement * node);

    void VisitForStatement(ast::NodeForStatement * node);

    void VisitWhileStatement(ast::NodeWhileStatement * node);

    void VisitDoWhileStatement(ast::NodeDoWhileStatement * node);

    void VisitReturnStatement(ast::NodeReturnStatement * node);

    void VisitContinue(ast::NodeContinue * node);

    void VisitBreak(ast::NodeBreak * node);

    void VisitAssignment(ast::NodeAssignment * node);

    llvm::Value *  VisitFunctionCall(ast::NodeFuncCall * node);

    llvm::Value * VisitExplicitTypeConversion(ast::NodeExplicitTypeConversion * node);

    llvm::Value * VisitLogicalNotOP(ast::NodeLogicalOP * node);

    llvm::Value * VisitLogicalAndOP(ast::NodeLogicalOP * node);

    llvm::Value * VisitLogicalOrOP(ast::NodeLogicalOP * node);

    llvm::Value * VisitPrefixAOP(ast::NodePrefixAOP * node);

    llvm::Value * VisitAOP(ast::NodeAOP * node);

    llvm::Value * VisitCompOP(ast::NodeCompOP * node);

    llvm::Value * VisitNodeUnaryOP(ast::NodeUnaryOP * node);

    llvm::Value * VisitLiteral(ast::NodeLiteral * node);

private:
    // Creates an internal initializer function.
    void CreateInternalInitializerFunction();

    // Finalizes the internal initializer function.
    void FinalizeInternalInitializerFunction();

    // Creates an LLVM base type (float, int, bool, etc.).
    llvm::Type * CreateBaseType(scc::Type type);

    // Creates an LLVM constant value.
    llvm::Constant * CreateConstant(scc::Type type, const std::string & value);

    // Creates a new global variable.
    llvm::GlobalVariable * CreateGlobalVariable(std::string name, scc::Type);

    // Creates a function.
    llvm::Function * CreateFunc(llvm::IRBuilder <> &Builder, scc::Type returnType, const std::string& Name, std::vector<llvm::Type *> & argTypes);

    // Creates a basic block.
    llvm::BasicBlock * CreateBasicBlock(llvm::Function * func, const std::string& name);

    // Loads the value if it is a pointer type.
    llvm::Value * LoadIfPointerType(llvm::Value * value);

    // Dumps the LLVM IR of the module.
    void DumpIRCode() const;

    // Converts an LLVM type to a string.
    std::string DebugLLVMTypeAsString(llvm::Type::TypeID typeID) const;

    // Deletes unreachable blocks in the function's basic block list.
    void DeleteUnreachableBasicBlocks(llvm::Function * function);

protected:
    // Stores the entire code.
    std::unique_ptr<llvm::Module>  m_module;

    // LLVM context. NOTE: We need an LLVMContext per-thread context.
    llvm::LLVMContext * m_context{nullptr};

    // Pointer to the current LLVM Function.
    llvm::Function *  m_currentFunction{nullptr};

    // Initializer function for global variables.
    llvm::Function *  m_initFunction{nullptr};

    // Last used basic block in the initializer function.
    llvm::BasicBlock *  m_initFunctionBlock{nullptr};

    // IR builder stack.
    llvm::IRBuilder<> * m_irBuilder{nullptr};

    // Stores LLVM BasicBlocks.
    NodeBasicBlocksStack    m_nodeBBStack;
};

}


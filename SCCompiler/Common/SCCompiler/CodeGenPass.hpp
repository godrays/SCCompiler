//
//  CodeGenPass.hpp
//
//  Created by Arkin Terli on 4/22/18.
//  Copyright © 2018 Arkin Terli. All rights reserved.
//

#pragma once

#include <list>
#include <vector>

#include "llvm/IR/CFG.h"
#include "llvm/ADT/STLExtras.h"
#include "llvm/ExecutionEngine/ExecutionEngine.h"
#include "llvm/ExecutionEngine/MCJIT.h"
#include "llvm/ExecutionEngine/GenericValue.h"
#include "llvm/IR/Argument.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/Verifier.h"
#include "llvm/Support/Casting.h"
#include "llvm/Support/ManagedStatic.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/Support/raw_ostream.h"


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
        class NodeBlock;
        class NodeReturnStatement;
        class NodeFuncCall;
        class NodeAssignment;
        class NodeAOP;
        class NodeLiteral;
    }

    class JITEngine;


    #pragma mark - Class SymbolProperty

    class SymbolProperty : public SymbolPropertyBase
    {
    public:
        // Constructors.
        SymbolProperty() = delete;
        SymbolProperty(llvm::Value * value);

        // Returns pointer to llvm value.
        llvm::Value * GetValue();

    protected:
        // Pointer to llvm value.
        llvm::Value *  m_value;
    };


    #pragma mark - Class NodeBasicBlocks

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


    #pragma mark - Class NodeBasicBlocksStack

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
        // Node BsaicBlock Stack. Using vector here to implement stack behavior since
        // std::stack implementation doesn't support iteration on its elements.
        std::vector<NodeBasicBlocks *>  m_nodeBBStack;
    };


    #pragma mark - Class CodeGenPass

    class  CodeGenPass
    {
    public:
        // Constructor.
        CodeGenPass();
        
        // Destructor.
        virtual ~CodeGenPass();
        
        // Perform semantic analysis on nodes AST.
        JITEngine * GenerateCode(ast::Node * node);

    private:
        // Visits all node childs.
        void VisitChilds(ast::Node * node);

        // Visits nodes to create scopes and define symbols.
        llvm::Value * Visit(ast::Node * node);

        void VisitProgram(ast::NodeProgram * node);

        void VisitVariableDeclaration(ast::NodeVarDeclaration * node);

        void VisitFunctionDeclaration(ast::NodeFuncDeclaration * node);

        void VisitBlock(ast::NodeBlock * node);

        void VisitIfStatement(ast::NodeIfStatement * node);

        void VisitForStatement(ast::NodeForStatement * node);

        void VisitReturnStatement(ast::NodeReturnStatement * node);

        void VisitContinue(ast::NodeContinue * node);

        void VisitAssignment(ast::NodeAssignment * node);

        llvm::Value *  VisitFunctionCall(ast::NodeFuncCall * node);

        llvm::Value * VisitExplicitTypeConversion(ast::NodeExplicitTypeConversion * node);

        llvm::Value * VisitLogicalNotOP(ast::NodeLogicalNotOP * node);

        llvm::Value * VisitAOP(ast::NodeAOP * node);

        llvm::Value * VisitCompOP(ast::NodeCompOP * node);

        llvm::Value * VisitNodeUnaryOP(ast::NodeUnaryOP * node);

        llvm::Value * VisitLiteral(ast::NodeLiteral * node);
        
    private:
        // Create internal initializer function.
        void CreateInternalInitializerFunction();

        // Finalize internal initializer function.
        void FinalizeInternalInitializerFunction();

        // Creates LLVM base type. (float, int, bool etc..)
        llvm::Type * CreateBaseType(scc::Type type);

        // Creates LLVM constant value.
        llvm::Constant * CreateConstant(scc::Type type, const std::string & value);

        // Creates new global variable.
        llvm::GlobalVariable * CreateGlobalVariable(std::string name, scc::Type);

        // Create function.
        llvm::Function * CreateFunc(llvm::IRBuilder <> &Builder, scc::Type returnType, std::string Name, std::vector<llvm::Type *> & argTypes);

        // Create basic block.
        llvm::BasicBlock * CreateBasicBlock(llvm::Function * func, std::string name);

        // Loads if value is pointer type.
        llvm::Value * LoadIfPointerType(llvm::Value * value);

        // Dumps LLVM IR of the module.
        void DumpIRCode() const;

        // Convert llvm type to string.
        std::string DebugLLVMTypeAsString(llvm::Type::TypeID typeID) const;
        
        // Delete unreachable blocks in function basic block list.
        void DeleteUnreachableBasicBlocks(llvm::Function * function);

    protected:
        // Stores entire code.
        std::unique_ptr<llvm::Module>  m_module;

        // LLVM context. NOTE: We need LLVMContext per-thread context.
        llvm::LLVMContext * m_context;
        
        // Pointer to current LLVM Function.
        llvm::Function *  m_currentFunction;
        
        // Initializer function for global variables.
        llvm::Function *  m_initFunction;

        // IR builder stack
        llvm::IRBuilder<> * m_irBuilder;
        
        // Stores LLVM BasicBlocks.
        NodeBasicBlocksStack    m_nodeBBStack;
   };
}


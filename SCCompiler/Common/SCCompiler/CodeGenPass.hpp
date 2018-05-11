//
//  CodeGenPass.hpp
//
//  Created by Arkin Terli on 4/22/18.
//  Copyright © 2018 Arkin Terli. All rights reserved.
//

#pragma once

#include <list>

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


namespace SCC
{
    // Forward declaration.
    namespace AST
    {
        class Node;
        class NodeProgram;
        class NodeVarDeclaration;
        class NodeFuncDeclaration;
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


    #pragma mark - Class CodeGenPass

    class  CodeGenPass
    {
    public:
        // Constructor.
        CodeGenPass();
        
        // Destructor.
        virtual ~CodeGenPass();
        
        // Perform semantic analysis on nodes AST.
        JITEngine * GenerateCode(AST::Node * node);

    private:
        // Visits all node childs.
        void VisitChilds(AST::Node * node);

        // Visits nodes to create scopes and define symbols.
        llvm::Value * Visit(AST::Node * node);

        void VisitProgram(AST::NodeProgram * node);

        void VisitVariableDeclaration(AST::NodeVarDeclaration * node);

        void VisitFunctionDeclaration(AST::NodeFuncDeclaration * node);

        void VisitBlock(AST::NodeBlock * node);

        void VisitReturnStatement(AST::NodeReturnStatement * node);

        void VisitFunctionCall(AST::NodeFuncCall * node);
        
        void VisitAssignment(AST::NodeAssignment * node);

        llvm::Value * VisitAOP(AST::NodeAOP * node);

        llvm::Value * VisitLiteral(AST::NodeLiteral * node);
        
    private:
        // Creates LLVM base type. (float, int, bool etc..)
        llvm::Type * CreateBaseType(SCC::Type type);

        // Creates LLVM constant value.
        llvm::Constant * CreateConstant(SCC::Type type, const std::string & value);

        // Creates new global variable.
        llvm::GlobalVariable * CreateGlobalVariable(std::string name, SCC::Type, const std::string & value);

        // Create function.
        llvm::Function * CreateFunc(llvm::IRBuilder <> &Builder, SCC::Type returnType, std:: string Name, std::vector<llvm::Type *> & argTypes);

        // Create basic block.
        llvm::BasicBlock * CreateBasicBlock(llvm::Function * func, std:: string name);

        // Loads if value is pointer type.
        llvm::Value * LoadIfPointerType(llvm::Value * value);

        // Dumps LLVM IR of the module.
        void DumpIRCode() const;

        // Convert llvm type to string.
        std::string DebugLLVMTypeAsString(llvm::Type::TypeID typeID) const;

    protected:
        // Stores entire code.
        std::unique_ptr<llvm::Module>  m_module;

        // LLVM context. NOTE: We need LLVMContext per-thread context.
        llvm::LLVMContext * m_context;
        
        // Pointer to current LLVM Function.
        llvm::Function *  m_currentFunction;
        
        // IR builder stack
        llvm::IRBuilder<> * m_irBuilder;
   };
}

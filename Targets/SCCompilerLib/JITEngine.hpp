//
//  Created by Arkin Terli on 5/5/18.
//  Copyright © 2018-Present, Arkin Terli. All rights reserved.
//

#pragma once

// Project includes
#include "SCModule.hpp"
// External includes
#include <llvm/ADT/STLExtras.h>
#include <llvm/Analysis/Passes.h>
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
#include <unordered_map>
#include <stack>
#include <string>


namespace scc
{

// Machine code execution engine.
// NOTE: JITEngine must keep minimum data during its life cycle to minimize memory usage.
class JITEngine final : public SCModule
{
public:
    // Constructor.
    explicit JITEngine(std::unique_ptr<llvm::Module> module);

    // Destructor.
    ~JITEngine() final;

    // Get function pointer.
    void * getFunctionPtr(std::string name) final;

    // Run function.
    llvm::GenericValue runFunction(const std::string& funcName, std::vector<llvm::GenericValue> & args);

    // Reset and initialize global variables.
    void reset() final;

    // Optimize IR code.
    void optimizeIR();

protected:
    llvm::Module *  m_module{nullptr};                      // Pointer to program module object.
    llvm::ExecutionEngine * m_executionEngine{nullptr};     // Execution engine.
};

}

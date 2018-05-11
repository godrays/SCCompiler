//
//  JITEngine.hpp
//
//  Created by Arkin Terli on 5/5/18.
//  Copyright © 2018 Arkin Terli. All rights reserved.
//

#pragma once

#include <stack>
#include <unordered_map>
#include <string>

#include "llvm/ADT/STLExtras.h"
#include "llvm/Analysis/Passes.h"
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

#include "SCModule.hpp"


namespace SCCompiler
{
    #pragma mark - Class JITEngine

    // Machine code execution engine.
    // NOTE: JITEngine must keep minimum data during it's life cycle to minimize memory usage.
    class JITEngine : public SCModule
    {
    public:
        // Constructor.
        JITEngine(std::unique_ptr<llvm::Module> module);

        // Destructor.
        virtual ~JITEngine();
        
        // Get function pointer.
        void * GetFunctionPtr(std::string name);

        // Run function.
        llvm::GenericValue RunFunction(std::string funcName, std::vector<llvm::GenericValue> & args);

    protected:
        // Pointer to program module object.
        llvm::Module *  m_module;

        // Execution engine.
        llvm::ExecutionEngine * m_executionEngine;
    };

}

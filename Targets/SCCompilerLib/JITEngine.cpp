//
//  JITEngine.cpp
//
//  Created by Arkin Terli on 5/5/18.
//  Copyright © 2018 Arkin Terli. All rights reserved.
//

#include <sstream>

#include "llvm/Analysis/TargetTransformInfo.h"
#include "llvm/Bitcode/BitcodeWriterPass.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/IR/LegacyPassNameParser.h"
#include "llvm/LinkAllPasses.h"
#include "llvm/Transforms/IPO/PassManagerBuilder.h"

#include "Types.hpp"
#include "Exceptions.hpp"
#include "JITEngine.hpp"

using namespace scc;


#pragma mark - JITEngine Implementations

JITEngine::JITEngine(std::unique_ptr<llvm::Module> module)
{
    // Setup the host target and ensure that the target libraries are linked.
    llvm::InitializeNativeTarget();
    llvm::InitializeNativeTargetAsmPrinter();
    llvm::InitializeNativeTargetAsmParser();

    m_module = module.get();

    OptimizeIR();

    // DEBUG
    // llvm::outs() << "[OPTIMIZED] ----------------------------------------\n" << *m_module;

    std::string error;
    m_executionEngine = llvm::EngineBuilder(std::move(module)).setEngineKind(llvm::EngineKind::Kind::JIT).setErrorStr(&error).create();
    if (m_executionEngine == nullptr)
    {
        std::stringstream   message;
        message << "Could not create ExecutionEngine: " << error << std::endl;
        throw CompileErrorException(message.str());
    }

    // Ensure the module is fully processed and is usable.
    // This method has no effect for the interpeter.
    m_executionEngine->finalizeObject();
}


JITEngine::~JITEngine()
{
    delete m_executionEngine;
    //TODO: llvm::llvm_shutdown(); needs to be called per process one time only.
}


void * JITEngine::GetFunctionPtr(std::string name)
{
    // OLD WAY : auto funcPtr = m_executionEngine->getPointerToFunction(m_module->getFunction(name));
    void * funcPtr = reinterpret_cast<void *>(m_executionEngine->getFunctionAddress(name));
    assert(funcPtr != nullptr);
    return funcPtr;
}


llvm::GenericValue JITEngine::RunFunction(std::string funcName, std::vector<llvm::GenericValue> & args)
{
    auto func = m_executionEngine->FindFunctionNamed(funcName);
    auto returnVal = m_executionEngine->runFunction(func, args);

    return returnVal;
}


void JITEngine::Reset()
{
    using InitFuncType = void (*)();
    auto initFunc = reinterpret_cast<InitFuncType>(GetFunctionPtr("__initGlobalVariables__"));
    // Initialize global variables.
    initFunc();
}


void JITEngine::OptimizeIR()
{
    // Create a PassManager to hold and optimize the collection of passes we are about to build.
    llvm::legacy::PassManager Passes;

    // Add internal analysis passes from the target machine.
    Passes.add(createTargetTransformInfoWrapperPass(llvm::TargetIRAnalysis()));

    std::unique_ptr<llvm::legacy::FunctionPassManager> FPasses;
    FPasses.reset(new llvm::legacy::FunctionPassManager(m_module));
    FPasses->add(createTargetTransformInfoWrapperPass(llvm::TargetIRAnalysis()));
    // Verify that input is correct
    FPasses->add(llvm::createVerifierPass());
    
    // Add Optimization Passes
    unsigned int OptLevel = 3;
    unsigned int SizeLevel = 0;

    llvm::PassManagerBuilder Builder;
    Builder.OptLevel = OptLevel;
    Builder.SizeLevel = SizeLevel;
    Builder.Inliner = llvm::createFunctionInliningPass(OptLevel, SizeLevel, false);
    Builder.LoopVectorize = true;
    Builder.SLPVectorize = true;
    Builder.populateFunctionPassManager(*FPasses);
    Builder.populateModulePassManager(Passes);

    if (FPasses)
    {
        FPasses->doInitialization();
        for (llvm::Function &F : *m_module)
        {
            FPasses->run(F);
        }
        FPasses->doFinalization();
    }

    // Check that the module is well formed on completion of optimization.
    Passes.add(llvm::createVerifierPass());

    // Now that we have all of the passes ready, run them.
    Passes.run(*m_module);
}


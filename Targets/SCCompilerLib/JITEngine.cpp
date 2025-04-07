//
//  Created by Arkin Terli on 5/5/18.
//  Copyright © 2018-Present, Arkin Terli. All rights reserved.
//

// Project includes
#include "JITEngine.hpp"
#include "Exceptions.hpp"
#include "Utils.hpp"
// External includes
#include <llvm/Analysis/TargetTransformInfo.h>
#include <llvm/Bitcode/BitcodeWriterPass.h>
#include <llvm/IR/LegacyPassManager.h>
#include <llvm/LinkAllPasses.h>
#include <llvm/Transforms/IPO/PassManagerBuilder.h>
// System includes
#include <memory>
#include <sstream>


using namespace scc;


JITEngine::JITEngine(std::unique_ptr<llvm::Module> module)
{
    // Set up the host target and ensure that the target libraries are linked.
    llvm::InitializeNativeTarget();
    llvm::InitializeNativeTargetAsmPrinter();
    llvm::InitializeNativeTargetAsmParser();

    m_module = module.get();

    OptimizeIR();

    // DEBUG
    // llvm::outs() << "[OPTIMIZED] ----------------------------------------\n" << *m_module;

    std::string error;
    m_executionEngine = llvm::EngineBuilder(std::move(module)).setEngineKind(llvm::EngineKind::Kind::JIT).setErrorStr(&error).create();
    throw_if(m_executionEngine == nullptr,
             CompileErrorException("Could not create ExecutionEngine: ", error));

    // Ensure the module is fully processed and is usable.
    // This method has no effect for the interpreter.
    m_executionEngine->finalizeObject();
}


JITEngine::~JITEngine()
{
    delete m_executionEngine;
    //TODO: llvm::llvm_shutdown(); needs to be called per process only one time.
}


void * JITEngine::GetFunctionPtr(std::string name)
{
    // OLD WAY: auto funcPtr = m_executionEngine->getPointerToFunction(m_module->getFunction(name));
    void * funcPtr = reinterpret_cast<void *>(m_executionEngine->getFunctionAddress(name));
    assert(funcPtr != nullptr);
    return funcPtr;
}


llvm::GenericValue JITEngine::RunFunction(const std::string & funcName, std::vector<llvm::GenericValue> & args)
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
    FPasses = std::make_unique<llvm::legacy::FunctionPassManager>(m_module);
    FPasses->add(createTargetTransformInfoWrapperPass(llvm::TargetIRAnalysis()));
    // Verify that the input is correct.
    FPasses->add(llvm::createVerifierPass());

    // Add Optimization Passes.
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

    // Check that the module is well-formed on completion of optimization.
    Passes.add(llvm::createVerifierPass());

    // Now that we have all the passes ready, run them.
    Passes.run(*m_module);
}

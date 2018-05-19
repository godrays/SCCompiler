//
//  JITEngine.cpp
//
//  Created by Arkin Terli on 5/5/18.
//  Copyright © 2018 Arkin Terli. All rights reserved.
//

#include <sstream>

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
    llvm::llvm_shutdown();
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

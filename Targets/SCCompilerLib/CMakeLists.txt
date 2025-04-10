#
#  Copyright © 2018-Present, Arkin Terli. All rights reserved.
#

set(TARGET_NAME SCCompilerLib)

if (SCCOMPILER_BUILD_STATIC)
    set(SCCOMPILER_LIB_TYPE STATIC)
else()
    set(SCCOMPILER_LIB_TYPE SHARED)
    # Reduce the need for explicit dllexport markup, even in C++ classes on Windows.
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
endif()

add_library(${TARGET_NAME} ${SCCOMPILER_LIB_TYPE}
        AST.cpp
        ASTGenerator.cpp
        ASTVisualizer.cpp
        CodeGenPass.cpp
        Compiler.cpp
        Exceptions.cpp
        JITEngine.cpp
        SemanticPass.cpp
        SCCompiler.cpp
        SCModule.cpp
        Symbols.cpp
        SymbolDefPass.cpp
        Types.cpp
        Parser/SCCompilerBaseListener.cpp
        Parser/SCCompilerBaseVisitor.cpp
        Parser/SCCompilerLexer.cpp
        Parser/SCCompilerListener.cpp
        Parser/SCCompilerParser.cpp
        Parser/SCCompilerVisitor.cpp
        )

add_dependencies(${TARGET_NAME} antlr4_cpp antlr4_tool llvm_cpp)

target_compile_definitions(${TARGET_NAME} PUBLIC ANTLR4CPP_STATIC)

if(MSVC)
    target_link_libraries(${TARGET_NAME} PRIVATE antlr4-runtime-static)
else()
    target_link_libraries(${TARGET_NAME} PRIVATE antlr4-runtime)
endif()

# Run llvm/installed/bin/llvm-config --libs to dump list of libs to include here and keep the original order of the libs.
target_link_libraries(${TARGET_NAME} PRIVATE
        LLVMWindowsManifest LLVMXRay LLVMLibDriver LLVMDlltoolDriver LLVMCoverage LLVMLineEditor LLVMX86Disassembler
        LLVMX86AsmParser LLVMX86CodeGen LLVMX86Desc LLVMX86Info LLVMARMDisassembler LLVMARMAsmParser LLVMARMCodeGen
        LLVMARMDesc LLVMARMUtils LLVMARMInfo LLVMAArch64Disassembler LLVMAArch64AsmParser LLVMAArch64CodeGen
        LLVMAArch64Desc LLVMAArch64Utils LLVMAArch64Info LLVMOrcJIT LLVMMCJIT LLVMJITLink LLVMOrcTargetProcess
        LLVMOrcShared LLVMInterpreter LLVMExecutionEngine LLVMRuntimeDyld LLVMSymbolize LLVMDebugInfoPDB
        LLVMDebugInfoGSYM LLVMOption LLVMObjectYAML LLVMMCA LLVMMCDisassembler LLVMLTO LLVMPasses LLVMCFGuard
        LLVMCoroutines LLVMObjCARCOpts LLVMHelloNew LLVMipo LLVMVectorize LLVMLinker LLVMInstrumentation
        LLVMFrontendOpenMP LLVMFrontendOpenACC LLVMExtensions LLVMDWARFLinker LLVMGlobalISel LLVMMIRParser
        LLVMAsmPrinter LLVMDebugInfoDWARF LLVMSelectionDAG LLVMCodeGen LLVMIRReader LLVMAsmParser LLVMInterfaceStub
        LLVMFileCheck LLVMFuzzMutate LLVMTarget LLVMScalarOpts LLVMInstCombine LLVMAggressiveInstCombine
        LLVMTransformUtils LLVMBitWriter LLVMAnalysis LLVMProfileData LLVMObject LLVMTextAPI LLVMMCParser LLVMMC
        LLVMDebugInfoCodeView LLVMDebugInfoMSF LLVMBitReader LLVMCore LLVMRemarks LLVMBitstreamReader LLVMBinaryFormat
        LLVMTableGen LLVMSupport LLVMDemangle
        )

install(FILES SCCompiler.hpp SCModule.hpp DESTINATION include)
install(TARGETS ${TARGET_NAME} ARCHIVE DESTINATION lib)

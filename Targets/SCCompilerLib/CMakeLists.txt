#
#  Copyright © 2018-Present, Arkin Terli. All rights reserved.
#

set(SCCOMPILER_LIB_TYPE SHARED)
if (SCCOMPILER_BUILD_STATIC)
    set(SCCOMPILER_LIB_TYPE STATIC)
endif()

add_library(SCCompilerLib ${SCCOMPILER_LIB_TYPE}
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

# Run llvm/installed/bin/llvm-config --libs to dump list of libs to include here and keep the original order of the libs.
target_link_libraries(SCCompilerLib PRIVATE
        antlr4-runtime_s
        z
        pthread
        edit
        curses
        dl
        m
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
install(TARGETS SCCompilerLib ARCHIVE DESTINATION lib)

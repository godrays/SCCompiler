//
//  CodeGenPass.cpp
//
//  Created by Arkin Terli on 4/22/18.
//  Copyright © 2018 Arkin Terli. All rights reserved.
//

#include <cassert>
#include <stack>
#include <unordered_map>
#include <string>

#include "Types.hpp"
#include "Symbols.hpp"
#include "AST.hpp"
#include "Exceptions.hpp"
#include "CodeGenPass.hpp"

using namespace SCCompiler;


#pragma mark - SymbolProperty Implementations.

SymbolProperty::SymbolProperty(llvm::Value * value) :
    m_value(value)
{

}


llvm::Value * SymbolProperty::GetValue()
{
    return m_value;
}


#pragma mark - CodeGenPass Implementations.


CodeGenPass::CodeGenPass() :
    m_module(nullptr),
    m_currentFunction(nullptr),
    m_irBuilder(nullptr)
{
    // Setup the host target and ensure that the target libraries are linked.
    llvm::InitializeNativeTarget();
}


CodeGenPass::~CodeGenPass()
{
    llvm::llvm_shutdown();
}


void CodeGenPass::GenerateCode(AST::Node * node)
{
    m_module = new llvm::Module("Program", m_context);

    // Create new IRBuilder for global scope.
    m_irBuilder = new llvm::IRBuilder<>(m_context);

    Visit(node);
    
    DumpIRCode();
}


void CodeGenPass::VisitChilds(AST::Node * node)
{
    // Visit node children.
    for (size_t index=0; index<node->ChildCount(); ++index)
    {
        Visit(node->GetChild(index));
    }
}


llvm::Value * CodeGenPass::Visit(AST::Node * node)
{
    switch(node->GetNodeType())
    {
        case AST::NodeType::tNodeTypeProgram:
            VisitProgram(static_cast<AST::NodeProgram *>(node));
            break;

        case AST::NodeType::tNodeTypeVariableDeclaration:
            VisitVariableDeclaration(static_cast<AST::NodeVarDeclaration *>(node));
            break;

        case AST::NodeType::tNodeTypeFunctionDeclaration:
            VisitFunctionDeclaration(static_cast<AST::NodeFuncDeclaration *>(node));
            break;

        case AST::NodeType::tNodeTypeBlock:
            VisitBlock(static_cast<AST::NodeBlock *>(node));
            break;

        case AST::NodeType::tNodeTypeReturnStatement:
            VisitReturnStatement(static_cast<AST::NodeReturnStatement *>(node));
            break;

        case AST::NodeType::tNodeTypeFuncCall:
            VisitFunctionCall(static_cast<AST::NodeFuncCall *>(node));
            break;

        case AST::NodeType::tNodeTypeAssignment:
            VisitAssignment(static_cast<AST::NodeAssignment *>(node));
            break;

        case AST::NodeType::tNodeTypeAOPMul:
        case AST::NodeType::tNodeTypeAOPDiv:
        case AST::NodeType::tNodeTypeAOPAdd:
        case AST::NodeType::tNodeTypeAOPSub:
            return VisitAOP(static_cast<AST::NodeAOP *>(node));
            break;

        case AST::NodeType::tNodeTypeLiteralFloat:
        case AST::NodeType::tNodeTypeLiteralInt32:
        case AST::NodeType::tNodeTypeLiteralBool:
        case AST::NodeType::tNodeTypeLiteralID:
            return VisitLiteral(static_cast<AST::NodeLiteral *>(node));
            break;

        default:
            assert(false && "Unknown node type in SemanticPass.");
            break;
    }

    return nullptr;
}


void CodeGenPass::VisitProgram(AST::NodeProgram * node)
{
    // Visit childs
    VisitChilds(node);
}


void CodeGenPass::VisitVariableDeclaration(AST::NodeVarDeclaration * node)
{
    auto childCount = node->ChildCount();
    auto varName = node->GetVarName();
    assert(childCount < 2);

    // Create global variable if variable is in global scope.
    if (node->GetScope()->GetCategory() == ScopeCategory::cScopeCategoryGlobal)
    {
        // Create global variable if there is no initializer.
        if (childCount == 0)
        {
            auto globalVar = CreateGlobalVariable(varName, node->GetVarType(), "");
            node->GetScope()->ResolveSymbol(varName)->SetProperty(new SymbolProperty(globalVar));
        }
        else if (childCount == 1)
        {
            auto rightExprNode = node->GetChild(0);
            auto nodeType = rightExprNode->GetNodeType();
            // If expression is constant value.
            if (nodeType == AST::NodeType::tNodeTypeLiteralInt32 ||
                nodeType == AST::NodeType::tNodeTypeLiteralFloat ||
                nodeType == AST::NodeType::tNodeTypeLiteralBool  ||
                nodeType == AST::NodeType::tNodeTypeLiteralID)
            {
                auto literalNode = dynamic_cast<AST::NodeLiteral *>(rightExprNode);
                auto globalVar = CreateGlobalVariable(varName, node->GetVarType(), literalNode->GetValue());
                node->GetScope()->ResolveSymbol(varName)->SetProperty(new SymbolProperty(globalVar));
            }
            else
            {
                assert(false);
                // TODO: Generate initializer code in internal initializer function.
                Visit(rightExprNode);
            }
        }
    }
    else
    {
        // Create stack allocated local variable.
        auto localVar = m_irBuilder->CreateAlloca(CreateBaseType(node->GetVarType()), nullptr, varName.c_str());
        // Set symbol property to save new llvm variable object. Save related llvm objects in symbol object.
        // We save llvm object because everytime this variable is used, we need to access to it's llvm object.
        node->GetScope()->ResolveSymbol(varName)->SetProperty(new SymbolProperty(localVar));

        // If node has child then it needs to be evaluated and assigned to the new variable.
        if (childCount == 1)
        {
            // Generate code for right expression and get assignment value.
            auto rightExprValue = Visit(node->GetChild(0));
            // We load value from rightExprValue address and store at localVar address.
            m_irBuilder->CreateStore(LoadIfPointerType(rightExprValue), localVar);
        }
    }
}


void CodeGenPass::VisitFunctionDeclaration(AST::NodeFuncDeclaration * node)
{
    // Save current block.
    llvm::BasicBlock *  prevBlock = m_irBuilder->GetInsertBlock();

    auto funcName = node->GetFuncName();

    auto funcSymbol = static_cast<FunctionSymbol*>(node->GetScope()->ResolveSymbol(funcName));
    funcSymbol->SetProperty(new SymbolProperty(m_currentFunction));

    // Create function argument types.
    std::vector<llvm::Type *>  argTypes;
    for (size_t i=0; i<funcSymbol->ArgumentCount(); ++i)
    {
        argTypes.emplace_back(CreateBaseType(funcSymbol->GetArgumentSymbol(i)->GetType()));
    }
    
    // Create function with arguments.
    m_currentFunction = CreateFunc(*m_irBuilder, node->GetReturnType(), funcName, argTypes);

    // Create basic block for function.
    llvm::BasicBlock * funcBlock = CreateBasicBlock(m_currentFunction, "entry");
    m_irBuilder->SetInsertPoint(funcBlock);

    // CreateFunc() creates function arguments without names. We need to set argument names.
    size_t index = 0;
    for (auto argIt = m_currentFunction->arg_begin(); index < funcSymbol->ArgumentCount(); ++argIt, ++index)
    {
        auto funcArgSymbol = funcSymbol->GetArgumentSymbol(index);
        // argIt->setName(funcArgSymbol->GetName());

        // Program should be able to change function parameter in function body but not original function parameter value.
        // To allow this we need to create new local variables and copy argument values to new local vars and use it as func arguments.
        // This way program can't change original function parameter values.
        auto localFuncArgVar = m_irBuilder->CreateAlloca(CreateBaseType(funcArgSymbol->GetType()), nullptr, funcArgSymbol->GetName());
        m_irBuilder->CreateStore(argIt, localFuncArgVar);
        funcArgSymbol->SetProperty(new SymbolProperty(localFuncArgVar));
    }

    // Visit childs.
    VisitChilds(node);

    m_currentFunction = nullptr;
    m_irBuilder->SetInsertPoint(prevBlock);
}


void CodeGenPass::VisitBlock(AST::NodeBlock * node)
{
    // Visit childs
    VisitChilds(node);
}


void CodeGenPass::VisitReturnStatement(AST::NodeReturnStatement * node)
{
    // If there is no child then return void. Function return type is void.
    if (node->ChildCount() == 0)
    {
        m_irBuilder->CreateRet(nullptr);
        return;
    }

    // return <expression>
    auto exprValue = Visit(node->GetChild(0));
    m_irBuilder->CreateRet(exprValue);
}


void CodeGenPass::VisitFunctionCall(AST::NodeFuncCall * node)
{
    // Visit childs
    VisitChilds(node);
}


void CodeGenPass::VisitAssignment(AST::NodeAssignment * node)
{
    // Get variable llvm value
    auto variable = Visit(node->GetChild(0));

    // Generate code for right expression and get assignment value.
    auto rightExprValue = Visit(node->GetChild(1));

    //std::cout << "VarTypeID:" << DebugLLVMTypeAsString(variable->getType()->getTypeID()) << std::endl;
    //std::cout << "BRightTypeID:" << DebugLLVMTypeAsString(rightExprValue->getType()->getTypeID()) << std::endl;
    //std::cout << "ARightTypeID:" << DebugLLVMTypeAsString(LoadIfPointerType(rightExprValue)->getType()->getTypeID()) << std::endl;

    // We load value from rightExprValue address and store at localVar address.
    m_irBuilder->CreateStore(LoadIfPointerType(rightExprValue), variable);
}


llvm::Value * CodeGenPass::VisitAOP(AST::NodeAOP * node)
{
    llvm::Value * resultValue = nullptr;

    // Visit always return pointer to value so we need to load to get value from pointed address.
    auto leftOperandValue = LoadIfPointerType(Visit(node->GetChild(0)));
    auto rightOperandValue = LoadIfPointerType(Visit(node->GetChild(1)));

    //std::cout << "BeforeLeftTypeID:" << DebugLLVMTypeAsString(leftOperandValue->getType()->getTypeID()) << std::endl;
    //std::cout << "BeforeRightTypeID:" << DebugLLVMTypeAsString(rightOperandValue->getType()->getTypeID()) << std::endl;

    leftOperandValue = LoadIfPointerType(leftOperandValue);
    rightOperandValue = LoadIfPointerType(rightOperandValue);

    //std::cout << "AfterLeftTypeID:" << DebugLLVMTypeAsString(leftOperandValue->getType()->getTypeID()) << std::endl;
    //std::cout << "AfterRightTypeID:" << DebugLLVMTypeAsString(rightOperandValue->getType()->getTypeID()) << std::endl;

    // Type promotion should be done here.
    llvm::Type::TypeID leftOpTypeID = leftOperandValue->getType()->getTypeID();
    llvm::Type::TypeID rightOpTypeID = rightOperandValue->getType()->getTypeID();

    switch (node->GetNodeType())
    {
        case AST::NodeType::tNodeTypeAOPMul:
        resultValue = m_irBuilder->CreateMul(leftOperandValue, rightOperandValue, "multmp");
        break;

        case AST::NodeType::tNodeTypeAOPDiv:
        resultValue = m_irBuilder->CreateSDiv(leftOperandValue, rightOperandValue, "sdivtmp");
        break;

        case AST::NodeType::tNodeTypeAOPAdd:
        resultValue = m_irBuilder->CreateAdd(leftOperandValue, rightOperandValue, "addtmp");
        break;

        case AST::NodeType::tNodeTypeAOPSub:
        resultValue = m_irBuilder->CreateSub(leftOperandValue, rightOperandValue, "subtmp");
        break;

        default:
            assert(false && "Unknown node type");
        break;
    }

    //std::cout << "ResultTypeID:" << DebugLLVMTypeAsString(resultValue->getType()->getTypeID()) << std::endl;
    
    return resultValue;
}


llvm::Value * CodeGenPass::VisitLiteral(AST::NodeLiteral * node)
{
    llvm::Value * literalValue = nullptr;
    
    switch (node->GetNodeType())
    {
        case AST::NodeType::tNodeTypeLiteralFloat:
        {
            // We create temp local variable and assign constant value.
            auto localVar = m_irBuilder->CreateAlloca(CreateBaseType(SCCompiler::Type::tTypeFloat), nullptr, "_ci");
            // Since we store constant, we don't need to load value from an address.
            m_irBuilder->CreateStore(CreateConstant(SCCompiler::Type::tTypeFloat, node->GetValue()), localVar);
            // Returns pointer to local variable.
            literalValue = localVar;
        }
        break;
        
        case AST::NodeType::tNodeTypeLiteralInt32:
        {
            // We create temp local variable and assign constant value.
            auto localVar = m_irBuilder->CreateAlloca(CreateBaseType(SCCompiler::Type::tTypeInt), nullptr, "_cf");
            // Since we store constant, we don't need to load value from an address.
            m_irBuilder->CreateStore(CreateConstant(SCCompiler::Type::tTypeInt, node->GetValue()), localVar);
            // Returns pointer to local variable.
            literalValue = localVar;
        }
        break;
        
        case AST::NodeType::tNodeTypeLiteralBool:
        assert("Not Implemented");
        break;
        
        case AST::NodeType::tNodeTypeLiteralID:
        {
            // Return llvm value object of the variable, which is stored as symbol property in symbol object.
            // llvm object is referring to variable pointer. Needs to be loaded to access to value of the variable.
            auto symbol = node->GetScope()->ResolveSymbol(node->GetValue());
            literalValue = static_cast<SymbolProperty *>(symbol->GetProperty())->GetValue();
        }
        break;
        
        default:
            assert(false && "Unknown node type.");
        break;
    }

    return literalValue;
}


llvm::Type * CodeGenPass::CreateBaseType(SCCompiler::Type type)
{
    switch(type)
    {
        case SCCompiler::Type::tTypeInt:
            return m_irBuilder->getInt32Ty();
        break;

        case SCCompiler::Type::tTypeFloat:
            return m_irBuilder->getFloatTy();
        break;

        case SCCompiler::Type::tTypeVoid:
            return m_irBuilder->getVoidTy();
        break;

        default:
            assert(false && "Unknown type.");
        break;
    }

    return nullptr;
}


llvm::Constant * CodeGenPass::CreateConstant(SCCompiler::Type type, const std::string & value)
{
    assert(value.size() > 0);

    switch(type)
    {
        case SCCompiler::Type::tTypeInt:
            return llvm::ConstantInt::get(m_context, llvm::APInt(32, uint32_t(atoi(value.c_str())), true));
            break;

        case SCCompiler::Type::tTypeFloat:
            return llvm::ConstantFP::get(m_context, llvm::APFloat(float(atof(value.c_str()))));
            break;

        default:
            assert(false && "Unknown type.");
            break;
    }

    return nullptr;
}


llvm::GlobalVariable * CodeGenPass::CreateGlobalVariable(std::string name,
                                                         SCCompiler::Type type,
                                                         const std::string & value)
{
    m_module->getOrInsertGlobal(name, CreateBaseType(type));
    auto gVar = m_module->getNamedGlobal(name);
    gVar->setLinkage(llvm::GlobalValue::CommonLinkage);
    gVar->setAlignment(4);

    if (value.size() > 0)
    {
        gVar->setInitializer(CreateConstant(type, value));
    }
    return gVar;
}


llvm::Function * CodeGenPass::CreateFunc(llvm::IRBuilder <> & Builder,
                                         SCCompiler::Type returnType,
                                         std:: string name,
                                         std::vector<llvm::Type *> & argTypes)
{
    llvm::FunctionType * funcType = llvm::FunctionType::get(CreateBaseType(returnType), argTypes, false);
    llvm::Function * func = llvm::Function::Create(funcType, llvm::Function::ExternalLinkage, name, m_module);

    return func;
}


llvm::BasicBlock * CodeGenPass::CreateBasicBlock(llvm::Function * func, std::string name)
{
    return llvm::BasicBlock::Create(m_context, name, func);
}


llvm::Value * CodeGenPass::LoadIfPointerType(llvm::Value * value)
{
    if (value->getType()->getTypeID() == llvm::Type::PointerTyID)
    {
        return m_irBuilder->CreateLoad(value);
    }

    return value;
}


void CodeGenPass::DumpIRCode() const
{
    m_module->dump();
}

std::string CodeGenPass::DebugLLVMTypeAsString(llvm::Type::TypeID typeID) const
{
    switch (typeID)
    {
        case llvm::Type::VoidTyID:        ///<  0: type with no size
        return "VoidTyID";

        case llvm::Type::HalfTyID:        ///<  1: 16-bit floating point type
        return "HalfTyID";

        case llvm::Type::FloatTyID:       ///<  2: 32-bit floating point type
        return "FloatTyID";

        case llvm::Type::DoubleTyID:      ///<  3: 64-bit floating point type
        return "DoubleTyID";

        case llvm::Type::X86_FP80TyID:    ///<  4: 80-bit floating point type (X87)
        return "X86_FP80TyID";

        case llvm::Type::FP128TyID:       ///<  5: 128-bit floating point type (112-bit mantissa)
        return "FP128TyID";

        case llvm::Type::PPC_FP128TyID:   ///<  6: 128-bit floating point type (two 64-bits, PowerPC)
        return "PPC_FP128TyID";

        case llvm::Type::LabelTyID:       ///<  7: Labels
        return "LabelTyID";

        case llvm::Type::MetadataTyID:    ///<  8: Metadata
        return "MetadataTyID";

        case llvm::Type::X86_MMXTyID:     ///<  9: MMX vectors (64 bits, X86 specific)
        return "X86_MMXTyID";

        case llvm::Type::TokenTyID:       ///< 10: Tokens
        return "TokenTyID";

        // Derived types... see DerivedTypes.h file.
        // Make sure FirstDerivedTyID stays up to date!
        case llvm::Type::IntegerTyID:     ///< 11: Arbitrary bit width integers
        return "IntegerTyID";

        case llvm::Type::FunctionTyID:    ///< 12: Functions
        return "FunctionTyID";

        case llvm::Type::StructTyID:      ///< 13: Structures
        return "StructTyID";

        case llvm::Type::ArrayTyID:       ///< 14: Arrays
        return "ArrayTyID";

        case llvm::Type::PointerTyID:     ///< 15: Pointers
        return "PointerTyID";

        case llvm::Type::VectorTyID:      ///< 16: SIMD 'packed' format, or other vector type
        return "VectorTyID";

        default:
        assert("Unknown llvm typeID");
        break;
    }
}

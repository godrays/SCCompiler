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
#include "JITEngine.hpp"
#include "CodeGenPass.hpp"

using namespace scc;


#pragma mark - SymbolProperty Implementations.

SymbolProperty::SymbolProperty(llvm::Value * value) :
    m_value(value)
{

}


llvm::Value * SymbolProperty::GetValue()
{
    return m_value;
}


#pragma mark - NodeBasicBlocks Implementations.

NodeBasicBlocks::NodeBasicBlocks(ast::Node * node,
                llvm::BasicBlock * conditionBasicBlock,
                llvm::BasicBlock * bodyBasicBlock,
                llvm::BasicBlock * incrementBasicBlock,
                llvm::BasicBlock * exitBasicBlock)
    : m_node(node),
      m_conditionBasicBlock(conditionBasicBlock),
      m_bodyBasicBlock(bodyBasicBlock),
      m_incrementBasicBlock(incrementBasicBlock),
      m_exitBasicBlock(exitBasicBlock)
{

}


ast::Node * NodeBasicBlocks::GetNode()
{
    return m_node;
}


llvm::BasicBlock * NodeBasicBlocks::GetConditionBasicBlock()
{
    assert(m_conditionBasicBlock != nullptr && "No reason to use if it is nullptr.");
    return m_conditionBasicBlock;
}


llvm::BasicBlock * NodeBasicBlocks::GetBodyBasicBlock()
{
    assert(m_bodyBasicBlock != nullptr && "No reason to use if it is nullptr.");
    return m_bodyBasicBlock;
}


llvm::BasicBlock * NodeBasicBlocks::GetIncrementBasicBlock()
{
    assert(m_incrementBasicBlock != nullptr && "No reason to use if it is nullptr.");
    return m_incrementBasicBlock;
}


llvm::BasicBlock * NodeBasicBlocks::GetExitBasicBlock()
{
    assert(m_exitBasicBlock != nullptr && "No reason to use if it is nullptr.");
    return m_exitBasicBlock;
}


#pragma mark - NodeBasicBlocksStack Implementations.

NodeBasicBlocksStack::~NodeBasicBlocksStack()
{
    assert(m_nodeBBStack.size() == 0 && "Stack size has to be zero.");
    m_nodeBBStack.clear();
}


void NodeBasicBlocksStack::Push(NodeBasicBlocks * nodeBasicBlocks)
{
    assert(nodeBasicBlocks != nullptr);
    m_nodeBBStack.emplace_back(nodeBasicBlocks);
}


void NodeBasicBlocksStack::PopAndDelete()
{
    auto stackSize = m_nodeBBStack.size();
    assert(stackSize > 0);

    // Pop nodeBBs.
    auto nodeBBs = m_nodeBBStack[stackSize - 1];
    m_nodeBBStack.pop_back();

    // Delete.
    assert(nodeBBs != nullptr);
    delete nodeBBs;
}


NodeBasicBlocks * NodeBasicBlocksStack::GetOneOfThese(const std::vector<ast::NodeType> & nodeTypes)
{
    auto size = m_nodeBBStack.size();
    assert(size > 0);
    
    for (size_t index=0; index < size; ++index)
    {
        // If node type matches one of the given type then return it.
        for (size_t ntIndex=0; ntIndex < nodeTypes.size(); ++ntIndex)
        {
            auto nodeBasicBlocks = m_nodeBBStack[size-index-1];
            if (nodeBasicBlocks->GetNode()->GetNodeType() == nodeTypes[ntIndex])
            {
                return nodeBasicBlocks;
            }
        }
    }

    return nullptr;
}


#pragma mark - CodeGenPass Implementations.

CodeGenPass::CodeGenPass() :
    m_module(nullptr),
    m_context(nullptr),
    m_initFunction(nullptr),
    m_initFunctionBlock(nullptr),
    m_currentFunction(nullptr),
    m_irBuilder(nullptr)
{

}


CodeGenPass::~CodeGenPass()
{
    delete m_irBuilder;
}


JITEngine * CodeGenPass::GenerateCode(ast::Node * node)
{
    m_context = new llvm::LLVMContext();
    m_module = std::make_unique<llvm::Module>("Program", *m_context);

    // Create new IRBuilder for global scope.
    m_irBuilder = new llvm::IRBuilder<>(*m_context);

    CreateInternalInitializerFunction();

    Visit(node);

    FinalizeInternalInitializerFunction();

    // DEBUG
    // DumpIRCode();

    // Create JITEngine. Transfer ownership of m_module and m_context to JITEngine.
    return new JITEngine(std::move(m_module));
}


void CodeGenPass::VisitChilds(ast::Node * node)
{
    // Visit node children.
    for (size_t index=0; index<node->ChildCount(); ++index)
    {
        Visit(node->GetChild(index));
    }
}


llvm::Value * CodeGenPass::Visit(ast::Node * node)
{
    switch(node->GetNodeType())
    {
        case ast::NodeType::kNodeTypeProgram:
            VisitProgram(static_cast<ast::NodeProgram *>(node));
            break;

        case ast::NodeType::kNodeTypeVariableDeclaration:
            VisitVariableDeclaration(static_cast<ast::NodeVarDeclaration *>(node));
            break;

        case ast::NodeType::kNodeTypeFunctionDeclaration:
            VisitFunctionDeclaration(static_cast<ast::NodeFuncDeclaration *>(node));
            break;

        case ast::NodeType::kNodeTypeBlock:
            VisitBlock(static_cast<ast::NodeBlock *>(node));
            break;

        case ast::NodeType::kNodeTypeIfStatement:
            VisitIfStatement(static_cast<ast::NodeIfStatement *>(node));
            break;

        case ast::NodeType::kNodeTypeForStatement:
            VisitForStatement(static_cast<ast::NodeForStatement *>(node));
            break;

        case ast::NodeType::kNodeTypeForVarDecl:
        case ast::NodeType::kNodeTypeForIncrement:
            VisitChilds(node);
            break;

        case ast::NodeType::kNodeTypeWhileStatement:
            VisitWhileStatement(static_cast<ast::NodeWhileStatement *>(node));
            break;

        case ast::NodeType::kNodeTypeDoWhileStatement:
            VisitDoWhileStatement(static_cast<ast::NodeDoWhileStatement *>(node));
            break;

        case ast::NodeType::kNodeTypeReturnStatement:
            VisitReturnStatement(static_cast<ast::NodeReturnStatement *>(node));
            break;

        case ast::NodeType::kNodeTypeContinue:
            VisitContinue(static_cast<ast::NodeContinue *>(node));
            break;

        case ast::NodeType::kNodeTypeBreak:
            VisitBreak(static_cast<ast::NodeBreak *>(node));
            break;

        case ast::NodeType::kNodeTypeFuncCall:
            return VisitFunctionCall(static_cast<ast::NodeFuncCall *>(node));
            break;

        case ast::NodeType::kNodeTypeAssignment:
            VisitAssignment(static_cast<ast::NodeAssignment *>(node));
            break;

        case ast::NodeType::kNodeTypeExplicitTypeConversion:
            return VisitExplicitTypeConversion(static_cast<ast::NodeExplicitTypeConversion *>(node));
            break;

        case ast::NodeType::kNodeTypeLogicalNotOP:
            return VisitLogicalNotOP(static_cast<ast::NodeLogicalOP *>(node));
            break;

        case ast::NodeType::kNodeTypeLogicalAndOP:
            return VisitLogicalAndOP(static_cast<ast::NodeLogicalOP *>(node));
            break;

        case ast::NodeType::kNodeTypeLogicalOrOP:
            return VisitLogicalOrOP(static_cast<ast::NodeLogicalOP *>(node));
            break;

        case ast::NodeType::kNodeTypeUOPMinus:
        case ast::NodeType::kNodeTypeUOPPlus:
            return VisitNodeUnaryOP(static_cast<ast::NodeUnaryOP *>(node));
            break;

        case ast::NodeType::kNodeTypeCompOPEQ:
        case ast::NodeType::kNodeTypeCompOPNEQ:
        case ast::NodeType::kNodeTypeCompOPLE:
        case ast::NodeType::kNodeTypeCompOPGE:
        case ast::NodeType::kNodeTypeCompOPL:
        case ast::NodeType::kNodeTypeCompOPG:
            return VisitCompOP(static_cast<ast::NodeCompOP *>(node));
            break;

        case ast::NodeType::kNodeTypeAOPMul:
        case ast::NodeType::kNodeTypeAOPDiv:
        case ast::NodeType::kNodeTypeAOPAdd:
        case ast::NodeType::kNodeTypeAOPSub:
            return VisitAOP(static_cast<ast::NodeAOP *>(node));
            break;

        case ast::NodeType::kNodeTypeLiteralFloat:
        case ast::NodeType::kNodeTypeLiteralInt32:
        case ast::NodeType::kNodeTypeLiteralBool:
        case ast::NodeType::kNodeTypeLiteralID:
            return VisitLiteral(static_cast<ast::NodeLiteral *>(node));
            break;

        case ast::NodeType::kNodeTypeForCondition:
            assert(false && "VisitForStatement() must manage this node implicitly.");
            break;

        default:
            assert(false && "Unknown node type in SemanticPass.");
            break;
    }

    return nullptr;
}


void CodeGenPass::VisitProgram(ast::NodeProgram * node)
{
    // Visit childs
    VisitChilds(node);
}


void CodeGenPass::VisitVariableDeclaration(ast::NodeVarDeclaration * node)
{
    auto childCount = node->ChildCount();
    auto varName = node->GetVarName();
    assert(childCount < 2);

    // Create global variable if variable is in global scope.
    if (node->GetScope()->GetCategory() == ScopeCategory::kScopeCategoryGlobal)
    {
        auto globalVar = CreateGlobalVariable(varName, node->GetVarType());
        node->GetScope()->ResolveSymbol(varName)->SetProperty(new SymbolProperty(globalVar));

        // Generate initialization code in internal initialization function.
        if (childCount == 1)
        {
            // Save current function.
            auto prevFunc = m_currentFunction;
            // Save current block
            auto prevBlock = m_irBuilder->GetInsertBlock();

            m_currentFunction = m_initFunction;

            // Set instruction generation pos to initialization function.
            m_irBuilder->SetInsertPoint(m_initFunctionBlock);

            // Generate code for right expression and get assignment value.
            auto rightExprValue = Visit(node->GetChild(0));

            // Save last used initializer function's basic block. If there is another
            // global variable, it will start from this block to generate code.
            m_initFunctionBlock = m_irBuilder->GetInsertBlock();

            // We load value from rightExprValue address and store at globalVar address.
            m_irBuilder->CreateStore(LoadIfPointerType(rightExprValue), globalVar);

            // Restore saved block (Intruction generation point).
            m_irBuilder->SetInsertPoint(prevBlock);
            // Restore saved function.
            m_currentFunction = prevFunc;
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


void CodeGenPass::VisitFunctionDeclaration(ast::NodeFuncDeclaration * node)
{
    // Save current block.
    llvm::BasicBlock *  prevBlock = m_irBuilder->GetInsertBlock();

    auto funcName = node->GetFuncName();
    auto funcReturnType = node->GetReturnType();
    auto funcSymbol = static_cast<FunctionSymbol*>(node->GetScope()->ResolveSymbol(funcName));

    // Create function argument types.
    std::vector<llvm::Type *>  argTypes;
    for (size_t i=0; i<funcSymbol->ArgumentCount(); ++i)
    {
        argTypes.emplace_back(CreateBaseType(funcSymbol->GetArgumentSymbol(i)->GetType()));
    }
    
    // Create function with arguments.
    m_currentFunction = CreateFunc(*m_irBuilder, funcReturnType, funcName, argTypes);
    funcSymbol->SetProperty(new SymbolProperty(m_currentFunction));

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

    // It's possible final nasic block may not have an return instruction.
    // Note: This is a workaround solution until return path analysis is done in semantic pass.
    if (m_irBuilder->GetInsertBlock()->getTerminator() == nullptr)
    {
        if (funcReturnType == scc::Type::kTypeVoid)
        {
            m_irBuilder->CreateRetVoid();
        }
        else
        {
            m_irBuilder->CreateRet(CreateConstant(funcReturnType, "0"));
        }
    }
    
    DeleteUnreachableBasicBlocks(m_currentFunction);

    // DEBUG
    // m_currentFunction->viewCFG();

    m_currentFunction = nullptr;
    m_irBuilder->SetInsertPoint(prevBlock);
}


void CodeGenPass::VisitBlock(ast::NodeBlock * node)
{
    // Visit childs
    VisitChilds(node);
}


void CodeGenPass::VisitIfStatement(ast::NodeIfStatement * node)
{
    //auto prevBlock = m_irBuilder->GetInsertBlock();

    auto condNode = node->GetChild(0);
    auto thenNode = node->GetChild(1);
    auto elseNode = node->ChildCount() == 3 ? node->GetChild(2) : nullptr;

    // Generate code for condition Expression.
    auto conditionValue = LoadIfPointerType(Visit(condNode));

    // Generate blocks.
    auto thenBlock  = CreateBasicBlock(m_currentFunction, "if.then");
    auto elseBlock  = CreateBasicBlock(m_currentFunction, "if.else");
    auto continueBlock = CreateBasicBlock(m_currentFunction, "if.cont");
    m_irBuilder->CreateCondBr(conditionValue, thenBlock, elseBlock);

    // Generate code for then statement.
    m_irBuilder->SetInsertPoint(thenBlock);
    auto thenValue = Visit(thenNode);
    m_irBuilder->CreateBr(continueBlock);

    m_irBuilder->SetInsertPoint(elseBlock);
    // Generate code only if there is else statement.
    if (elseNode != nullptr)
    {
        Visit(elseNode);
    }
    // Even there is no else block, we create else block to make flow work properly.
    // Empty else block will be eliminated by code optimizer.
    m_irBuilder->CreateBr(continueBlock);

    // New code generation should start in continue block.
    m_irBuilder->SetInsertPoint(continueBlock);
}


void CodeGenPass::VisitForStatement(ast::NodeForStatement * node)
{
    auto childCount = node->ChildCount();
    // There has to be min 4 childs. ForVarDec, ForCondition, ForIncrements and ForCodeBlock
    assert(childCount == 4);

    // for ( varDecl ; forCondition ; forIncrements ) forBody
    auto forVarDeclNode = node->GetChild(0);
    auto forCondNode    = node->GetChild(1);
    auto forIncsNode    = node->GetChild(2);
    auto forBodyNode    = node->GetChild(3);

    // Create basic blocks for loop construction.
    // Note: The reason we have extra block (for.body) is that LLVM has a strict rule that every basic block
    //       has to end with a terminator (ret, br etc..) instruction and each block can have only one terminator.
    /*
        for.cmp:
            <condition comparison>
            br for.body or for.exit
     
        for.body:
            <for body instructions>
            br for.inc

        for.Inc:
            <for increment instructions>
            br for.cmp
     
        for.exit:
            <...>
    */
    auto forCondBlock = CreateBasicBlock(m_currentFunction, "for.cmp");
    auto forBodyBlock = CreateBasicBlock(m_currentFunction, "for.body");
    auto forIncBlock  = CreateBasicBlock(m_currentFunction, "for.inc");
    auto forExitBlock = CreateBasicBlock(m_currentFunction, "for.exit");

    // Push BasicBlocks into the stack for this node. We may need these blocks create branch
    // for continue, break, return etc statements to create brach to jump to this nodes blocks
    // if necessary.
    m_nodeBBStack.Push(new NodeBasicBlocks(node, forCondBlock, forBodyBlock, forIncBlock, forExitBlock));

    // Generate code for variable declarations in current block.
    VisitChilds(forVarDeclNode);
    m_irBuilder->CreateBr(forCondBlock);
    
    // Generate code for.cmp

    m_irBuilder->SetInsertPoint(forCondBlock);

    if (forCondNode->ChildCount() > 0)
    {
        auto condValue = LoadIfPointerType(Visit(forCondNode->GetChild(0)));
        m_irBuilder->CreateCondBr(condValue, forBodyBlock, forExitBlock);
    }
    else
    {
        // If there is no condition then jump to body.
        m_irBuilder->CreateBr(forBodyBlock);
    }

    // Generate code for.body
    m_irBuilder->SetInsertPoint(forBodyBlock);
    Visit(forBodyNode);
    m_irBuilder->CreateBr(forIncBlock);

    // Generate code for.Inc

    m_irBuilder->SetInsertPoint(forIncBlock);

    if (forIncsNode->ChildCount() > 0)
    {
        VisitChilds(forIncsNode);
    }
    
    m_irBuilder->CreateBr(forCondBlock);

    // Set the code geneartion block to for.exit

    m_irBuilder->SetInsertPoint(forExitBlock);
    
    // Pop BasiBlock info from stack.
    m_nodeBBStack.PopAndDelete();
}


void CodeGenPass::VisitWhileStatement(ast::NodeWhileStatement * node)
{
    auto childCount = node->ChildCount();
    // There has to be 2 childs. expr and body.
    assert(childCount == 2);

    // while ( condition ) body
    auto condNode = node->GetChild(0);
    auto bodyNode = node->GetChild(1);

    // Create basic blocks for while loop construction.
    // Note: The reason we have extra block (while.body) is that LLVM has a strict rule that every basic block
    //       has to end with a terminator (ret, br etc..) instruction and each block can have only one terminator.
    /*
        while.cmp:
            <condition comparison>
            br while.body or while.exit
     
        while.body:
            <body instructions>
            br while.cmp
     
        while.exit:
            <...>
    */
    auto condBlock = CreateBasicBlock(m_currentFunction, "while.cmp");
    auto bodyBlock = CreateBasicBlock(m_currentFunction, "while.body");
    auto exitBlock = CreateBasicBlock(m_currentFunction, "while.exit");

    // Push BasicBlocks into the stack for this node. We may need these blocks create branch
    // for continue, break, return etc statements to create brach to jump to this nodes blocks
    // if necessary.
    m_nodeBBStack.Push(new NodeBasicBlocks(node, condBlock, bodyBlock, nullptr, exitBlock));

    // Jump from current block to condition block.
    m_irBuilder->CreateBr(condBlock);
    
    // Generate code while.cmp

    m_irBuilder->SetInsertPoint(condBlock);

    auto condValue = LoadIfPointerType(Visit(condNode));
    m_irBuilder->CreateCondBr(condValue, bodyBlock, exitBlock);

    // Generate code while.body
    m_irBuilder->SetInsertPoint(bodyBlock);
    Visit(bodyNode);
    m_irBuilder->CreateBr(condBlock);

    // Set the code geneartion block to for.exit
    m_irBuilder->SetInsertPoint(exitBlock);
    
    // Pop BasiBlock info from stack.
    m_nodeBBStack.PopAndDelete();
}


void CodeGenPass::VisitDoWhileStatement(ast::NodeDoWhileStatement * node)
{
    auto childCount = node->ChildCount();
    // There has to be 2 childs. expr and body.
    assert(childCount == 2);

    // do body while ( condition )
    auto bodyNode = node->GetChild(0);
    auto condNode = node->GetChild(1);

    // Create basic blocks for do while loop construction.
    // Note: The reason we have extra block (do_while.body) is that LLVM has a strict rule that every basic block
    //       has to end with a terminator (ret, br etc..) instruction and each block can have only one terminator.
    /*
        do_while.body:
            <body instructions>
            br do_while.cmp

        do_while.cmp:
            <condition comparison>
            br do_while.body or do_while.exit

        do_while.exit:
            <...>
    */
    auto condBlock = CreateBasicBlock(m_currentFunction, "do_while.cmp");
    auto bodyBlock = CreateBasicBlock(m_currentFunction, "do_while.body");
    auto exitBlock = CreateBasicBlock(m_currentFunction, "do_while.exit");

    // Push BasicBlocks into the stack for this node. We may need these blocks create branch
    // for continue, break, return etc statements to create brach to jump to this nodes blocks
    // if necessary.
    m_nodeBBStack.Push(new NodeBasicBlocks(node, condBlock, bodyBlock, nullptr, exitBlock));

    // Jump from current block to condition block.
    m_irBuilder->CreateBr(bodyBlock);
    
    // Generate code while.body

    m_irBuilder->SetInsertPoint(bodyBlock);
    Visit(bodyNode);
    m_irBuilder->CreateBr(condBlock);

    // Generate code do_while.cmp

    m_irBuilder->SetInsertPoint(condBlock);

    auto condValue = LoadIfPointerType(Visit(condNode));
    m_irBuilder->CreateCondBr(condValue, bodyBlock, exitBlock);

    // Set the code geneartion block to for.exit
    m_irBuilder->SetInsertPoint(exitBlock);
    
    // Pop BasiBlock info from stack.
    m_nodeBBStack.PopAndDelete();
}


void CodeGenPass::VisitReturnStatement(ast::NodeReturnStatement * node)
{
    // If there is no child then return void. Function return type is void.
    if (node->ChildCount() == 0)
    {
        m_irBuilder->CreateRetVoid();
    }
    else
    {
        // return <expression>
        auto exprValue = LoadIfPointerType(Visit(node->GetChild(0)));
        m_irBuilder->CreateRet(exprValue);
    }
    // Any instruction after a terminator instruction (ret, br, switch, ...) won't be executed.
    // Creating a new block and generating all unreachable code in then optimizer can eliminate it.
    auto unreachableBlock = CreateBasicBlock(m_currentFunction, "unreachable");
    m_irBuilder->SetInsertPoint(unreachableBlock);
}


void CodeGenPass::VisitContinue(ast::NodeContinue * node)
{
    auto nodeBasicBlocks = m_nodeBBStack.GetOneOfThese({ast::NodeType::kNodeTypeForStatement,
                                                        ast::NodeType::kNodeTypeWhileStatement,
                                                        ast::NodeType::kNodeTypeDoWhileStatement});
    assert(nodeBasicBlocks);
    
    switch (nodeBasicBlocks->GetNode()->GetNodeType())
    {
        case ast::NodeType::kNodeTypeForStatement:
        m_irBuilder->CreateBr(nodeBasicBlocks->GetIncrementBasicBlock());
        break;

        case ast::NodeType::kNodeTypeWhileStatement:
        case ast::NodeType::kNodeTypeDoWhileStatement:
        m_irBuilder->CreateBr(nodeBasicBlocks->GetConditionBasicBlock());
        break;

        default:
        assert(false && "Unhandled node type!");
        break;
    }

    // Create new basic blcok for unreachable instructions after coming continue statement.
    auto unreachableBasicBlock = CreateBasicBlock(m_currentFunction, "unreachable");
    m_irBuilder->SetInsertPoint(unreachableBasicBlock);
}


void CodeGenPass::VisitBreak(ast::NodeBreak * node)
{
    auto nodeBasicBlocks = m_nodeBBStack.GetOneOfThese({ast::NodeType::kNodeTypeForStatement,
                                                        ast::NodeType::kNodeTypeWhileStatement,
                                                        ast::NodeType::kNodeTypeDoWhileStatement});
    assert(nodeBasicBlocks);
    
    switch (nodeBasicBlocks->GetNode()->GetNodeType())
    {
        case ast::NodeType::kNodeTypeForStatement:
        m_irBuilder->CreateBr(nodeBasicBlocks->GetExitBasicBlock());
        break;

        case ast::NodeType::kNodeTypeWhileStatement:
        case ast::NodeType::kNodeTypeDoWhileStatement:
        m_irBuilder->CreateBr(nodeBasicBlocks->GetExitBasicBlock());
        break;

        default:
        assert(false && "Unhandled node type!");
        break;
    }

    // Create new basic blcok for unreachable instructions after coming break statement.
    auto unreachableBasicBlock = CreateBasicBlock(m_currentFunction, "unreachable");
    m_irBuilder->SetInsertPoint(unreachableBasicBlock);
}


llvm::Value * CodeGenPass::VisitFunctionCall(ast::NodeFuncCall * node)
{
    std::vector<llvm::Value *> args;

    // Visit all function argument expressions.
    for (size_t index=0; index < node->ChildCount(); ++index)
    {
        auto argExprValue = Visit(node->GetChild(index));
        args.emplace_back(LoadIfPointerType(argExprValue));
    }
    auto funcName = node->GetFuncName();
    auto funcSymbol = static_cast<FunctionSymbol *>(node->GetScope()->ResolveSymbol(funcName));
    assert(funcSymbol != nullptr);
    
    auto func = static_cast<SymbolProperty *>(funcSymbol->GetProperty())->GetValue();
    assert(func != nullptr);

    return m_irBuilder->CreateCall(func, args);
}


void CodeGenPass::VisitAssignment(ast::NodeAssignment * node)
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


llvm::Value * CodeGenPass::VisitExplicitTypeConversion(ast::NodeExplicitTypeConversion * node)
{
    // Generate code for expression.
    auto exprValue = LoadIfPointerType(Visit(node->GetChild(0)));
    llvm::Value * convertedValue = nullptr;
    
    // Convert exprValue from Float To (int or bool)
    if (exprValue->getType()->getTypeID() == llvm::Type::TypeID::FloatTyID)
    {
        switch (node->GetConversionType())
        {
            case Type::kTypeInt:
            convertedValue = m_irBuilder->CreateFPToSI(exprValue, CreateBaseType(Type::kTypeInt));
            break;

            case Type::kTypeBool:
            convertedValue = m_irBuilder->CreateFCmpUNE(exprValue, CreateConstant(scc::Type::kTypeFloat, "0"));
            break;

            case Type::kTypeFloat:
            // No need to do any conversion.
            convertedValue = exprValue;
            break;

            default:
            assert(false && "Unhandled conversion type.");
            break;
        }
    }

    // Convert exprValue from Int To (float or bool)
    if (exprValue->getType()->getTypeID() == llvm::Type::TypeID::IntegerTyID &&
        exprValue->getType()->getPrimitiveSizeInBits() == 32)
    {
        switch (node->GetConversionType())
        {
            case Type::kTypeFloat:
            convertedValue = m_irBuilder->CreateSIToFP(exprValue, CreateBaseType(Type::kTypeFloat));
            break;

            case Type::kTypeBool:
            convertedValue = m_irBuilder->CreateICmpNE(exprValue, CreateConstant(scc::Type::kTypeInt, "0"));
            break;

            case Type::kTypeInt:
            // No need to do any conversion.
            convertedValue = exprValue;
            break;

            default:
            assert(false && "Unhandled conversion type.");
            break;
        }
    }

    // Convert exprValue from Bool To (float or Int)
    if (exprValue->getType()->getTypeID() == llvm::Type::TypeID::IntegerTyID &&
        exprValue->getType()->getPrimitiveSizeInBits() == 1)
    {
        switch (node->GetConversionType())
        {
            case Type::kTypeFloat:
            convertedValue = m_irBuilder->CreateUIToFP(exprValue, CreateBaseType(Type::kTypeFloat));
            break;

            case Type::kTypeInt:
            {
                convertedValue = m_irBuilder->CreateZExt(exprValue, CreateBaseType(scc::Type::kTypeInt));
            }
            break;

            case Type::kTypeBool:
            // No need to do any conversion.
            convertedValue = exprValue;
            break;

            default:
            assert(false && "Unhandled conversion type.");
            break;
        }
    }


    return convertedValue;
}


llvm::Value * CodeGenPass::VisitLogicalNotOP(ast::NodeLogicalOP * node)
{
    auto exprValue = LoadIfPointerType(Visit(node->GetChild(0)));
    auto exprType = exprValue->getType()->getTypeID();
    
    if (exprType == llvm::Type::TypeID::FloatTyID)
    {
        exprValue = m_irBuilder->CreateFCmpUNE(exprValue, CreateConstant(scc::Type::kTypeFloat, "0"));
        exprValue = m_irBuilder->CreateXor(exprValue, CreateConstant(scc::Type::kTypeBool, "true"));
        exprValue = m_irBuilder->CreateUIToFP(exprValue, CreateBaseType(scc::Type::kTypeFloat));
    }
    else if (exprType == llvm::Type::TypeID::IntegerTyID &&
             exprValue->getType()->getPrimitiveSizeInBits() == 32)
    {
        exprValue = m_irBuilder->CreateICmpNE(exprValue, CreateConstant(scc::Type::kTypeInt, "0"));
        exprValue = m_irBuilder->CreateXor(exprValue, CreateConstant(scc::Type::kTypeBool, "true"));
        exprValue = m_irBuilder->CreateZExt(exprValue, CreateBaseType(scc::Type::kTypeInt));
    }
    else if (exprType == llvm::Type::TypeID::IntegerTyID &&
             exprValue->getType()->getPrimitiveSizeInBits() == 1)
    {
        exprValue = m_irBuilder->CreateXor(exprValue, CreateConstant(scc::Type::kTypeBool, "true"));
    }
    else
    {
        assert(false && "Unknown type for logical not operator.");
    }

    return exprValue;
}


llvm::Value * CodeGenPass::VisitLogicalAndOP(ast::NodeLogicalOP * node)
{
    auto leftExprNode  = node->GetChild(0);
    auto rightExprNode = node->GetChild(1);

    auto rightExprBlock = CreateBasicBlock(m_currentFunction, "&&.rightExpr");
    auto exitBlock = CreateBasicBlock(m_currentFunction, "&&.exit");

    // Generate code in current block.
    auto resultVar = m_irBuilder->CreateAlloca(CreateBaseType(scc::Type::kTypeBool), nullptr, "_cb");
    auto leftExprValue = LoadIfPointerType(Visit(leftExprNode));
    m_irBuilder->CreateStore(leftExprValue, resultVar);
    m_irBuilder->CreateCondBr(leftExprValue, rightExprBlock, exitBlock);

    // Generate code for rightExprBlock.
    m_irBuilder->SetInsertPoint(rightExprBlock);
    auto rightExprValue = LoadIfPointerType(Visit(rightExprNode));
    m_irBuilder->CreateStore(rightExprValue, resultVar);
    m_irBuilder->CreateBr(exitBlock);

    // Generate code for exitBlock.
    m_irBuilder->SetInsertPoint(exitBlock);

    return resultVar;
}


llvm::Value * CodeGenPass::VisitLogicalOrOP(ast::NodeLogicalOP * node)
{
    auto leftExprNode  = node->GetChild(0);
    auto rightExprNode = node->GetChild(1);

    auto rightExprBlock = CreateBasicBlock(m_currentFunction, "&&.rightExpr");
    auto exitBlock = CreateBasicBlock(m_currentFunction, "&&.exit");

    // Generate code in current block.
    auto resultVar = m_irBuilder->CreateAlloca(CreateBaseType(scc::Type::kTypeBool), nullptr);
    auto leftExprValue = LoadIfPointerType(Visit(leftExprNode));
    m_irBuilder->CreateStore(leftExprValue, resultVar);
    m_irBuilder->CreateCondBr(leftExprValue, exitBlock, rightExprBlock);

    // Generate code for rightExprBlock.
    m_irBuilder->SetInsertPoint(rightExprBlock);
    auto rightExprValue = LoadIfPointerType(Visit(rightExprNode));
    m_irBuilder->CreateStore(rightExprValue, resultVar);
    m_irBuilder->CreateBr(exitBlock);

    // Generate code for exitBlock.
    m_irBuilder->SetInsertPoint(exitBlock);

    return resultVar;
}


llvm::Value * CodeGenPass::VisitNodeUnaryOP(ast::NodeUnaryOP * node)
{
    // Generate code for right expression.
    auto exprValue = LoadIfPointerType(Visit(node->GetChild(0)));
    llvm::Value * negatedValue = nullptr;

    // Nothing to do for '+' unary operation. Just return expr value.
    if (node->GetNodeType() == ast::NodeType::kNodeTypeUOPPlus)
    {
        return exprValue;
    }

    // Negate value based on type. After semantic pass, only allowed types should reach to this point.
    switch (exprValue->getType()->getTypeID())
    {
        case llvm::Type::TypeID::FloatTyID:
            negatedValue = m_irBuilder->CreateFMul(CreateConstant(scc::Type::kTypeFloat, "-1"), exprValue, "negtmp");
        break;

        case llvm::Type::TypeID::IntegerTyID:
            negatedValue = m_irBuilder->CreateMul(CreateConstant(scc::Type::kTypeInt, "-1"), exprValue, "negtmp");
        break;

        default:
        assert(false && "Unhandled type for unary operation.");
        break;
    }
    
    return negatedValue;
}


llvm::Value * CodeGenPass::VisitCompOP(ast::NodeCompOP * node)
{
    llvm::Value * resultValue = nullptr;

    // Visit always return pointer to value so we need to load to get value from pointed address.
    auto leftOperandValue = LoadIfPointerType(Visit(node->GetChild(0)));
    auto rightOperandValue = LoadIfPointerType(Visit(node->GetChild(1)));

    llvm::Type::TypeID leftOpTypeID = leftOperandValue->getType()->getTypeID();
    llvm::Type::TypeID rightOpTypeID = rightOperandValue->getType()->getTypeID();
    assert(leftOpTypeID == rightOpTypeID);

    if (leftOpTypeID == llvm::Type::FloatTyID)
    {
        switch (node->GetNodeType())
        {
            case ast::NodeType::kNodeTypeCompOPEQ:
                resultValue = m_irBuilder->CreateFCmpOEQ(leftOperandValue, rightOperandValue);
            break;

            case ast::NodeType::kNodeTypeCompOPNEQ:
                resultValue = m_irBuilder->CreateFCmpONE(leftOperandValue, rightOperandValue);
            break;

            case ast::NodeType::kNodeTypeCompOPLE:
                resultValue = m_irBuilder->CreateFCmpOLE(leftOperandValue, rightOperandValue);
            break;

            case ast::NodeType::kNodeTypeCompOPGE:
                resultValue = m_irBuilder->CreateFCmpOGE(leftOperandValue, rightOperandValue);
            break;

            case ast::NodeType::kNodeTypeCompOPL:
                resultValue = m_irBuilder->CreateFCmpOLT(leftOperandValue, rightOperandValue);
            break;

            case ast::NodeType::kNodeTypeCompOPG:
                resultValue = m_irBuilder->CreateFCmpOGT(leftOperandValue, rightOperandValue);
            break;

            default:
                assert(false && "Unknown comparison node type.");
            break;
        }
    }
    else if (leftOpTypeID == llvm::Type::IntegerTyID)
    {
        switch (node->GetNodeType())
        {
            case ast::NodeType::kNodeTypeCompOPEQ:
                resultValue = m_irBuilder->CreateICmpEQ(leftOperandValue, rightOperandValue);
            break;

            case ast::NodeType::kNodeTypeCompOPNEQ:
                resultValue = m_irBuilder->CreateICmpNE(leftOperandValue, rightOperandValue);
            break;

            case ast::NodeType::kNodeTypeCompOPLE:
                resultValue = m_irBuilder->CreateICmpSLE(leftOperandValue, rightOperandValue);
            break;

            case ast::NodeType::kNodeTypeCompOPGE:
                resultValue = m_irBuilder->CreateICmpSGE(leftOperandValue, rightOperandValue);
            break;

            case ast::NodeType::kNodeTypeCompOPL:
                resultValue = m_irBuilder->CreateICmpSLT(leftOperandValue, rightOperandValue);
            break;

            case ast::NodeType::kNodeTypeCompOPG:
                resultValue = m_irBuilder->CreateICmpSGT(leftOperandValue, rightOperandValue);
            break;

            default:
                assert(false && "Unknown comparison node type.");
            break;
        }
    }
    else
    {
        assert(false && "Unknown comparison type.");
    }

    return resultValue;
}


llvm::Value * CodeGenPass::VisitAOP(ast::NodeAOP * node)
{
    llvm::Value * resultValue = nullptr;

    // Visit always return pointer to value so we need to load to get value from pointed address.
    auto leftOperandValue = LoadIfPointerType(Visit(node->GetChild(0)));
    auto rightOperandValue = LoadIfPointerType(Visit(node->GetChild(1)));

    //std::cout << "BeforeLeftTypeID:" << DebugLLVMTypeAsString(leftOperandValue->getType()->getTypeID()) << std::endl;
    //std::cout << "BeforeRightTypeID:" << DebugLLVMTypeAsString(rightOperandValue->getType()->getTypeID()) << std::endl;

    // Type promotion should be done here.
    llvm::Type::TypeID leftOpTypeID = leftOperandValue->getType()->getTypeID();
    llvm::Type::TypeID rightOpTypeID = rightOperandValue->getType()->getTypeID();

    switch (node->GetNodeType())
    {
        case ast::NodeType::kNodeTypeAOPMul:
            if (leftOpTypeID == llvm::Type::FloatTyID)
                resultValue = m_irBuilder->CreateFMul(leftOperandValue, rightOperandValue, "fmultmp");
            else
                resultValue = m_irBuilder->CreateMul(leftOperandValue, rightOperandValue, "multmp");
        break;

        case ast::NodeType::kNodeTypeAOPDiv:
            if (leftOpTypeID == llvm::Type::FloatTyID)
                resultValue = m_irBuilder->CreateFDiv(leftOperandValue, rightOperandValue, "fdivtmp");
            else
                resultValue = m_irBuilder->CreateSDiv(leftOperandValue, rightOperandValue, "sdivtmp");
        break;

        case ast::NodeType::kNodeTypeAOPAdd:
            if (leftOpTypeID == llvm::Type::FloatTyID)
                resultValue = m_irBuilder->CreateFAdd(leftOperandValue, rightOperandValue, "faddtmp");
            else
                resultValue = m_irBuilder->CreateAdd(leftOperandValue, rightOperandValue, "addtmp");
        break;

        case ast::NodeType::kNodeTypeAOPSub:
            if (leftOpTypeID == llvm::Type::FloatTyID)
                resultValue = m_irBuilder->CreateFSub(leftOperandValue, rightOperandValue, "fsubtmp");
            else
                resultValue = m_irBuilder->CreateSub(leftOperandValue, rightOperandValue, "subtmp");
        break;

        default:
            assert(false && "Unknown node type");
        break;
    }

    return resultValue;
}



llvm::Value * CodeGenPass::VisitLiteral(ast::NodeLiteral * node)
{
    llvm::Value * literalValue = nullptr;
    
    switch (node->GetNodeType())
    {
        case ast::NodeType::kNodeTypeLiteralFloat:
        {
            // We create temp local variable and assign constant value.
            auto localVar = m_irBuilder->CreateAlloca(CreateBaseType(scc::Type::kTypeFloat), nullptr, "_ci");
            // Since we store constant, we don't need to load value from an address.
            m_irBuilder->CreateStore(CreateConstant(scc::Type::kTypeFloat, node->GetValue()), localVar);
            // Returns pointer to local variable.
            literalValue = localVar;
        }
        break;
        
        case ast::NodeType::kNodeTypeLiteralInt32:
        {
            // We create temp local variable and assign constant value.
            auto localVar = m_irBuilder->CreateAlloca(CreateBaseType(scc::Type::kTypeInt), nullptr, "_cf");
            // Since we store constant, we don't need to load value from an address.
            m_irBuilder->CreateStore(CreateConstant(scc::Type::kTypeInt, node->GetValue()), localVar);
            // Returns pointer to local variable.
            literalValue = localVar;
        }
        break;
        
        case ast::NodeType::kNodeTypeLiteralBool:
        {
            // We create temp local variable and assign constant value.
            auto localVar = m_irBuilder->CreateAlloca(CreateBaseType(scc::Type::kTypeBool), nullptr, "_cb");
            // Since we store constant, we don't need to load value from an address.
            m_irBuilder->CreateStore(CreateConstant(scc::Type::kTypeBool, node->GetValue()), localVar);
            // Returns pointer to local variable.
            literalValue = localVar;
        }
        break;
        
        case ast::NodeType::kNodeTypeLiteralID:
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


void CodeGenPass::CreateInternalInitializerFunction()
{
    // Save current block.
    llvm::BasicBlock *  prevBlock = m_irBuilder->GetInsertBlock();

    // No argument is required.
    std::vector<llvm::Type *> argTypes;

    // Create initializer function.
    m_initFunction = CreateFunc(*m_irBuilder, Type::kTypeVoid, "__initGlobalVariables__", argTypes);

    // Create basic block for function.
    m_initFunctionBlock = CreateBasicBlock(m_initFunction, "entry");
    
    // Restore previous block.
    m_irBuilder->SetInsertPoint(prevBlock);
}


void CodeGenPass::FinalizeInternalInitializerFunction()
{
    // Finalize global variable initialization code.
    auto prevBlock = m_irBuilder->GetInsertBlock();
    m_irBuilder->SetInsertPoint(m_initFunctionBlock);
    m_irBuilder->CreateRetVoid();
    m_irBuilder->SetInsertPoint(prevBlock);
}


llvm::Type * CodeGenPass::CreateBaseType(scc::Type type)
{
    switch(type)
    {
        case scc::Type::kTypeInt:
            return m_irBuilder->getInt32Ty();
        break;

        case scc::Type::kTypeFloat:
            return m_irBuilder->getFloatTy();
        break;

        case scc::Type::kTypeVoid:
            return m_irBuilder->getVoidTy();
        break;

        case scc::Type::kTypeBool:
            return m_irBuilder->getInt1Ty();
        break;

        default:
            assert(false && "Unknown type.");
        break;
    }

    return nullptr;
}


llvm::Constant * CodeGenPass::CreateConstant(scc::Type type, const std::string & value)
{
    assert(value.size() > 0);

    switch(type)
    {
        case scc::Type::kTypeInt:
            return llvm::ConstantInt::get(*m_context, llvm::APInt(32, uint32_t(atoi(value.c_str())), true));
            break;

        case scc::Type::kTypeFloat:
            return llvm::ConstantFP::get(*m_context, llvm::APFloat(float(atof(value.c_str()))));
            break;

        case scc::Type::kTypeBool:
            return llvm::ConstantInt::get(*m_context, llvm::APInt(1, value == "true" ? 1 : 0, false));
            break;

        default:
            assert(false && "Unknown type.");
            break;
    }

    return nullptr;
}


llvm::GlobalVariable * CodeGenPass::CreateGlobalVariable(std::string name, scc::Type type)
{
    m_module->getOrInsertGlobal(name, CreateBaseType(type));
    auto gVar = m_module->getNamedGlobal(name);
    gVar->setLinkage(llvm::GlobalValue::CommonLinkage);
    gVar->setAlignment(4);
    gVar->setInitializer(CreateConstant(type, "0"));

    return gVar;
}


llvm::Function * CodeGenPass::CreateFunc(llvm::IRBuilder <> & Builder,
                                         scc::Type returnType,
                                         std::string name,
                                         std::vector<llvm::Type *> & argTypes)
{
    llvm::FunctionType * funcType = llvm::FunctionType::get(CreateBaseType(returnType), argTypes, false);
    // ExternalLinkage enumeration member means that the function can be referred from other modules.
    llvm::Function * func = llvm::Function::Create(funcType, llvm::Function::ExternalLinkage, name, m_module.get());

    return func;
}


llvm::BasicBlock * CodeGenPass::CreateBasicBlock(llvm::Function * func, std::string name)
{
    return llvm::BasicBlock::Create(*m_context, name, func);
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


void CodeGenPass::DeleteUnreachableBasicBlocks(llvm::Function * function)
{
    auto & bbList = m_currentFunction->getBasicBlockList();
    auto prevIt = bbList.begin();
    for (auto it = bbList.begin(); it != bbList.end(); ++it)
    {
        if (it->getName().str().size() > 10 && it->getName().str().compare(0, 11, "unreachable") == 0)
        {
            it->eraseFromParent();
            it = prevIt;
        }
        prevIt = it;
    }
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

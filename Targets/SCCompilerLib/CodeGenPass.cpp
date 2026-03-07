//
//  Created by Arkin Terli on 4/22/18.
//  Copyright © 2018-Present, Arkin Terli. All rights reserved.
//

// Project includes
#include "CodeGenPass.hpp"
#include "AST.hpp"
#include "JITEngine.hpp"
#include "Symbols.hpp"
#include "Types.hpp"
// External includes
#include <llvm/ADT/STLExtras.h>
#include <llvm/ExecutionEngine/ExecutionEngine.h>
#include <llvm/ExecutionEngine/GenericValue.h>
#include <llvm/ExecutionEngine/MCJIT.h>
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
#include <cassert>
#include <string>


using namespace scc;


CodeGenPass::CodeGenPass() = default;


SymbolProperty::SymbolProperty(llvm::Value * value) :
    m_value(value)
{

}


llvm::Value * SymbolProperty::getValue()
{
    return m_value;
}


NodeBasicBlockSet::NodeBasicBlockSet(ast::Node * node,
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


ast::Node * NodeBasicBlockSet::getNode()
{
    return m_node;
}


llvm::BasicBlock * NodeBasicBlockSet::getConditionBasicBlock()
{
    assert(m_conditionBasicBlock != nullptr && "No reason to use if it is nullptr.");
    return m_conditionBasicBlock;
}


llvm::BasicBlock * NodeBasicBlockSet::getBodyBasicBlock()
{
    assert(m_bodyBasicBlock != nullptr && "No reason to use if it is nullptr.");
    return m_bodyBasicBlock;
}


llvm::BasicBlock * NodeBasicBlockSet::getIncrementBasicBlock()
{
    assert(m_incrementBasicBlock != nullptr && "No reason to use if it is nullptr.");
    return m_incrementBasicBlock;
}


llvm::BasicBlock * NodeBasicBlockSet::getExitBasicBlock()
{
    assert(m_exitBasicBlock != nullptr && "No reason to use if it is nullptr.");
    return m_exitBasicBlock;
}


void NodeBasicBlockSetStack::push(std::unique_ptr<NodeBasicBlockSet> nodeBasicBlockSet)
{
    assert(nodeBasicBlockSet != nullptr);
    m_nodeBasicBlockStack.emplace_back(std::move(nodeBasicBlockSet));
}


void NodeBasicBlockSetStack::pop()
{
    assert(!m_nodeBasicBlockStack.empty());
    m_nodeBasicBlockStack.pop_back();
}


NodeBasicBlockSet * NodeBasicBlockSetStack::getOneOfNodeTypes(const std::vector<ast::NodeType> & nodeTypes)
{
    auto size = m_nodeBasicBlockStack.size();
    assert(size > 0);
    
    for (size_t index=0; index < size; ++index)
    {
        // If node type matches one of the given type then return it.
        for (auto nodeType : nodeTypes)
        {
            auto nodeBasicBlockSet = m_nodeBasicBlockStack[size-index-1].get();
            if (nodeBasicBlockSet->getNode()->getNodeType() == nodeType)
            {
                return nodeBasicBlockSet;
            }
        }
    }

    return nullptr;
}


CodeGenPass::~CodeGenPass()
{
}


std::unique_ptr<SCModule> CodeGenPass::generateCode(ast::Node * node)
{
    m_context = std::make_unique<llvm::LLVMContext>();
    m_module = std::make_unique<llvm::Module>("Program", *m_context);

    // Create new IRBuilder for global scope.
    m_irBuilder = std::make_unique<llvm::IRBuilder<>>(*m_context);

    createInternalInitializerFunction();

    visit(node);

    finalizeInternalInitializerFunction();

    // dumpIRCode(); // REQUIRES to build LLVM in debug mode.

    // Create JITEngine. Transfer ownership of m_module and m_context to JITEngine.
    return std::make_unique<JITEngine>(std::move(m_module), std::move(m_context));
}


void CodeGenPass::visitChildren(ast::Node * node)
{
    // Visit node children.
    for (size_t index=0; index<node->childCount(); ++index)
    {
        visit(node->getChild(index));
    }
}


llvm::Value * CodeGenPass::visit(ast::Node * node)
{
    switch(node->getNodeType())
    {
        case ast::NodeType::kProgram:
            visitProgram(static_cast<ast::NodeProgram *>(node));
            break;

        case ast::NodeType::kVariableDeclaration:
            visitVariableDeclaration(static_cast<ast::NodeVariableDeclaration *>(node));
            break;

        case ast::NodeType::kFunctionDeclaration:
            visitFunctionDeclaration(static_cast<ast::NodeFunctionDeclaration *>(node));
            break;

        case ast::NodeType::kBlock:
            visitBlock(static_cast<ast::NodeBlock *>(node));
            break;

        case ast::NodeType::kIfStatement:
            visitIfStatement(static_cast<ast::NodeIfStatement *>(node));
            break;

        case ast::NodeType::kForStatement:
            visitForStatement(static_cast<ast::NodeForStatement *>(node));
            break;

        case ast::NodeType::kForVarDecl:
        case ast::NodeType::kForIncrement:
            visitChildren(node);
            break;

        case ast::NodeType::kWhileStatement:
            visitWhileStatement(static_cast<ast::NodeWhileStatement *>(node));
            break;

        case ast::NodeType::kDoWhileStatement:
            visitDoWhileStatement(static_cast<ast::NodeDoWhileStatement *>(node));
            break;

        case ast::NodeType::kReturnStatement:
            visitReturnStatement(static_cast<ast::NodeReturnStatement *>(node));
            break;

        case ast::NodeType::kContinue:
            visitContinue(static_cast<ast::NodeContinue *>(node));
            break;

        case ast::NodeType::kBreak:
            visitBreak(static_cast<ast::NodeBreak *>(node));
            break;

        case ast::NodeType::kFunctionCall:
            return visitFunctionCall(static_cast<ast::NodeFunctionCall *>(node));
            break;

        case ast::NodeType::kAssignment:
            visitAssignment(static_cast<ast::NodeAssignment *>(node));
            break;

        case ast::NodeType::kExplicitTypeConversion:
            return visitExplicitTypeConversion(static_cast<ast::NodeExplicitTypeConversion *>(node));
            break;

        case ast::NodeType::kLogicalNotOP:
            return visitLogicalNotOperator(static_cast<ast::NodeLogicalOperator *>(node));
            break;

        case ast::NodeType::kLogicalAndOP:
            return visitLogicalAndOperator(static_cast<ast::NodeLogicalOperator *>(node));
            break;

        case ast::NodeType::kLogicalOrOP:
            return visitLogicalOrOperator(static_cast<ast::NodeLogicalOperator *>(node));
            break;

        case ast::NodeType::kUOPMinus:
        case ast::NodeType::kUOPPlus:
            return visitUnaryOperator(static_cast<ast::NodeUnaryOperator *>(node));
            break;

        case ast::NodeType::kCompOPEQ:
        case ast::NodeType::kCompOPNEQ:
        case ast::NodeType::kCompOPLE:
        case ast::NodeType::kCompOPGE:
        case ast::NodeType::kCompOPL:
        case ast::NodeType::kCompOPG:
            return visitComparisonOperator(static_cast<ast::NodeComparisonOperator *>(node));
            break;

        case ast::NodeType::kPrefixIncAOP:
        case ast::NodeType::kPrefixDecAOP:
            return visitPrefixArithmeticOperator(static_cast<ast::NodePrefixArithmeticOperator *>(node));
            break;

        case ast::NodeType::kAOPMul:
        case ast::NodeType::kAOPDiv:
        case ast::NodeType::kAOPAdd:
        case ast::NodeType::kAOPSub:
            return visitArithmeticOperator(static_cast<ast::NodeArithmeticOperator *>(node));
            break;

        case ast::NodeType::kLiteralFloat:
        case ast::NodeType::kLiteralInt32:
        case ast::NodeType::kLiteralBool:
        case ast::NodeType::kLiteralID:
            return visitLiteral(static_cast<ast::NodeLiteral *>(node));
            break;

        case ast::NodeType::kForCondition:
            assert(false && "visitForStatement() must manage this node implicitly.");
            break;

        default:
            assert(false && "Unknown node type in SemanticPass.");
            break;
    }

    return nullptr;
}


void CodeGenPass::visitProgram(ast::NodeProgram * node)
{
    visitChildren(node);
}


void CodeGenPass::visitVariableDeclaration(ast::NodeVariableDeclaration * node)
{
    auto childCount = node->childCount();
    auto varName = node->getVarName();
    assert(childCount < 2);

    // Create a global variable if the variable is in the global scope.
    if (node->getScope()->getCategory() == ScopeCategory::kGlobal)
    {
        auto globalVar = createGlobalVariable(varName, node->getVarType());
        node->getScope()->resolveSymbol(varName)->setProperty(std::make_unique<SymbolProperty>(globalVar));

        // Generate initialization code in the internal initialization function.
        if (childCount == 1)
        {
            // Save the current function.
            auto prevFunc = m_currentFunction;
            // Save the current block.
            auto prevBlock = m_irBuilder->GetInsertBlock();

            m_currentFunction = m_initFunction;

            // Set the instruction generation position to the initialization function.
            m_irBuilder->SetInsertPoint(m_initFunctionBlock);

            // Generate code for the right expression and get the assignment value.
            auto rightExprValue = visit(node->getChild(0));

            // Save the last used initializer function's basic block. If there is another
            // global variable, it will start from this block to generate code.
            m_initFunctionBlock = m_irBuilder->GetInsertBlock();

            // We load the value from the rightExprValue address and store it at the globalVar address.
            m_irBuilder->CreateStore(loadIfPointerType(rightExprValue), globalVar);

            // Restore the saved block (instruction generation point).
            m_irBuilder->SetInsertPoint(prevBlock);
            // Restore the saved function.
            m_currentFunction = prevFunc;
        }
    }
    else
    {
        // Create a stack-allocated local variable.
        auto localVar = m_irBuilder->CreateAlloca(createBaseType(node->getVarType()), nullptr, varName);
        // Set the symbol property to save the new LLVM variable object. Save related LLVM objects in the symbol object.
        // We save the LLVM object because every time this variable is used, we need to access its LLVM object.
        node->getScope()->resolveSymbol(varName)->setProperty(std::make_unique<SymbolProperty>(localVar));

        // If the node has a child, then it needs to be evaluated and assigned to the new variable.
        if (childCount == 1)
        {
            // Generate code for the right expression and get the assignment value.
            auto rightExprValue = visit(node->getChild(0));
            // We load the value from the rightExprValue address and store it at the localVar address.
            m_irBuilder->CreateStore(loadIfPointerType(rightExprValue), localVar);
        }
    }
}

void CodeGenPass::visitFunctionDeclaration(ast::NodeFunctionDeclaration * node)
{
    // Save current block.
    llvm::BasicBlock *  prevBlock = m_irBuilder->GetInsertBlock();

    auto funcName = node->getFuncName();
    auto funcReturnType = node->getReturnType();
    auto funcSymbol = static_cast<FunctionSymbol*>(node->getScope()->resolveSymbol(funcName));

    // Create function argument types.
    std::vector<llvm::Type *>  argTypes;
    for (size_t i=0; i<funcSymbol->argumentCount(); ++i)
    {
        argTypes.emplace_back(createBaseType(funcSymbol->getArgumentSymbol(i)->getType()));
    }
    
    // Create function with arguments.
    m_currentFunction = createFunc(*m_irBuilder, funcReturnType, funcName, argTypes);
    funcSymbol->setProperty(std::make_unique<SymbolProperty>(m_currentFunction));

    // Create basic block for function.
    llvm::BasicBlock * funcBlock = createBasicBlock(m_currentFunction, "entry");
    m_irBuilder->SetInsertPoint(funcBlock);

    // createFunc() creates function arguments without names. We need to set argument names.
    size_t index = 0;
    for (auto argIt = m_currentFunction->arg_begin(); index < funcSymbol->argumentCount(); ++argIt, ++index)
    {
        auto functionArgumentSymbol = funcSymbol->getArgumentSymbol(index);
        // argIt->setName(functionArgumentSymbol->getName());

        // Program should be able to change function parameter in function body but not original function parameter value.
        // To allow this we need to create new local variables and copy argument values to new local vars and use it as func arguments.
        // This way program can't change original function parameter values.
        auto localFuncArgVar = m_irBuilder->CreateAlloca(createBaseType(functionArgumentSymbol->getType()), nullptr,
                                                         functionArgumentSymbol->getName());
        m_irBuilder->CreateStore(argIt, localFuncArgVar);
        functionArgumentSymbol->setProperty(std::make_unique<SymbolProperty>(localFuncArgVar));
    }

    visitChildren(node);

    // It's possible that the final basic block may not have a return instruction.
    // Note: This is a workaround solution until return path analysis is done in the semantic pass.
    if (m_irBuilder->GetInsertBlock()->getTerminator() == nullptr)
    {
        if (funcReturnType == scc::Type::kTypeVoid)
        {
            m_irBuilder->CreateRetVoid();
        }
        else
        {
            m_irBuilder->CreateRet(createConstant(funcReturnType, "0"));
        }
    }
    
    deleteUnreachableBasicBlocks(m_currentFunction);

    // DEBUG
    // m_currentFunction->viewCFG();

    m_currentFunction = nullptr;
    m_irBuilder->SetInsertPoint(prevBlock);
}


void CodeGenPass::visitBlock(ast::NodeBlock * node)
{
    visitChildren(node);
}


void CodeGenPass::visitIfStatement(ast::NodeIfStatement* node)
{
    //auto prevBlock = m_irBuilder->GetInsertBlock();

    auto condNode = node->getChild(0);
    auto thenNode = node->getChild(1);
    auto elseNode = node->childCount() == 3 ? node->getChild(2) : nullptr;

    // Generate code for the condition expression.
    auto conditionValue = loadIfPointerType(visit(condNode));

    // Generate blocks.
    auto thenBlock = createBasicBlock(m_currentFunction, "if.then");
    auto elseBlock = createBasicBlock(m_currentFunction, "if.else");
    auto continueBlock = createBasicBlock(m_currentFunction, "if.cont");
    m_irBuilder->CreateCondBr(conditionValue, thenBlock, elseBlock);

    // Generate code for the then statement.
    m_irBuilder->SetInsertPoint(thenBlock);
    visit(thenNode);
    m_irBuilder->CreateBr(continueBlock);

    m_irBuilder->SetInsertPoint(elseBlock);
    // Generate code only if there is an else statement.
    if (elseNode != nullptr)
    {
        visit(elseNode);
    }
    // Even if there is no else block, we create an else block to make the flow work properly.
    // The empty else block will be eliminated by the code optimizer.
    m_irBuilder->CreateBr(continueBlock);

    // New code generation should start in the continue block.
    m_irBuilder->SetInsertPoint(continueBlock);
}


void CodeGenPass::visitForStatement(ast::NodeForStatement * node)
{
    // There have to be at least 4 children: ForVarDec, ForCondition, ForIncrements, and ForCodeBlock
    assert(node->childCount() == 4);

    // for ( varDecl ; forCondition ; forIncrements ) forBody
    auto forVarDeclNode = node->getChild(0);
    auto forCondNode    = node->getChild(1);
    auto forIncsNode    = node->getChild(2);
    auto forBodyNode    = node->getChild(3);

    // Create basic blocks for loop construction.
    // Note: The reason we have an extra block (for.body) is that LLVM has a strict rule that every basic block
    //       has to end with a terminator (ret, br etc.) instruction, and each block can have only one terminator.
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
    auto forCondBlock = createBasicBlock(m_currentFunction, "for.cmp");
    auto forBodyBlock = createBasicBlock(m_currentFunction, "for.body");
    auto forIncBlock  = createBasicBlock(m_currentFunction, "for.inc");
    auto forExitBlock = createBasicBlock(m_currentFunction, "for.exit");

    // Push BasicBlocks onto the stack for this node. We may need these blocks to create branches
    // for continue, break, return etc. statements to create branches to jump to this node's blocks
    // if necessary.
    m_nodeBasicBlockStack.push(std::make_unique<NodeBasicBlockSet>(node, forCondBlock, forBodyBlock, forIncBlock, forExitBlock));

    // Generate code for variable declarations in the current block.
    visitChildren(forVarDeclNode);
    m_irBuilder->CreateBr(forCondBlock);

    // Generate code for 'for.cmp'

    m_irBuilder->SetInsertPoint(forCondBlock);

    if (forCondNode->childCount() > 0)
    {
        auto condValue = loadIfPointerType(visit(forCondNode->getChild(0)));
        m_irBuilder->CreateCondBr(condValue, forBodyBlock, forExitBlock);
    }
    else
    {
        // If there is no condition, then jump to the body.
        m_irBuilder->CreateBr(forBodyBlock);
    }

    // Generate code for 'for.body'
    m_irBuilder->SetInsertPoint(forBodyBlock);
    visit(forBodyNode);
    m_irBuilder->CreateBr(forIncBlock);

    // Generate code for 'for.Inc'

    m_irBuilder->SetInsertPoint(forIncBlock);

    if (forIncsNode->childCount() > 0)
    {
        visitChildren(forIncsNode);
    }

    m_irBuilder->CreateBr(forCondBlock);

    // Set the code generation block to for.exit

    m_irBuilder->SetInsertPoint(forExitBlock);

    // Pop BasicBlock info from the stack.
    m_nodeBasicBlockStack.pop();
}


void CodeGenPass::visitWhileStatement(ast::NodeWhileStatement * node)
{
    // There have to be 2 children: expr and body.
    assert(node->childCount() == 2);

    // while ( condition ) body
    auto condNode = node->getChild(0);
    auto bodyNode = node->getChild(1);

    // Create basic blocks for while loop construction.
    // Note: The reason we have an extra block (while.body) is that LLVM has a strict rule that every basic block
    //       has to end with a terminator (ret, br etc.) instruction, and each block can have only one terminator.
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
    auto condBlock = createBasicBlock(m_currentFunction, "while.cmp");
    auto bodyBlock = createBasicBlock(m_currentFunction, "while.body");
    auto exitBlock = createBasicBlock(m_currentFunction, "while.exit");

    // Push BasicBlocks onto the stack for this node. We may need these blocks to create branches
    // for continue, break, return etc. statements to create branches to jump to this node's blocks
    // if necessary.
    m_nodeBasicBlockStack.push(std::make_unique<NodeBasicBlockSet>(node, condBlock, bodyBlock, nullptr, exitBlock));

    // Jump from the current block to the condition block.
    m_irBuilder->CreateBr(condBlock);

    // Generate code for while.cmp

    m_irBuilder->SetInsertPoint(condBlock);

    auto condValue = loadIfPointerType(visit(condNode));
    m_irBuilder->CreateCondBr(condValue, bodyBlock, exitBlock);

    // Generate code for while.body
    m_irBuilder->SetInsertPoint(bodyBlock);
    visit(bodyNode);
    m_irBuilder->CreateBr(condBlock);

    // Set the code generation block to while.exit
    m_irBuilder->SetInsertPoint(exitBlock);

    // Pop BasicBlock info from the stack.
    m_nodeBasicBlockStack.pop();
}


void CodeGenPass::visitDoWhileStatement(ast::NodeDoWhileStatement * node)
{
    // There have to be 2 children: expr and body.
    assert(node->childCount() == 2);

    // do body while ( condition )
    auto bodyNode = node->getChild(0);
    auto condNode = node->getChild(1);

    // Create basic blocks for do while loop construction.
    // Note: The reason we have an extra block (do_while.body) is that LLVM has a strict rule that every basic block
    //       has to end with a terminator (ret, br etc.) instruction, and each block can have only one terminator.
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
    auto condBlock = createBasicBlock(m_currentFunction, "do_while.cmp");
    auto bodyBlock = createBasicBlock(m_currentFunction, "do_while.body");
    auto exitBlock = createBasicBlock(m_currentFunction, "do_while.exit");

    // Push BasicBlocks onto the stack for this node. We may need these blocks to create branches
    // for continue, break, return etc. statements to create branches to jump to this node's blocks
    // if necessary.
    m_nodeBasicBlockStack.push(std::make_unique<NodeBasicBlockSet>(node, condBlock, bodyBlock, nullptr, exitBlock));

    // Jump from the current block to the body block.
    m_irBuilder->CreateBr(bodyBlock);

    // Generate code for 'do_while.body'

    m_irBuilder->SetInsertPoint(bodyBlock);
    visit(bodyNode);
    m_irBuilder->CreateBr(condBlock);

    // Generate code for 'do_while.cmp'

    m_irBuilder->SetInsertPoint(condBlock);

    auto condValue = loadIfPointerType(visit(condNode));
    m_irBuilder->CreateCondBr(condValue, bodyBlock, exitBlock);

    // Set the code generation block to do_while.exit
    m_irBuilder->SetInsertPoint(exitBlock);

    // Pop BasicBlock info from the stack.
    m_nodeBasicBlockStack.pop();
}


void CodeGenPass::visitReturnStatement(ast::NodeReturnStatement * node)
{
    // If there is no child, then return void. The function return type is void.
    if (node->childCount() == 0)
    {
        m_irBuilder->CreateRetVoid();
    }
    else
    {
        // return <expression>
        auto exprValue = loadIfPointerType(visit(node->getChild(0)));
        m_irBuilder->CreateRet(exprValue);
    }
    // Any instructions after a terminator instruction (ret, br, switch, ...) won't be executed.
    // Creating a new block and generating all unreachable code in it allows the optimizer to eliminate it.
    auto unreachableBlock = createBasicBlock(m_currentFunction, "unreachable");
    m_irBuilder->SetInsertPoint(unreachableBlock);
}


void CodeGenPass::visitContinue(ast::NodeContinue * node)
{
    auto nodeBasicBlockSet = m_nodeBasicBlockStack.getOneOfNodeTypes({ast::NodeType::kForStatement,
                                                                      ast::NodeType::kWhileStatement,
                                                                      ast::NodeType::kDoWhileStatement});
    assert(nodeBasicBlockSet);
    
    switch (nodeBasicBlockSet->getNode()->getNodeType())
    {
        case ast::NodeType::kForStatement:
            m_irBuilder->CreateBr(nodeBasicBlockSet->getIncrementBasicBlock());
            break;

        case ast::NodeType::kWhileStatement:
        case ast::NodeType::kDoWhileStatement:
            m_irBuilder->CreateBr(nodeBasicBlockSet->getConditionBasicBlock());
            break;

        default:
            assert(false && "Unhandled node type!");
            break;
    }

    // Create a new basic block for unreachable instructions after the current continue statement.
    auto unreachableBasicBlock = createBasicBlock(m_currentFunction, "unreachable");
    m_irBuilder->SetInsertPoint(unreachableBasicBlock);
}


void CodeGenPass::visitBreak(ast::NodeBreak * node)
{
    auto nodeBasicBlockSet = m_nodeBasicBlockStack.getOneOfNodeTypes({ast::NodeType::kForStatement,
                                                                      ast::NodeType::kWhileStatement,
                                                                      ast::NodeType::kDoWhileStatement});
    assert(nodeBasicBlockSet);
    
    switch (nodeBasicBlockSet->getNode()->getNodeType())
    {
        case ast::NodeType::kForStatement:
        case ast::NodeType::kWhileStatement:
        case ast::NodeType::kDoWhileStatement:
            m_irBuilder->CreateBr(nodeBasicBlockSet->getExitBasicBlock());
            break;

        default:
            assert(false && "Unhandled node type!");
            break;
    }

    // Create a new basic block for unreachable instructions after the current continue statement.
    auto unreachableBasicBlock = createBasicBlock(m_currentFunction, "unreachable");
    m_irBuilder->SetInsertPoint(unreachableBasicBlock);
}


llvm::Value * CodeGenPass::visitFunctionCall(ast::NodeFunctionCall * node)
{
    std::vector<llvm::Value *> args;

    // Visit all function argument expressions.
    for (size_t index=0; index < node->childCount(); ++index)
    {
        auto argExprValue = visit(node->getChild(index));
        args.emplace_back(loadIfPointerType(argExprValue));
    }
    auto funcName = node->getFuncName();
    auto funcSymbol = static_cast<FunctionSymbol *>(node->getScope()->resolveSymbol(funcName));
    assert(funcSymbol != nullptr);
    
    auto func = static_cast<SymbolProperty *>(funcSymbol->getProperty())->getValue();
    assert(func != nullptr);

    auto funcPtr = llvm::dyn_cast<llvm::Function>(func);
    assert(funcPtr != nullptr);

    return m_irBuilder->CreateCall(funcPtr, args);
}


void CodeGenPass::visitAssignment(ast::NodeAssignment * node)
{
    // Get the variable's LLVM value
    auto variable = visit(node->getChild(0));

    // Generate code for the right expression and get the assignment value.
    auto rightExprValue = visit(node->getChild(1));

    //std::cout << "VarTypeID:" << debugLLVMTypeAsString(variable->getType()->getTypeID()) << std::endl;
    //std::cout << "BRightTypeID:" << debugLLVMTypeAsString(rightExprValue->getType()->getTypeID()) << std::endl;
    //std::cout << "ARightTypeID:" << debugLLVMTypeAsString(loadIfPointerType(rightExprValue)->getType()->getTypeID()) << std::endl;

    // We load the value from the rightExprValue address and store it at the variable address.
    m_irBuilder->CreateStore(loadIfPointerType(rightExprValue), variable);
}


llvm::Value * CodeGenPass::visitExplicitTypeConversion(ast::NodeExplicitTypeConversion * node)
{
    // Generate code for the expression.
    auto exprValue = loadIfPointerType(visit(node->getChild(0)));
    llvm::Value * convertedValue{nullptr};

    // Convert exprValue from Float to (int or bool)
    if (exprValue->getType()->getTypeID() == llvm::Type::TypeID::FloatTyID)
    {
        switch (node->getConversionType())
        {
            case Type::kTypeInt:
                convertedValue = m_irBuilder->CreateFPToSI(exprValue, createBaseType(Type::kTypeInt));
                break;

            case Type::kTypeBool:
                convertedValue = m_irBuilder->CreateFCmpUNE(exprValue, createConstant(scc::Type::kTypeFloat, "0"));
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

    // Convert exprValue from Int to (float or bool)
    if (exprValue->getType()->getTypeID() == llvm::Type::TypeID::IntegerTyID &&
        exprValue->getType()->getPrimitiveSizeInBits() == 32)
    {
        switch (node->getConversionType())
        {
            case Type::kTypeFloat:
                convertedValue = m_irBuilder->CreateSIToFP(exprValue, createBaseType(Type::kTypeFloat));
                break;

            case Type::kTypeBool:
                convertedValue = m_irBuilder->CreateICmpNE(exprValue, createConstant(scc::Type::kTypeInt, "0"));
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

    // Convert exprValue from Bool to (float or Int)
    if (exprValue->getType()->getTypeID() == llvm::Type::TypeID::IntegerTyID &&
        exprValue->getType()->getPrimitiveSizeInBits() == 1)
    {
        switch (node->getConversionType())
        {
            case Type::kTypeFloat:
                convertedValue = m_irBuilder->CreateUIToFP(exprValue, createBaseType(Type::kTypeFloat));
                break;

            case Type::kTypeInt:
                {
                    convertedValue = m_irBuilder->CreateZExt(exprValue, createBaseType(scc::Type::kTypeInt));
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


llvm::Value * CodeGenPass::visitLogicalNotOperator(ast::NodeLogicalOperator * node)
{
    auto exprValue = loadIfPointerType(visit(node->getChild(0)));
    auto exprType = exprValue->getType()->getTypeID();
    
    if (exprType == llvm::Type::TypeID::FloatTyID)
    {
        exprValue = m_irBuilder->CreateFCmpUNE(exprValue, createConstant(scc::Type::kTypeFloat, "0"));
        exprValue = m_irBuilder->CreateXor(exprValue, createConstant(scc::Type::kTypeBool, "true"));
        exprValue = m_irBuilder->CreateUIToFP(exprValue, createBaseType(scc::Type::kTypeFloat));
    }
    else if (exprType == llvm::Type::TypeID::IntegerTyID &&
             exprValue->getType()->getPrimitiveSizeInBits() == 32)
    {
        exprValue = m_irBuilder->CreateICmpNE(exprValue, createConstant(scc::Type::kTypeInt, "0"));
        exprValue = m_irBuilder->CreateXor(exprValue, createConstant(scc::Type::kTypeBool, "true"));
        exprValue = m_irBuilder->CreateZExt(exprValue, createBaseType(scc::Type::kTypeInt));
    }
    else if (exprType == llvm::Type::TypeID::IntegerTyID &&
             exprValue->getType()->getPrimitiveSizeInBits() == 1)
    {
        exprValue = m_irBuilder->CreateXor(exprValue, createConstant(scc::Type::kTypeBool, "true"));
    }
    else
    {
        assert(false && "Unknown type for logical not operator.");
    }

    return exprValue;
}


llvm::Value * CodeGenPass::visitLogicalAndOperator(ast::NodeLogicalOperator * node)
{
    auto leftExprNode  = node->getChild(0);
    auto rightExprNode = node->getChild(1);

    auto rightExprBlock = createBasicBlock(m_currentFunction, "&&.rightExpr");
    auto exitBlock = createBasicBlock(m_currentFunction, "&&.exit");

    // Generate code in current block.
    auto resultVar = m_irBuilder->CreateAlloca(createBaseType(scc::Type::kTypeBool), nullptr, "_cb");
    auto leftExprValue = loadIfPointerType(visit(leftExprNode));
    m_irBuilder->CreateStore(leftExprValue, resultVar);
    m_irBuilder->CreateCondBr(leftExprValue, rightExprBlock, exitBlock);

    // Generate code for rightExprBlock.
    m_irBuilder->SetInsertPoint(rightExprBlock);
    auto rightExprValue = loadIfPointerType(visit(rightExprNode));
    m_irBuilder->CreateStore(rightExprValue, resultVar);
    m_irBuilder->CreateBr(exitBlock);

    // Generate code for exitBlock.
    m_irBuilder->SetInsertPoint(exitBlock);

    return resultVar;
}


llvm::Value * CodeGenPass::visitLogicalOrOperator(ast::NodeLogicalOperator * node)
{
    auto leftExprNode  = node->getChild(0);
    auto rightExprNode = node->getChild(1);

    auto rightExprBlock = createBasicBlock(m_currentFunction, "&&.rightExpr");
    auto exitBlock = createBasicBlock(m_currentFunction, "&&.exit");

    // Generate code in current block.
    auto resultVar = m_irBuilder->CreateAlloca(createBaseType(scc::Type::kTypeBool), nullptr);
    auto leftExprValue = loadIfPointerType(visit(leftExprNode));
    m_irBuilder->CreateStore(leftExprValue, resultVar);
    m_irBuilder->CreateCondBr(leftExprValue, exitBlock, rightExprBlock);

    // Generate code for rightExprBlock.
    m_irBuilder->SetInsertPoint(rightExprBlock);
    auto rightExprValue = loadIfPointerType(visit(rightExprNode));
    m_irBuilder->CreateStore(rightExprValue, resultVar);
    m_irBuilder->CreateBr(exitBlock);

    // Generate code for exitBlock.
    m_irBuilder->SetInsertPoint(exitBlock);

    return resultVar;
}


llvm::Value * CodeGenPass::visitUnaryOperator(ast::NodeUnaryOperator * node)
{
    // Generate code for the right expression.
    auto exprValue = loadIfPointerType(visit(node->getChild(0)));
    llvm::Value * negatedValue{nullptr};

    // Nothing to do for '+' unary operation. Just return the expr value.
    if (node->getNodeType() == ast::NodeType::kUOPPlus)
    {
        return exprValue;
    }

    // Negate the value based on its type. After the semantic pass, only allowed types should reach this point.
    switch (exprValue->getType()->getTypeID())
    {
        case llvm::Type::TypeID::FloatTyID:
            negatedValue = m_irBuilder->CreateFMul(createConstant(scc::Type::kTypeFloat, "-1"), exprValue, "negtmp");
            break;

        case llvm::Type::TypeID::IntegerTyID:
            negatedValue = m_irBuilder->CreateMul(createConstant(scc::Type::kTypeInt, "-1"), exprValue, "negtmp");
            break;

        default:
            assert(false && "Unhandled type for unary operation.");
            break;
    }
    
    return negatedValue;
}


llvm::Value * CodeGenPass::visitComparisonOperator(ast::NodeComparisonOperator * node)
{
    llvm::Value * resultValue{nullptr};

    // Visit always returns a pointer to the value, so we need to load it to get the value from the pointed address.
    auto leftOperandValue = loadIfPointerType(visit(node->getChild(0)));
    auto rightOperandValue = loadIfPointerType(visit(node->getChild(1)));

    llvm::Type::TypeID leftOpTypeID = leftOperandValue->getType()->getTypeID();
    assert(rightOperandValue->getType()->getTypeID() == leftOpTypeID);

    if (leftOpTypeID == llvm::Type::FloatTyID)
    {
        switch (node->getNodeType())
        {
            case ast::NodeType::kCompOPEQ:
                resultValue = m_irBuilder->CreateFCmpOEQ(leftOperandValue, rightOperandValue);
                break;

            case ast::NodeType::kCompOPNEQ:
                resultValue = m_irBuilder->CreateFCmpONE(leftOperandValue, rightOperandValue);
                break;

            case ast::NodeType::kCompOPLE:
                resultValue = m_irBuilder->CreateFCmpOLE(leftOperandValue, rightOperandValue);
                break;

            case ast::NodeType::kCompOPGE:
                resultValue = m_irBuilder->CreateFCmpOGE(leftOperandValue, rightOperandValue);
                break;

            case ast::NodeType::kCompOPL:
                resultValue = m_irBuilder->CreateFCmpOLT(leftOperandValue, rightOperandValue);
                break;

            case ast::NodeType::kCompOPG:
                resultValue = m_irBuilder->CreateFCmpOGT(leftOperandValue, rightOperandValue);
                break;

            default:
                assert(false && "Unknown comparison node type.");
                break;
        }
    }
    else if (leftOpTypeID == llvm::Type::IntegerTyID)
    {
        switch (node->getNodeType())
        {
            case ast::NodeType::kCompOPEQ:
                resultValue = m_irBuilder->CreateICmpEQ(leftOperandValue, rightOperandValue);
                break;

            case ast::NodeType::kCompOPNEQ:
                resultValue = m_irBuilder->CreateICmpNE(leftOperandValue, rightOperandValue);
                break;

            case ast::NodeType::kCompOPLE:
                resultValue = m_irBuilder->CreateICmpSLE(leftOperandValue, rightOperandValue);
                break;

            case ast::NodeType::kCompOPGE:
                resultValue = m_irBuilder->CreateICmpSGE(leftOperandValue, rightOperandValue);
                break;

            case ast::NodeType::kCompOPL:
                resultValue = m_irBuilder->CreateICmpSLT(leftOperandValue, rightOperandValue);
                break;

            case ast::NodeType::kCompOPG:
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


llvm::Value * CodeGenPass::visitPrefixArithmeticOperator(ast::NodePrefixArithmeticOperator * node)
{
    llvm::Value * resultValue{nullptr};

    // Visit always returns a pointer to the value, so we need to load it to get the value from the pointed address.
    auto operandVar = visit(node->getChild(0));
    auto operandValue = loadIfPointerType(operandVar);

    auto opTypeID = operandValue->getType()->getTypeID();

    switch (node->getNodeType())
    {
        case ast::NodeType::kPrefixIncAOP:
            if (opTypeID == llvm::Type::FloatTyID)
                resultValue = m_irBuilder->CreateFAdd(operandValue, createConstant(Type::kTypeFloat, "1.0"), "faddtmp");
            else
                resultValue = m_irBuilder->CreateAdd(operandValue, createConstant(Type::kTypeInt, "1"), "addtmp");
            break;

        case ast::NodeType::kPrefixDecAOP:
            if (opTypeID == llvm::Type::FloatTyID)
                resultValue = m_irBuilder->CreateFSub(operandValue, createConstant(Type::kTypeFloat, "1.0"), "fsubtmp");
            else
                resultValue = m_irBuilder->CreateSub(operandValue, createConstant(Type::kTypeInt, "1"), "subtmp");
            break;

        default:
            assert(false && "Unknown node type");
            break;
    }

    m_irBuilder->CreateStore(resultValue, operandVar);

    return operandVar;
}


llvm::Value * CodeGenPass::visitArithmeticOperator(ast::NodeArithmeticOperator * node)
{
    llvm::Value * resultValue{nullptr};

    // Visit always returns a pointer to the value, so we need to load it to get the value from the pointed address.
    auto leftOperandValue = loadIfPointerType(visit(node->getChild(0)));
    auto rightOperandValue = loadIfPointerType(visit(node->getChild(1)));

    //std::cout << "BeforeLeftTypeID:" << debugLLVMTypeAsString(leftOperandValue->getType()->getTypeID()) << std::endl;
    //std::cout << "BeforeRightTypeID:" << debugLLVMTypeAsString(rightOperandValue->getType()->getTypeID()) << std::endl;

    // Type promotion should be done here.
    llvm::Type::TypeID leftOpTypeID = leftOperandValue->getType()->getTypeID();
    //llvm::Type::TypeID rightOpTypeID = rightOperandValue->getType()->getTypeID();

    switch (node->getNodeType())
    {
        case ast::NodeType::kAOPMul:
            if (leftOpTypeID == llvm::Type::FloatTyID)
                resultValue = m_irBuilder->CreateFMul(leftOperandValue, rightOperandValue, "fmultmp");
            else
                resultValue = m_irBuilder->CreateMul(leftOperandValue, rightOperandValue, "multmp");
            break;

        case ast::NodeType::kAOPDiv:
            if (leftOpTypeID == llvm::Type::FloatTyID)
                resultValue = m_irBuilder->CreateFDiv(leftOperandValue, rightOperandValue, "fdivtmp");
            else
                resultValue = m_irBuilder->CreateSDiv(leftOperandValue, rightOperandValue, "sdivtmp");
            break;

        case ast::NodeType::kAOPAdd:
            if (leftOpTypeID == llvm::Type::FloatTyID)
                resultValue = m_irBuilder->CreateFAdd(leftOperandValue, rightOperandValue, "faddtmp");
            else
                resultValue = m_irBuilder->CreateAdd(leftOperandValue, rightOperandValue, "addtmp");
            break;

        case ast::NodeType::kAOPSub:
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


llvm::Value * CodeGenPass::visitLiteral(ast::NodeLiteral * node)
{
    llvm::Value * literalValue{nullptr};
    
    switch (node->getNodeType())
    {
        case ast::NodeType::kLiteralFloat:
            {
                // We create a temp local variable and assign a constant value.
                auto localVar = m_irBuilder->CreateAlloca(createBaseType(scc::Type::kTypeFloat), nullptr, "_ci");
                // Since we store a constant, we don't need to load the value from an address.
                m_irBuilder->CreateStore(createConstant(scc::Type::kTypeFloat, node->getValue()), localVar);
                // Returns a pointer to the local variable.
                literalValue = localVar;
            }
            break;

        case ast::NodeType::kLiteralInt32:
            {
                // We create a temp local variable and assign a constant value.
                auto localVar = m_irBuilder->CreateAlloca(createBaseType(scc::Type::kTypeInt), nullptr, "_cf");
                // Since we store a constant, we don't need to load the value from an address.
                m_irBuilder->CreateStore(createConstant(scc::Type::kTypeInt, node->getValue()), localVar);
                // Returns a pointer to the local variable.
                literalValue = localVar;
            }
            break;

        case ast::NodeType::kLiteralBool:
            {
                // We create a temp local variable and assign a constant value.
                auto localVar = m_irBuilder->CreateAlloca(createBaseType(scc::Type::kTypeBool), nullptr, "_cb");
                // Since we store a constant, we don't need to load the value from an address.
                m_irBuilder->CreateStore(createConstant(scc::Type::kTypeBool, node->getValue()), localVar);
                // Returns a pointer to the local variable.
                literalValue = localVar;
            }
            break;

        case ast::NodeType::kLiteralID:
            {
                // Returns the llvm value object of the variable, which is stored as a symbol property in the symbol object.
                // The llvm object is referring to the variable pointer. It needs to be loaded to access the value of the variable.
                auto symbol = node->getScope()->resolveSymbol(node->getValue());
                literalValue = static_cast<SymbolProperty *>(symbol->getProperty())->getValue();
            }
            break;

        default:
            assert(false && "Unknown node type.");
            break;
    }

    return literalValue;
}


void CodeGenPass::createInternalInitializerFunction()
{
    // Save the current block.
    llvm::BasicBlock *  prevBlock = m_irBuilder->GetInsertBlock();

    // No arguments are required.
    std::vector<llvm::Type *> argTypes;

    // Create the initializer function.
    m_initFunction = createFunc(*m_irBuilder, Type::kTypeVoid, "__initGlobalVariables__", argTypes);

    // Create a basic block for the function.
    m_initFunctionBlock = createBasicBlock(m_initFunction, "entry");

    // Restore the previous block.
    m_irBuilder->SetInsertPoint(prevBlock);
}


void CodeGenPass::finalizeInternalInitializerFunction()
{
    // Finalize the global variable initialization code.
    auto prevBlock = m_irBuilder->GetInsertBlock();
    m_irBuilder->SetInsertPoint(m_initFunctionBlock);
    m_irBuilder->CreateRetVoid();
    m_irBuilder->SetInsertPoint(prevBlock);
}


llvm::Type * CodeGenPass::createBaseType(scc::Type type)
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


llvm::Constant * CodeGenPass::createConstant(scc::Type type, const std::string & value)
{
    assert(!value.empty());

    switch(type)
    {
        case scc::Type::kTypeInt:
            return llvm::ConstantInt::get(*m_context, llvm::APInt(32, uint32_t(atoi(value.c_str())), true));

        case scc::Type::kTypeFloat:
            return llvm::ConstantFP::get(*m_context, llvm::APFloat(float(atof(value.c_str()))));

        case scc::Type::kTypeBool:
            return llvm::ConstantInt::get(*m_context, llvm::APInt(1, value == "true" ? 1 : 0, false));

        default:
            assert(false && "Unknown type.");
            break;
    }

    return nullptr;
}


llvm::GlobalVariable * CodeGenPass::createGlobalVariable(std::string name, scc::Type type)
{
    m_module->getOrInsertGlobal(name, createBaseType(type));
    auto gVar = m_module->getNamedGlobal(name);
    gVar->setLinkage(llvm::GlobalValue::CommonLinkage);
    gVar->setAlignment(llvm::MaybeAlign(sizeof(void*)));
    gVar->setInitializer(createConstant(type, "0"));

    return gVar;
}


llvm::Function * CodeGenPass::createFunc(LLVMIRBuilder & Builder,
                                         scc::Type returnType,
                                         const std::string & name,
                                         std::vector<llvm::Type *> & argTypes)
{
    auto funcType = llvm::FunctionType::get(createBaseType(returnType), argTypes, false);
    // The ExternalLinkage enumeration member means that the function can be referred to from other modules.
    auto func = llvm::Function::Create(funcType, llvm::Function::ExternalLinkage, name, m_module.get());

    return func;
}


llvm::BasicBlock * CodeGenPass::createBasicBlock(llvm::Function * func, const std::string & name)
{
    return llvm::BasicBlock::Create(*m_context, name, func);
}


llvm::Value * CodeGenPass::loadIfPointerType(llvm::Value * value)
{
    if (value->getType()->getTypeID() == llvm::Type::PointerTyID)
    {
        return m_irBuilder->CreateLoad(value);
    }

    return value;
}


void CodeGenPass::dumpIRCode() const
{
    // REQUIRES to build LLVM in debug mode.
    // m_module->dump();
}


void CodeGenPass::deleteUnreachableBasicBlocks(llvm::Function * function)
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

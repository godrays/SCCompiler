//
//  Created by Arkin Terli on 4/13/18.
//  Copyright © 2018-Present, Arkin Terli. All rights reserved.
//

// Project includes
#include "ASTVisualizer.hpp"
#include "AST.hpp"
// External includes
// System includes
#include <cassert>
#include <sstream>


using namespace scc;


void ASTVisualizer::generateDOTFile(ast::Node * node, const std::string & filename)
{
    // Open dot file.
    m_outputFile.open(filename);

    // Write Graphiviz DOT graph configuration
    m_outputFile << "digraph g" << std::endl
                 << "{"
                 << "\tnode [shape = record,height=.05];"
                 << std::endl;

    // visit each node and output node details to file.
    visit(node);

    // Complete the dot configuration.
    m_outputFile << "}" << std::endl;

    // Close dot file.
    m_outputFile.close();
}


void ASTVisualizer::visit(ast::Node * node)
{
    // Output node-specific data to dot file.
    switch(node->getNodeType())
    {
        case ast::NodeType::kNodeTypeProgram:
            outputConfig(node, "[label = \"Program\"];");
            break;
    
        case ast::NodeType::kNodeTypeVariableDeclaration:
            outputConfigVariableDecl(node);
            break;

        case ast::NodeType::kNodeTypeFunctionDeclaration:
            outputConfigFuncDecl(node);
            break;

        case ast::NodeType::kNodeTypeBlock:
            outputConfig(node, "[label = \"Block\"];");
            break;

        case ast::NodeType::kNodeTypeIfStatement:
            outputConfig(node, "[label = \"If\"];");
            break;

        case ast::NodeType::kNodeTypeForStatement:
            outputConfig(node, "[label = \"For\"];");
            break;

        case ast::NodeType::kNodeTypeForVarDecl:
            outputConfig(node, "[label = \"ForVarDecl\"];");
            break;

        case ast::NodeType::kNodeTypeForCondition:
            outputConfig(node, "[label = \"ForCondition\"];");
            break;

        case ast::NodeType::kNodeTypeForIncrement:
            outputConfig(node, "[label = \"ForIncrement\"];");
            break;

        case ast::NodeType::kNodeTypeWhileStatement:
            outputConfig(node, "[label = \"While\"];");
            break;

        case ast::NodeType::kNodeTypeDoWhileStatement:
            outputConfig(node, "[label = \"Do While\"];");
            break;

        case ast::NodeType::kNodeTypeReturnStatement:
            outputConfig(node, "[label = \"Func Return\"];");
            break;

        case ast::NodeType::kNodeTypeContinue:
            outputConfig(node, "[label = \"Continue\"];");
            break;

        case ast::NodeType::kNodeTypeBreak:
            outputConfig(node, "[label = \"Break\"];");
            break;

        case ast::NodeType::kNodeTypeFuncCall:
            outputConfig(node, "[label = \"Func Call: " + dynamic_cast<ast::NodeFuncCall*>(node)->GetFuncName() + "\"];");
            break;

        case ast::NodeType::kNodeTypeAssignment:
            outputConfig(node, "[label = \"=\"];");
            break;

        case ast::NodeType::kNodeTypeExplicitTypeConversion:
            outputConfig(node, "[label = \"ExplTypeConv To: " + ast::TypeToString(dynamic_cast<ast::NodeExplicitTypeConversion*>(node)->GetConversionType()) + "\"];");
            break;

        case ast::NodeType::kNodeTypeLogicalNotOP:
            outputConfig(node, "[label = \"!\"];");
            break;

        case ast::NodeType::kNodeTypeLogicalAndOP:
            outputConfig(node, "[label = \"&&\"];");
            break;

        case ast::NodeType::kNodeTypeLogicalOrOP:
            outputConfig(node, "[label = \"||\"];");
            break;

        case ast::NodeType::kNodeTypeUOPPlus:
            outputConfig(node, "[label = \"UnaryOP: +\"];");
            break;

        case ast::NodeType::kNodeTypeUOPMinus:
            outputConfig(node, "[label = \"UnaryOP: -\"];");
            break;

        case ast::NodeType::kNodeTypeCompOPEQ:
            outputConfig(node, "[label = \"Cmp EQ\"];");
            break;

        case ast::NodeType::kNodeTypeCompOPNEQ:
            outputConfig(node, "[label = \"Cmp NE\"];");
            break;

        case ast::NodeType::kNodeTypeCompOPLE:
            outputConfig(node, "[label = \"Cmp LE\"];");
            break;

        case ast::NodeType::kNodeTypeCompOPGE:
            outputConfig(node, "[label = \"Cmp GE\"];");
            break;

        case ast::NodeType::kNodeTypeCompOPL:
            outputConfig(node, "[label = \"Cmp LT\"];");
            break;

        case ast::NodeType::kNodeTypeCompOPG:
            outputConfig(node, "[label = \"Cmp GT\"];");
            break;

        case ast::NodeType::kNodeTypePrefixIncAOP:
            outputConfig(node, "[label = \"++\"];");
            break;

        case ast::NodeType::kNodeTypePrefixDecAOP:
            outputConfig(node, "[label = \"--\"];");
            break;

        case ast::NodeType::kNodeTypeAOPMul:
            outputConfig(node, "[label = \"*\"];");
            break;

        case ast::NodeType::kNodeTypeAOPDiv:
            outputConfig(node, "[label = \"/\"];");
            break;

        case ast::NodeType::kNodeTypeAOPAdd:
             outputConfig(node, "[label = \"+\"];");
            break;

        case ast::NodeType::kNodeTypeAOPSub:
            outputConfig(node, "[label = \"-\"];");
            break;

        case ast::NodeType::kNodeTypeLiteralFloat:
            outputConfig(node, "[label = \"Float: " + dynamic_cast<ast::NodeLiteral*>(node)->GetValue() + "\"];");
            break;

        case ast::NodeType::kNodeTypeLiteralInt32:
            outputConfig(node, "[label = \"Int: " + dynamic_cast<ast::NodeLiteral*>(node)->GetValue() + "\"];");
            break;

        case ast::NodeType::kNodeTypeLiteralBool:
            outputConfig(node, "[label = \"Bool: " + dynamic_cast<ast::NodeLiteral*>(node)->GetValue() + "\"];");
            break;

        case ast::NodeType::kNodeTypeLiteralID:
            outputConfig(node, "[label = \"Variable: " + dynamic_cast<ast::NodeLiteral*>(node)->GetValue() + "\"];");
            break;

        default:
            assert(false && "Unknown node type in ASTVisualizer.");
            break;
    }

    // visit node children.
    for (size_t index=0; index<node->childCount(); ++index)
    {
        visit(node->getChild(index));
    }
}


void ASTVisualizer::outputConfig(ast::Node * node, const std::string & nodeConfig)
{
    // Write node's address configuration.
    m_outputFile << "\tnode_" << std::hex << node << " " << nodeConfig << std::endl;

    // Write node's child connections.
    for (size_t index=0; index < node->childCount(); ++index)
    {
        m_outputFile << "\tnode_" << std::hex << node << " -> "
                     << "node_" << std::hex << node->getChild(index) << ";" << std::endl;
    }
}


void ASTVisualizer::outputConfigVariableDecl(ast::Node *  node)
{
    auto varDecNode = dynamic_cast<ast::NodeVarDeclaration *>(node);
    assert(varDecNode != nullptr);
    
    // Generate config string.
    std::ostringstream  strStream;
    strStream   << "[label = \"{Variable Decl |" << ast::TypeToString(varDecNode->GetVarType())
                << " " << varDecNode->GetVarName() << "}\"];" << std::endl;

    outputConfig(node, strStream.str());
}


void ASTVisualizer::outputConfigFuncDecl(ast::Node * node)
{
    auto funcDecNode = dynamic_cast<ast::NodeFuncDeclaration *>(node);
    assert(funcDecNode != nullptr);
    auto arguments = funcDecNode->GetArguments();
    
    // Generate config string.
    std::ostringstream  strStream;
    strStream   << "[label = \"{Func Decl |" << funcDecNode->GetFuncName() << "| Return Type: " << ast::TypeToString(funcDecNode->GetReturnType());
    
    // Write arguments.
    for (auto & argument : arguments)
    {
        strStream << "| Arg: " << ast::TypeToString(argument.getType()) << " " << argument.getName() ;
    }
    
    strStream   << "}\"];" << std::endl;

    outputConfig(node, strStream.str());
}


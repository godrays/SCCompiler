//
//  ASTVisualizer.cpp
//
//  Created by Arkin Terli on 4/13/18.
//  Copyright © 2018 Arkin Terli. All rights reserved.
//

#include <cassert>
#include <sstream>

#include "AST.hpp"
#include "ASTVisualizer.hpp"

using namespace scc;


#pragma mark - ASTVisualizer Implementations.

void ASTVisualizer::GenerateDOTFile(ast::Node * node, std::string filename)
{
    // Open dot file.
    m_outputFile.open(filename);

    // Write Graphiviz DOT graph configuration
    m_outputFile << "digraph g" << std::endl
                 << "{"
                 << "\tnode [shape = record,height=.05];"
                 << std::endl;

    // Visit each node and output node deteils to file.
    Visit(node);

    // Complete the dot configuration.
    m_outputFile << "}" << std::endl;

    // Close dot file.
    m_outputFile.close();
}


void ASTVisualizer::Visit(ast::Node * node)
{
    // Output node specific data to dot file.
    switch(node->GetNodeType())
    {
        case ast::NodeType::kNodeTypeProgram:
            OutputConfig(node, "[label = \"Program\"];");
            break;
    
        case ast::NodeType::kNodeTypeVariableDeclaration:
            OutputConfigVariableDecl(node);
            break;

        case ast::NodeType::kNodeTypeFunctionDeclaration:
            OutputConfigFuncDecl(node);
            break;

        case ast::NodeType::kNodeTypeBlock:
            OutputConfig(node, "[label = \"Block\"];");
            break;

        case ast::NodeType::kNodeTypeReturnStatement:
            OutputConfig(node, "[label = \"Func Return\"];");
            break;

        case ast::NodeType::kNodeTypeFuncCall:
            OutputConfig(node, "[label = \"Func Call: " + dynamic_cast<ast::NodeFuncCall*>(node)->GetFuncName() + "\"];");
            break;

        case ast::NodeType::kNodeTypeAssignment:
            OutputConfig(node, "[label = \"=\"];");
            break;

        case ast::NodeType::kNodeTypeAOPMul:
            OutputConfig(node, "[label = \"*\"];");
            break;

        case ast::NodeType::kNodeTypeAOPDiv:
            OutputConfig(node, "[label = \"/\"];");
            break;

        case ast::NodeType::kNodeTypeAOPAdd:
             OutputConfig(node, "[label = \"+\"];");
            break;

        case ast::NodeType::kNodeTypeAOPSub:
            OutputConfig(node, "[label = \"-\"];");
            break;

        case ast::NodeType::kNodeTypeLiteralFloat:
            OutputConfig(node, "[label = \"Float: " + dynamic_cast<ast::NodeLiteral*>(node)->GetValue() + "\"];");
            break;

        case ast::NodeType::kNodeTypeLiteralInt32:
            OutputConfig(node, "[label = \"Int: " + dynamic_cast<ast::NodeLiteral*>(node)->GetValue() + "\"];");
            break;

        case ast::NodeType::kNodeTypeLiteralBool:
            OutputConfig(node, "[label = \"Bool: " + dynamic_cast<ast::NodeLiteral*>(node)->GetValue() + "\"];");
            break;

        case ast::NodeType::kNodeTypeLiteralID:
            OutputConfig(node, "[label = \"Variable: " + dynamic_cast<ast::NodeLiteral*>(node)->GetValue() + "\"];");
            break;

        default:
            assert(false && "Unknown node type in ASTVisualizer.");
            break;
    }

    // Visit node children.
    for (size_t index=0; index<node->ChildCount(); ++index)
    {
        Visit(node->GetChild(index));
    }
}


void ASTVisualizer::OutputConfig(ast::Node * node, const std::string & nodeConfig)
{
    // Write node's address configuration.
    m_outputFile << "\tnode_" << std::hex << node << " " << nodeConfig << std::endl;

    // Write node's child connections.
    for (size_t index=0; index < node->ChildCount(); ++index)
    {
        m_outputFile << "\tnode_" << std::hex << node << " -> "
                     << "node_" << std::hex << node->GetChild(index) << ";" << std::endl;
    }
}


void ASTVisualizer::OutputConfigVariableDecl(ast::Node *  node)
{
    auto varDecNode = dynamic_cast<ast::NodeVarDeclaration *>(node);
    assert(varDecNode != nullptr);
    
    // Generate config string.
    std::ostringstream  strStream;
    strStream   << "[label = \"{Variable Decl |" << ast::TypeToString(varDecNode->GetVarType())
                << " " << varDecNode->GetVarName() << "}\"];" << std::endl;

    OutputConfig(node, strStream.str());
}


void ASTVisualizer::OutputConfigFuncDecl(ast::Node * node)
{
    auto funcDecNode = dynamic_cast<ast::NodeFuncDeclaration *>(node);
    assert(funcDecNode != nullptr);
    auto arguments = funcDecNode->GetArguments();
    
    // Generate config string.
    std::ostringstream  strStream;
    strStream   << "[label = \"{Func Decl |" << funcDecNode->GetFuncName() << "| Return Type: " << ast::TypeToString(funcDecNode->GetReturnType());
    
    // Write arguments.
    for (size_t index=0; index < arguments.size(); ++index)
    {
        strStream << "| Arg: " << ast::TypeToString(arguments[index].GetType()) << " " << arguments[index].GetName() ;
    }
    
    strStream   << "}\"];" << std::endl;

    OutputConfig(node, strStream.str());
}


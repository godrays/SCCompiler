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

using namespace SCCompiler;


#pragma mark - ASTVisualizer Implementations.


void ASTVisualizer::GenerateDOTFile(AST::Node * node, std::string filename)
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


void ASTVisualizer::Visit(AST::Node * node)
{
    // Output node specific data to dot file.
    switch(node->GetNodeType())
    {
        case AST::NodeType::tNodeTypeProgram:
            OutputConfig(node, "[label = \"Program\"];");
            break;
    
        case AST::NodeType::tNodeTypeVariableDeclaration:
            OutputConfigVariableDecl(node);
            break;

        case AST::NodeType::tNodeTypeFunctionDeclaration:
            OutputConfigFuncDecl(node);
            break;

        case AST::NodeType::tNodeTypeBlock:
            OutputConfig(node, "[label = \"Block\"];");
            break;

        case AST::NodeType::tNodeTypeReturnStatement:
            OutputConfig(node, "[label = \"Func Return\"];");
            break;

        case AST::NodeType::tNodeTypeFuncCall:
            OutputConfig(node, "[label = \"Func Call: " + dynamic_cast<AST::NodeFuncCall*>(node)->GetFuncName() + "\"];");
            break;

        case AST::NodeType::tNodeTypeAssignment:
            OutputConfig(node, "[label = \"=\"];");
            break;

        case AST::NodeType::tNodeTypeAOPMul:
            OutputConfig(node, "[label = \"*\"];");
            break;

        case AST::NodeType::tNodeTypeAOPDiv:
            OutputConfig(node, "[label = \"/\"];");
            break;

        case AST::NodeType::tNodeTypeAOPAdd:
             OutputConfig(node, "[label = \"+\"];");
            break;

        case AST::NodeType::tNodeTypeAOPSub:
            OutputConfig(node, "[label = \"-\"];");
            break;

        case AST::NodeType::tNodeTypeLiteralFloat:
            OutputConfig(node, "[label = \"Float: " + dynamic_cast<AST::NodeLiteral*>(node)->GetValue() + "\"];");
            break;

        case AST::NodeType::tNodeTypeLiteralInt32:
            OutputConfig(node, "[label = \"Int: " + dynamic_cast<AST::NodeLiteral*>(node)->GetValue() + "\"];");
            break;

        case AST::NodeType::tNodeTypeLiteralBool:
            OutputConfig(node, "[label = \"Bool: " + dynamic_cast<AST::NodeLiteral*>(node)->GetValue() + "\"];");
            break;

        case AST::NodeType::tNodeTypeLiteralID:
            OutputConfig(node, "[label = \"Variable: " + dynamic_cast<AST::NodeLiteral*>(node)->GetValue() + "\"];");
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


void ASTVisualizer::OutputConfig(AST::Node * node, const std::string & nodeConfig)
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


void ASTVisualizer::OutputConfigVariableDecl(AST::Node *  node)
{
    auto varDecNode = dynamic_cast<AST::NodeVarDeclaration *>(node);
    assert(varDecNode != nullptr);
    
    // Generate config string.
    std::ostringstream  strStream;
    strStream   << "[label = \"{Variable Decl |" << AST::TypeToString(varDecNode->GetVarType())
                << " " << varDecNode->GetVarName() << "}\"];" << std::endl;

    OutputConfig(node, strStream.str());
}


void ASTVisualizer::OutputConfigFuncDecl(AST::Node * node)
{
    auto funcDecNode = dynamic_cast<AST::NodeFuncDeclaration *>(node);
    assert(funcDecNode != nullptr);
    auto arguments = funcDecNode->GetArguments();
    
    // Generate config string.
    std::ostringstream  strStream;
    strStream   << "[label = \"{Func Decl |" << funcDecNode->GetFuncName() << "| Return Type: " << AST::TypeToString(funcDecNode->GetReturnType());
    
    // Write arguments.
    for (size_t index=0; index < arguments.size(); ++index)
    {
        strStream << "| Arg: " << AST::TypeToString(arguments[index].GetType()) << " " << arguments[index].GetName() ;
    }
    
    strStream   << "}\"];" << std::endl;

    OutputConfig(node, strStream.str());
}


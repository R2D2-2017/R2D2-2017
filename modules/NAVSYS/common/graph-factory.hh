/**
 * \file
 * \brief     This file includes contains the definitions for the graphfactory class
 * \author    Jeremy
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See LICENSE
 */

#pragma once

#include <string>
#include <vector>
#include "graph.hh"
#include "node.hh"


class GraphFactory {
private:
    /**
     * \brief    This function finds a node in the node  vector by name
     * \param[in] name, name of node
     * \param[in] nodes, list of nodes
     * \return  it  iterator to node element
     */
    Node getNodeByName(const std::string &name, std::vector<Node> nodes);


    /**
     * \brief    This function asks the factory to create nodes based on the nodes file
     *
     *  This function handle the parsing of lines found in the nodes file and the creation of nodes
     *
     * This function wil keep getting lines from the file from which it wil extract the nodes information.
     * This information is stored in strings named after the information they contain.
     * After parsing a line from the file, a nodes object is created with the data found.
     * This created nodes is then passed to the graph.
     * This repeats until there are no more lines in the file.
     *
     * !!!
     * If the user enters an entry directly in the file itself, make sure not to end the last
     * with a new line. This will cause the node factory to read an additional empty entry and store it.
     * This causes undefined behavior when iterating over elements in other functions.
     * !!!
     *
     * \param[in]nodeFilePath path to node file
     * \return nodes  vector with vertice elements filled.
     */
    std::vector<Node>  RunNodeFactory(const std::string &nodeFilePath);



    /**
     * \brief This function asks the factory to create vertices based on the vertice file
     *
     * This function handle the parsing of lines found in the vertice file and the creation of vertices
     *
     * This function wil keep getting lines from the file from which it wil extract the vertice information.
     * This information is stored in strings named after the information they contain.
     * After parsing a line from the file, a vertice object is created with the data found.
     * in the case of the involved nodes this is done by calling the graph to return the *ptr to the nodes  in the vertice.
     * This is done based on node id.
     * This created vertice is then passed to the graph.
     * This repeats until there are no more lines in the file.
     *
     * !!!
     * If the user enters an entry directly in the file itself, make sure not to end the last
     * with a new line. This will cause the vertice factory to read an additional empty entry and store it.
     * This causes undefined behavior when iterating over elements in other functions.
     * !!!
     * 
     * \param[in]verticeFilePath path to vertice file
     * \param[in]nodes list of nodes
     * 
     * \return  vertices  vector with vertice elements filled.
     */
    std::vector<Vertice> RunVerticeFactory(const std::string &verticeFilePath, std::vector<Node> nodes);


public:
    /**
     * \brief    This function asks the factory to create a graph
     * 
     * \param[in] nodeFilePath Path to node file
     * \param[in] verticeFilePath Path to vertice file
     * \param[in] graph Reference to the graph to be filled by the factory
     * \param[out] graph Reference to the filled graph
     */
    void createGraph(const std::string &nodeFilePath, const std::string &verticeFilePath, Graph & graph);
    
};

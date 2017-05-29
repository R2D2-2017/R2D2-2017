/**
 * \file
 * \brief     This file includes contains the definitions for the graphfactory class
 * \author    Jeremy
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See LICENSE
 */

#ifndef NAVSYS_GRAPHFACTORY_HH
#define NAVSYS_GRAPHFACTORY_HH
#include <iostream>
#include <fstream>
#include <vector>
#include "graph.hh"
#include "node.hh"

using namespace std;

class GraphFactory {
private:


/**
 * \brief    This function finds a node in the node  vector by name
 * \param[in] name name of node
 * \return  it  iterator to node element
 */
    std::vector<Node>::iterator getNodeByName(std::string name, std::vector<Node> nodes);


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
 * \return nodes  vector with vertice elements filled.
 */
    std::vector<Node>  RunNodeFactory(std::string nodeFilePath);



/**
 * \brief    This function asks the factory to create vertices based on the vertice file
 *
 *  This function handle the parsing of lines found in the vertice file and the creation of vertices
 *
 *This function wil keep getting lines from the file from which it wil extract the vertice information.
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
 * \return  vertices  vector with vertice elements filled.
 */
    std::vector<Vertice> RunVerticeFactory(std::string verticeFilePath, std::vector<Node> nodes);


public:


/**
 * \brief    This function asks the factory to create a graph
 * \return graph a pointer to the new created graph by the factory
 */
    Graph* createGraph(std::string nodeFilePath,std::string verticeFilePath);


};


#endif //NAVSYS_GRAPHFACTORY_HH


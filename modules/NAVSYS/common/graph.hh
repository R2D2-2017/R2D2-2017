/**
 * \file
 * \brief     The definition of the graph class
 * \author    Robert
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See LICENSE
 */
#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "node.hh"
#include "vertice.hh"

/**
 * \brief Graph class
 * \details
 * Container class for nodes and vertices in the same graph
 */

class Graph {
private:
    std::vector<Node> nodes;
    std::vector<Vertice> vertices;

public:

    /**
     * \brief Add node to graph
     * \param node node to add
     */
    void addNode(const Node node);

    /**
     * \brief Remove node from graph
     * \param node node to remove
     */
    void removeNode(const Node node);

    /**
     * \brief Add vertice to graph
     * \param vertice vertice to add
     */
    void addVertice(const Vertice vertice);

    /**
     * \brief Remove vertice from graph
     * \param vertice vertice to remove
     */
    void removeVertice(const Vertice vertice);

    /**
     * \brief Check if node is in graph
     * \param node to check
     * \return true if node is in graph
     */
    bool containsNode(const Node node);

    /**
     * \brief Check if vertice is in graph
     * \param vertice vertice to check
     * \return true if vertice is in graph
     */
    bool containsVertice(const Vertice vertice);

    /**
     * Get a vector with all nodes in the graph
     * \return vector of all nodes
     */
    std::vector<Node>  getNodes();

    /**
     * Get a vector with all vertices in the graph
     * \return all vertices
     */
    std::vector<Vertice>  getVertices();

    /**
    * \brief function to set the nodes vector
    */
    void setNodes(std::vector<Node>  newNodes);

    /**
    * \brief function to set the vertice vector
    */
    void setVertices(std::vector<Vertice>  newVertices);

    /**
    * \brief function to get a element of the nodes vector by name
    */
    Node &getNodeByName(std::string name);

    /**
    * \brief function to write the graph to the disk at the specified filepaths.
    * \param [in]nodeFilePath the node filepath
    * \param [in]verticeFilePath the vertice filepath
    */
    void dumpGraphToDisk(const std::string nodeFilePath, const std::string verticeFilePath);
};

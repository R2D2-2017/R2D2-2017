/**
 * \file      graph.hh
 * \brief     The definition of the graph class.
 * \author    Robert
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See LICENSE
 */

#pragma once

#include <string>
#include <vector>
#include "node.hh"
#include "vertice.hh"

/**
 * \brief Graph class
 *
 * \details
 * Container class for nodes and vertices in the same graph.
 */
class Graph {
private:
    std::vector<Node> nodes;
    std::vector<Vertice> vertices;
public:
    /**
     * \brief Adds a node to  the graph.
     *
     * \param[in] node Node to add
     */
    void addNode(const Node & node);

    /**
     * \brief Removes a node from the graph.
     *
     * \param[in] node Node to remove
     */
    void removeNode(const Node & node);

    /**
     * \brief Adds a vertice to the graph.
     *
     * \param[in] vertice Vertice to add
     */
    void addVertice(const Vertice & vertice);

    /**
     * \brief Removes a vertice from the graph.
     *
     * \param[in] vertice Vertice to remove
     */
    void removeVertice(const Vertice & vertice);

    /**
     * \brief Checks if node is in the graph.
     *
     * \param[in] node The node to check
     *
     * \return True if node is in graph
     */
    bool containsNode(const Node & node);

    /**
     * \brief Checks if vertice is in the graph.
     *
     * \param[in] vertice Vertice to check
     *
     * \return True if vertice is in graph
     */
    bool containsVertice(const Vertice & vertice);

    /**
     * \brief Gets a vector containing all nodes in the graph.
     *
     * \return Vector of all nodes
     */
    std::vector<Node>  getNodes();

    /**
     * \brief Gets a vector containing all vertice from the graph.
     *
     * \return All vertices
     */
    std::vector<Vertice>  getVertices();

    /**
     * \brief Function to set the nodes vector.
     *
     * \param[in] newNodes The vector with the new nodes
     */
    void setNodes(std::vector<Node>  newNodes);

    /**
     * \brief Function to set the vertice vector.
     *
     * \param[in] newVertices The vector with the new vertices
     */
    void setVertices(std::vector<Vertice>  newVertices);

    /**
     * \brief Function to get a element of the nodes vector by name.
     *
     * \param[in] name The name of the node to get
     *
     * \return The node whose name was put in
     */
    Node &getNodeByName(const std::string &name);

    /**
     * \brief Function to write the graph to the disk at the specified filepaths.
     *
     * \param [in]nodeFilePath The node filepath
     * \param [in]verticeFilePath The vertice filepath
     */
    void dumpGraphToDisk(const std::string &nodeFilePath,
                         const std::string &verticeFilePath);
};

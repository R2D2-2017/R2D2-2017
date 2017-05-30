//
// Created by Robert on 5/19/17.
//

#ifndef NAVIGATIONSYSTEM_GRAPH_HH
#define NAVIGATIONSYSTEM_GRAPH_HH

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

    void addNode(const Node node);

    void removeNode(const Node node);

    void addVertice(const Vertice vertice);

    void removeVertice(const Vertice vertice);

    bool containsNode(const Node node);

    bool containsVertice(const Vertice vertice);

    std::vector<Node> getNodes();

    std::vector<Vertice> getVertices();

    /**
 * \brief function to set the nodes vector
 */
    void setNodes(std::vector<Node> nodes);

    /**
 * \brief function to set the vertice vector
 */
    void setVertices(std::vector<Vertice> vertices);

    /**
  * \brief function to get a element of the nodes vector by name
  */
    Node & getNodeByName(std::string name);

    /**
* \brief function to write the graph to the disk at the specified filepaths.
     * \param [in]nodeFilePath the node filepath
     * \param [in]verticeFilePath the vertice filepath
*/
    void dumpGraphToDisk(const std::string nodeFilePath,const std::string verticeFilePath);
};


#endif //NAVIGATIONSYSTEM_GRAPH_HH
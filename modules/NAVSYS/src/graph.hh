//
// Created by Robert on 5/19/17.
//

#ifndef NAVIGATIONSYSTEM_GRAPH_HH
#define NAVIGATIONSYSTEM_GRAPH_HH

#include <iostream>
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

    void setNodes(std::vector<Node> nodes);

    void setVertices(std::vector<Vertice> vertices);

    std::vector<Node>::iterator getNodeByName(std::string name);

    void dumpGraphToDisk(const std::string nodeFilePath,const std::string verticeFilePath);
};


#endif //NAVIGATIONSYSTEM_GRAPH_HH

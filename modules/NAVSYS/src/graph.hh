//
// Created by Robert and jeremy on 5/19/17.
//

#ifndef NAVIGATIONSYSTEM_GRAPH_HH
#define NAVIGATIONSYSTEM_GRAPH_HH

#include <vector>
#include "node.hh"
#include "vertice.hh"
#include "StorageManager.hh"
class StorageMngr;

class Graph {
private:
    std::vector<Node> nodes;
    std::vector<Vertice> vertices;
    StorageMngr * storage = nullptr;

public:
    Graph(const std::string  nodeFilePath, const std::string  verticeFilePath);
    void writeGraphToStorage();
    void addNode(const Node node);
    void removeNode(const Node node);
    void addVertice(const Vertice vertice);
    void removeVertice(const Vertice vertice);
    bool containsNode(const Node node);
    bool containsVertice(const Vertice vertice);
    std::vector<Node> & getNodes();
    std::vector<Vertice> & getVertices();
    std::vector<Node>::iterator getNodeByID(int id);
    void addNodeEntry();
    void addVerticeEntry();
};

#endif //NAVIGATIONSYSTEM_GRAPH_HH

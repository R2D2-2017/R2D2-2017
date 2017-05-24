//
// Created by Robert and jeremy on 5/19/17.
//

#ifndef NAVIGATIONSYSTEM_GRAPH_HH
#define NAVIGATIONSYSTEM_GRAPH_HH

#include <vector>
#include "node.hh"
#include "vertice.hh"
#include "StorageManager.hh"

// forward declaration of StorageMngr
// which is necessary for the compiler make this class
class StorageMngr;
/**
 * \brief Graph class
 * \details
 * Container class for nodes and vertices in the same graph
 */
class Graph {
private:
    std::vector<Node> nodes;
    std::vector<Vertice> vertices;
    StorageMngr * storage = nullptr;

public:
    Graph(const std::string  nodeFilePath, const std::string  verticeFilePath);
///author jeremy
///
/// This function can be used to write the current state of the graph to disk.
///
/// The function calls the storage manager to handle storage.
///
/// Output vertices and nodes saved in their respective files.
    void writeGraphToStorage();
    void addNode(const Node node);
    void removeNode(const Node node);
    void addVertice(const Vertice vertice);
    void removeVertice(const Vertice vertice);
    bool containsNode(const Node node);
    bool containsVertice(const Vertice vertice);
    std::vector<Node> & getNodes();
    std::vector<Vertice> & getVertices();

///author jeremy
///
/// This function gets a node from the graph based on id.
///
/// /param int id
///
/// This function iterates over all the node elements en returns the element where the id matches.
/// This function is only used to close the input file streams used by the factory functions.
///
/// Output the iterator pointing to the node will be returned.
///
/// /return it
    std::vector<Node>::iterator getNodeByID(int id);

///author jeremy
///
/// This function can be used to add a node to the graph.
///
/// The function calls the storage manager to handle the input.
///
/// Output node added to graph.
    void addNodeEntry();


///author jeremy
///
/// This function can be used to add a node to the graph.
///
/// The function calls the storage manager to handle the input.
///
/// Output node added to graph.
    void addVerticeEntry();
};

#endif //NAVIGATIONSYSTEM_GRAPH_HH

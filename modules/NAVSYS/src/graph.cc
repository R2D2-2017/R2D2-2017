//

// Created by Robert and jeremy on 5/19/17.
//
#include <algorithm>
#include "graph.hh"

Graph::Graph(const string nodeFilePath, const string verticeFilePath):

    storage( new StorageMngr(nodeFilePath, verticeFilePath) )
{

    storage->storageSetGraph(this);
    storage->RunGraphFactory();
}


void Graph::addNode(const Node node) {
    if (!containsNode(node)) {
        nodes.push_back(node);
    } else {
        throw std::runtime_error("Node already in graph");
    }
}
void Graph::removeNode(const Node node) {
    nodes.erase(std::remove(nodes.begin(), nodes.end(), node), nodes.end());
}
void Graph::addVertice(const Vertice vertice) {
    if (!containsVertice(vertice)) {
        vertices.push_back(vertice);
    } else {
        throw std::runtime_error("Vertice already in graph");
    }
}

void Graph::removeVertice(const Vertice vertice) {
    vertices.erase(std::remove(vertices.begin(), vertices.end(), vertice), vertices.end());
}
bool Graph::containsNode(const Node node) {
    return std::find(nodes.begin(), nodes.end(), node) != nodes.end();
}

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
std::vector<Node>::iterator Graph::getNodeByID(int id) {
    std::vector<Node>::iterator it;
     it = std::find_if(std::begin(nodes), std::end(nodes),[&](const Node & node) -> bool{
        return node.getNodeId() == id;
    });
    return it;
}
bool Graph::containsVertice(const Vertice vertice) {
    return std::find(vertices.begin(), vertices.end(), vertice) != vertices.end();
}
std::vector<Node> & Graph::getNodes() {
    return nodes;
}
std::vector<Vertice> & Graph::getVertices() {
    return vertices;
}

///author jeremy
///
/// This function can be used to write the current state of the graph to disk.
///
/// The function calls the storage manager to handle storage.
///
/// Output vertices and nodes saved in their respective files.
void Graph::writeGraphToStorage() {
    storage->storeGraphOnDisk();
}

///author jeremy
///
/// This function can be used to add a node to the graph.
///
/// The function calls the storage manager to handle the input.
///
/// Output node added to graph.
void Graph::addNodeEntry() {
    storage->getNodeEntryFromScreen();
}

///author jeremy
///
/// This function can be used to add a node to the graph.
///
/// The function calls the storage manager to handle the input.
///
/// Output node added to graph.
void Graph::addVerticeEntry() {
    storage->getVerticeEntryFromScreen();
}




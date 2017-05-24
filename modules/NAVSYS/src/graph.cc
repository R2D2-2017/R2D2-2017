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

void Graph::writeGraphToStorage() {
    storage->storeGraphOnDisk();
}


void Graph::addNodeEntry() {
    storage->getNodeEntryFromScreen();
}

void Graph::addVerticeEntry() {
    storage->getVerticeEntryFromScreen();
}



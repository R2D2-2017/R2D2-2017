/**
 * \node      graph.cc
 * \author    Robert
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See ../../LICENSE
 */

#include "graph.hh"

#include <iostream>
#include <fstream>
#include <stdexcept>

void Graph::addNode(const Node & node) {
    if (!containsNode(node)) {
        nodes.push_back(node);
    }
    else {
        //throw std::runtime_error("Node already in graph");
    }
}

void Graph::removeNode(const Node & node) {
    nodes.erase(std::remove(nodes.begin(), nodes.end(), node), nodes.end());
}

void Graph::addVertice(const Vertice & vertice) {
    if (!containsVertice(vertice)) {
        vertices.push_back(vertice);
    } else {
        //throw std::runtime_error("Vertice already in graph");
    }
}

void Graph::removeVertice(const Vertice & vertice) {
    vertices.erase(std::remove(vertices.begin(), vertices.end(), vertice), 
                               vertices.end());
}

bool Graph::containsNode(const Node & node) {
    return std::find(nodes.begin(), nodes.end(), node) != nodes.end();
}

bool Graph::containsVertice(const Vertice & vertice) {
    return std::find(vertices.begin(), vertices.end(), 
                     vertice) != vertices.end();
}

std::vector<Node> Graph::getNodes() {
    return nodes;
}

std::vector<Vertice> Graph::getVertices() {
    return vertices;
}

void  Graph::setNodes(std::vector<Node>  newNodes) {
    nodes = newNodes;
}
void  Graph::setVertices(std::vector<Vertice>  newVertices) {
    vertices = newVertices;
}

Node & Graph::getNodeByName(const std::string &name) {
    std::vector<Node>::iterator it;
    it = std::find_if(
        std::begin(nodes),
        std::end(nodes),
        [&]( Node & node) -> bool {
            return node.getName() == name;
        });
    return *it;
}

void Graph::dumpGraphToDisk(const std::string &nodeFilePath, 
                            const std::string &verticeFilePath) {
    std::cout<< "Saving nodes on disk\n";

    std::ofstream nodeFile;
    nodeFile.open(nodeFilePath);

    // for each node in the graph create the format string and write it the the
    // correct file.
    std::for_each (
        nodes.begin(),
        nodes.end(),
        [&nodeFile](Node node){
            std::string tmp = "";
            tmp+="(";
            tmp.append(node.getName());
            tmp+=")[";
            tmp.append(std::to_string(static_cast<int>(node.getCoordinate().x)));
            tmp+=",";
            tmp.append(std::to_string(static_cast<int>(node.getCoordinate().y)));
            tmp+="]";
            tmp+="\n";
            std::cout << tmp;
            nodeFile << tmp;
        });

    nodeFile.close();

    std::ofstream verticeFile;
    verticeFile.open(verticeFilePath);

    std::cout<< "saving vertices on disk\n";

    // for each node in the graph create the format string and write it the the 
    // correct file.
    std::for_each (
        vertices.begin(),
        vertices.end(),
        [&verticeFile](Vertice vertice) {
            std::string tmp = "";
            tmp+="(";
            tmp.append(vertice.getCurrent().getName());
            tmp+=")-(";
            tmp.append(vertice.getNeighbour().getName());
            tmp+=")[";
            tmp.append(std::to_string(vertice.getWeight()));
            tmp+="]\n";
            std::cout << tmp;
            verticeFile << tmp;
        });

    verticeFile.close();
}

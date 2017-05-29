//
// Created by Robert on 5/19/17.
//
#include <algorithm>
#include "graph.hh"
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


bool Graph::containsVertice(const Vertice vertice) {
    return std::find(vertices.begin(), vertices.end(), vertice) != vertices.end();
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

std::vector<Node>::iterator Graph::getNodeByName(std::string name) {
    std::vector<Node>::iterator it;
    it = std::find_if(std::begin(nodes), std::end(nodes),[&](const Node & node) -> bool{
        return node.getNodeName() == name;
    });
    return it;
}

void Graph::dumpGraphToDisk(const std::string nodeFilePath,const std::string verticeFilePath) {

    FILE* nodeFile;

    nodeFile = fopen(nodeFilePath.c_str(),"w");
    std::cout<< "saving nodes on disk\n";

    // for each node in the graph create the format string and write it the the correct file.
    std::for_each (nodes.begin(), nodes.end(), [nodeFile](Node node){
        std::string tmp = "";
        tmp+="(";
        tmp.append(node.getNodeName());
        tmp+=")[";
        tmp.append(std::to_string((int)node.getCoordinate().x));
        tmp+=",";
        tmp.append(std::to_string((int)node.getCoordinate().y));
        tmp+="]";
        tmp+="\n";
        std::cout << tmp;
        fputs(tmp.c_str(),nodeFile );
    });

    fclose(nodeFile);

    FILE* verticeFile;
    verticeFile = fopen(verticeFilePath.c_str(),"w");
    std::cout<< "saving vertices on disk\n";

    // for each node in the graph create the format string and write it the the correct file.
    std::for_each (vertices.begin(), vertices.end(), [verticeFile](Vertice vertice) {
        std::string tmp = "";
        tmp+="(";
        tmp.append(vertice.getCurrent()->getNodeName());
        tmp+=")-(";
        tmp.append(vertice.getNeighbour()->getNodeName());
        tmp+=")[";
        tmp.append(std::to_string(vertice.getWeight()));
        tmp+="]\n";
        std::cout << tmp;
        fputs(tmp.c_str(),verticeFile );
    });

    fclose(verticeFile);
}


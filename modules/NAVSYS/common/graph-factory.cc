/**
 * \file      graph-factory.cc
 * \author    Jeremy, Arco Gelderblom
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See LICENSE
 */

#include "graph-factory.hh"
#include <fstream>
#include <iostream>

void GraphFactory::createGraph(const std::string &nodeFilePath, 
                               const std::string &verticeFilePath, 
                               Graph & graph ) {
    graph.setNodes(RunNodeFactory(nodeFilePath));
    graph.setVertices(RunVerticeFactory(verticeFilePath,graph.getNodes()));
}

Node GraphFactory::getNodeByName(const std::string &name, 
                                 std::vector<Node> nodes) {
    auto it = std::find_if(
            std::begin(nodes),
            std::end(nodes),
            [&](Node & node) -> bool {
                return node.getName() == name;
            });
    if (it != nodes.end()) {
        return *it;
    }
    return Node();
}

std::vector<Node> GraphFactory::RunNodeFactory(
                                    const std::string & nodeFilePath) {
    std::vector<Node> nodes;
    std::ifstream nodeFileStreamIn;
    nodeFileStreamIn.open(nodeFilePath,std::ios_base::app);

    std::string nodeEntry = "";
    //get line out of file
    while (getline (nodeFileStreamIn,nodeEntry)) {
        std::string nodeName = "";
        std::string nodePosX = "";
        std::string nodePosY = "";

        // flags to to deside based on specific chars, 
        // which data element is being read.
        bool nameFlag = false;
        bool coordinateFlagX = false;
        bool coordinateFlagY = false;

        // for each char in line
        unsigned int i = 0;
        while (i < nodeEntry.length()) {

            char c = nodeEntry.at(i);
            if (c == '(') {
                nameFlag = true;
            }
            else if (c == ')') {
                nameFlag = false;
            }
            else if (c == '[') {
                coordinateFlagX = true;
            }
            else if (c == ']') {
                coordinateFlagY = false;
            }
            else if (c == ',') {
                coordinateFlagX = false;
                coordinateFlagY = true;
            }
            else {
                if (nameFlag) {
                    nodeName += c;
                }
                if (coordinateFlagX) {
                    nodePosX += c;
                }
                if (coordinateFlagY) {
                    nodePosY += c;
                }
            }
            ++i;
        }

        float tmpPosX = std::stof(nodePosX);
        float tmpPosY = std::stof(nodePosY);
        
        // add created node to vector
        Node newNode = Node(tmpPosX,tmpPosY,  nodeName);
        nodes.push_back(newNode);
    }
    nodeFileStreamIn.close();
    return nodes;
}

std::vector<Vertice> GraphFactory::RunVerticeFactory(
                                            const std::string &verticeFilePath, 
                                            std::vector<Node> nodes) {
    std::vector<Vertice> vertices;
    std::ifstream verticeFileStreamIn(verticeFilePath,std::ios_base::app);

    if (verticeFileStreamIn.is_open()) {
        std::string verticeEntry = "";
        // reset EOF and set pointer at beginning of the file
        verticeFileStreamIn.clear();
        verticeFileStreamIn.seekg(0, std::ios::beg);
        //get line out of file
        while (getline (verticeFileStreamIn,verticeEntry)) {

            // strings to store chars read
            std::string nodeA = "";
            std::string nodeB = "";
            std::string weight = "";
            // flags to to deside based on specific chars, which data element is being read.
            bool nodeFlagA = false;
            bool nodeFlagB = false;
            bool weightFlag = false;

            // for each char in line
            unsigned int i = 0;
            while (i < verticeEntry.length()) {
                char c = verticeEntry.at(i);
                if (c == '(' && !nodeFlagB) {
                    nodeFlagA = true;
                }
                else if (c == '(' && nodeFlagB) {
                    //nothing
                }
                else if (c == ')') {
                    nodeFlagA = false;
                    nodeFlagB = false;
                }
                else if (c == '[') {
                    weightFlag = true;
                }
                else if (c == ']') {
                    weightFlag = false;
                }
                else if (c == '-'){
                    nodeFlagB = true;
                }
                else {
                    if (nodeFlagA) {
                        nodeA += c;
                    }
                    if (nodeFlagB) {
                        nodeB += c;
                    }
                    if (weightFlag) {
                        weight += c;
                    }
                }
                ++i;
            }
            int tmpWeight =  atoi(weight.c_str());
            // add created vertice to vector
            vertices.push_back(Vertice(
                Node(
                    getNodeByName(nodeA, nodes).getCoordinate().x,
                    getNodeByName(nodeA, nodes).getCoordinate().y,
                    getNodeByName(nodeA, nodes).getName()),
                Node(
                    getNodeByName(nodeB,nodes).getCoordinate().x,
                    getNodeByName(nodeB,nodes).getCoordinate().y,
                    getNodeByName(nodeB,nodes).getName()),
                    tmpWeight));
        }
    } else {
        std::cerr<<"Couldn't open the file";
    }
    return vertices;
}

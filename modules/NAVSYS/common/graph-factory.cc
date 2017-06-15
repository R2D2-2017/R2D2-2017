/**
 * \file      graph-factory.cc
 * \brief     This file includes contains the implementations for the graphfactory class
 * \author    Jeremy, Arco Gelderblom
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See LICENSE
 */

#include "graph-factory.hh"
#include <fstream>
//#include <algorithm>

void GraphFactory::createGraph(const std::string &nodeFilePath, const std::string &verticeFilepath, Graph & graph ) {
    graph.setNodes(RunNodeFactory(nodeFilePath));
    graph.setVertices(RunVerticeFactory(verticeFilepath,graph.getNodes()));
}

Node GraphFactory::getNodeByName(const std::string &name, std::vector<Node> nodes) {
    std::vector<Node>::iterator it;
    it = std::find_if(
            std::begin(nodes),
            std::end(nodes),
            [&](Node & node) -> bool {
                return node.getName() == name;
            });
    return *it;
}

std::vector<Node>  GraphFactory::RunNodeFactory(const std::string &nodeFilePath) {
    std::vector<Node> nodes;
    std::ifstream nodeFileStreamIn;
    nodeFileStreamIn.open(nodeFilePath,std::ios_base::app);

    std::string nodeEntry = "";
    //get line out of file
    while (getline (nodeFileStreamIn,nodeEntry)) {
        std::string nodeName = "";
        std::string nodePosX = "";
        std::string nodePosY = "";

        // flags to to deside based on specific chars, which data element is being read.
        bool nameFlag = 0;
        bool coordinateFlagX = 0;
        bool coordinateFlagY = 0;

        // for each char in line
        unsigned int i = 0;
        while (i < nodeEntry.length()) {

            char c = nodeEntry.at(i);
            if (c == '(') {
                nameFlag = 1;
            }
            else if (c == ')') {
                nameFlag = 0;
            }
            else if (c == '[') {
                coordinateFlagX = 1;
            }
            else if (c == ']') {
                coordinateFlagY = 0;
            }
            else if (c == ',') {
                coordinateFlagX = 0;
                coordinateFlagY = 1;
            }
            else {
                if (nameFlag) {
                    nodeName += c;
                }
                else if (c == ')') {
                    nameFlag = 0;
                }
                else if (c == '[') {
                    coordinateFlagX = 1;
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

std::vector<Vertice> GraphFactory::RunVerticeFactory(const std::string &verticeFilePath, std::vector<Node> nodes) {
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
            bool nodeFlagA = 0;
            bool nodeFlagB = 0;
            bool weightFlag = 0;

            // for each char in line
            unsigned int i = 0;
            while (i < verticeEntry.length()) {
                char c = verticeEntry.at(i);
            if (c == '(' && !nodeFlagB) {
                nodeFlagA = 1;
            }
            else if (c == '(' && nodeFlagB) {
                //nothing
            }
            else if (c == ')') {
                nodeFlagA = 0;
                nodeFlagB = 0;
            }
            else if (c == '[') {
                weightFlag = 1;
            }
            else if (c == ']') {
                weightFlag = 0;
            }
            else if (c == '-'){
                nodeFlagB =1;
            }
            else {
                if (nodeFlagA) {
                    nodeA += c;
                }
                else if (c == '[') {
                    weightFlag = 1;
                }
                else if (c == ']') {
                    weightFlag = 0;
                }
                else if (c == '-'){
                    nodeFlagB =1;
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
    return vertices;
}

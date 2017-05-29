/**
 * \file
 * \brief     This file includes contains the implementations for the graphfactory class
 * \author    Jeremy
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See LICENSE
 */
#include "graph-factory.hh"
#include <algorithm>




Graph* GraphFactory::createGraph(std::string nodeFilePath,std::string verticeFilePath ){

    Graph * graph = new Graph();
    graph->setNodes(RunNodeFactory(nodeFilePath));
    graph->setVertices(RunVerticeFactory(verticeFilePath,graph->getNodes()));

    return graph;
}


std::vector<Node>::iterator GraphFactory::getNodeByName(std::string name, std::vector<Node> nodes) {
    std::vector<Node>::iterator it;
    it = std::find_if(std::begin(nodes), std::end(nodes),[&](const Node & node) -> bool{
        return node.getNodeName() == name;
    });
    return it;
}

/*author jeremy
*
* This function handle the parsing of lines found in the node file and the creation of nodes
*
* This function wil keep getting lines from the file from which it wil extract the node information.
* This information is stored in strings named after the information they contain.
* After parsing a line from the file, a node object is created with the data found.
* This created node is then passed to the graph.
* This repeats untill there are no more lines in the file.
*
*!!!
* If the user enters an entry directly in the file itself, make sure not to end the last
* with a new line. This will cause the node factories to read an additional empty entry and store it.
* This causes undefined behavior when iterating over elements in other functions.
* !!!
*
* Output vector of nodes are returned
*/

std::vector<Node>  GraphFactory::RunNodeFactory(std::string nodeFilePath) {
    std::vector<Node> nodes;

    ifstream nodeFileStreamIn;
    nodeFileStreamIn.open(nodeFilePath,std::ios_base::app);


    string nodeEntry = "";
    //get line out of file
    while (getline (nodeFileStreamIn,nodeEntry)) {
        string nodeName = "";
        string nodePosX = "";
        string nodePosY = "";

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
                if (coordinateFlagX) {
                    nodePosX += c;
                }
                if (coordinateFlagY) {
                    nodePosY += c;
                }

            }
            i++;
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


/* author jeremy
*
* This function handle the parsing of lines found in the vertice file and the creation of vertices
*
* This function wil keep getting lines from the file from which it wil extract the vertice information.
* This information is stored in strings named after the information they contain.
* After parsing a line from the file, a vertice object is created with the data found.
* in the case of the involved nodes this is done by calling the graph to return the *ptr to the nodes  in the vertice.
* This is done based on node id.
* This created vertice is then passed to the graph.
* This repeats until there are no more lines in the file.
*
* !!!
* If the user enters an entry directly in the file itself, make sure not to end the last
* with a new line. This will cause the node factories to read an additional empty entry and store it.
* This causes undefined behavior when iterating over elements in other functions.
* !!!
*
* Output vertices are stored in graph
*/
std::vector<Vertice> GraphFactory::RunVerticeFactory(std::string verticeFilePath, std::vector<Node> nodes) {
    std::vector<Vertice> vertices;

    ifstream verticeFileStreamIn;
    verticeFileStreamIn.open(verticeFilePath,std::ios_base::app);

    string verticeEntry = "";
    //get line out of file
    while (getline (verticeFileStreamIn,verticeEntry)) {

        // strings to store chars read
        string nodeA = "";
        string nodeB = "";
        string weight = "";


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
                if (nodeFlagB) {
                    nodeB += c;
                }
                if (weightFlag) {
                    weight += c;
                }
            }

            i++;
        }

        int tmpWeight =  atoi(weight.c_str());
        // add created vertice to vector
        vertices.push_back(Vertice( Node( getNodeByName(nodeA,nodes)->getCoordinate().x, getNodeByName(nodeA,nodes)->getCoordinate().y,
                                  getNodeByName(nodeA,nodes)->getNodeName()),
                            Node( getNodeByName(nodeB,nodes)->getCoordinate().x, getNodeByName(nodeB,nodes)->getCoordinate().y,
                                  getNodeByName(nodeB,nodes)->getNodeName()),
                            tmpWeight ));

    }
    verticeFileStreamIn.close();
    return vertices;
}



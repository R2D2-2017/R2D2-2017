//
// Created by datz on 26-5-17.
//

#include "graphfactory.hh"


 graphfactory::graphfactory(const std::string nodeFilePath,const std::string verticeFilePath):
        nodeFilePath(nodeFilePath),verticeFilePath(verticeFilePath)
{

}


void graphfactory::addNode(const Node node) {
    if (!containsNode(node)) {
        nodes.push_back(node);
    } else {
        throw std::runtime_error("Node already in list");
    }
}


void graphfactory::addVertice(const Vertice vertice) {
    if (!containsVertice(vertice)) {
        vertices.push_back(vertice);
    } else {
        throw std::runtime_error("Vertice already in list");
    }
}

bool graphfactory::containsNode(const Node node) {
    return std::find(nodes.begin(), nodes.end(), node) != nodes.end();
}

bool graphfactory::containsVertice(const Vertice vertice) {
    return std::find(vertices.begin(), vertices.end(), vertice) != vertices.end();
}


///author jeremy
///
/// This function calles the necessary parts to create a graph.
///
/// /return graph
Graph* graphfactory::createGraph(){

    RunGraphFactory();
    Graph * graph = new Graph();
    graph->setNodes(nodes);
    graph->setVertices(vertices);

    return graph;
}

///author jeremy
///
/// This function closes all files opened by the factory.
///
/// Output files are closed
void graphfactory::closeFiles() {
    if (nodeFileStreamIn.is_open()){
        nodeFileStreamIn.close();
    }
    if (verticeFileStreamIn.is_open()){
        verticeFileStreamIn.close();
    }

}

///author jeremy
///
/// This function finds a node based on name .
///
/// /return iterator to node

std::vector<Node>::iterator graphfactory::getNodeByName(std::string name) {
    std::vector<Node>::iterator it;
    it = std::find_if(std::begin(nodes), std::end(nodes),[&](const Node & node) -> bool{
        return node.getNodeName() == name;
    });
    return it;
}

///author jeremy
///
/// This function handle the parsing of lines found in the node file and the creation of nodes
///
/// This function wil keep getting lines from the file from which it wil extract the node information.
/// This information is stored in strings named after the information they contain.
/// After parsing a line from the file, a node object is created with the data found.
/// This created node is then passed to the graph.
/// This repeats untill there are no more lines in the file.
///
/// !!!
/// If the user enters an entry directly in the file itself, make sure not to end the last
/// with a new line. This will cause the node factories to read an additional empty entry and store it.
/// This causes undefined behavior when iterating over elements in other functions.
/// !!!
///
/// Output nodes are stored in graph

void graphfactory::RunNodeFactory() {

    string nodeEntry = "";
    while (getline (nodeFileStreamIn,nodeEntry)) {
        string nodeName = "";
        string nodePosX = "";
        string nodePosY = "";


        bool nameFlag = 0;
        bool coordinateFlagX = 0;
        bool coordinateFlagY = 0;


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

        Node newNode = Node(tmpPosX,tmpPosY,  nodeName);
        addNode(newNode);

    }
}


///author jeremy
///
/// This function handle the parsing of lines found in the vertice file and the creation of vertices
///
/// This function wil keep getting lines from the file from which it wil extract the vertice information.
/// This information is stored in strings named after the information they contain.
/// After parsing a line from the file, a vertice object is created with the data found.
/// in the case of the involved nodes this is done by calling the graph to return the *ptr to the nodes  in the vertice.
/// This is done based on node id.
/// This created vertice is then passed to the graph.
/// This repeats until there are no more lines in the file.
///
/// !!!
/// If the user enters an entry directly in the file itself, make sure not to end the last
/// with a new line. This will cause the node factories to read an additional empty entry and store it.
/// This causes undefined behavior when iterating over elements in other functions.
/// !!!
///
/// Output vertices are stored in graph
void graphfactory::RunVerticeFactory() {

    string verticeEntry = "";
    while (getline (verticeFileStreamIn,verticeEntry)) {
        string nodeA = "";
        string nodeB = "";
        string weight = "";

        bool nodeFlagA = 0;
        bool nodeFlagB = 0;
        bool weightFlag = 0;


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

        addVertice(Vertice( Node( getNodeByName(nodeA)->getCoordinate().x, getNodeByName(nodeA)->getCoordinate().y,
                                  getNodeByName(nodeA)->getNodeName()),
                            Node( getNodeByName(nodeB)->getCoordinate().x, getNodeByName(nodeB)->getCoordinate().y,
                                  getNodeByName(nodeB)->getNodeName()),
                            tmpWeight ));

    }
}

///author jeremy
///
/// This function is used to start the graph factory
///
/// This function opens the fil streams in append mode
/// and calles the independent node and vertice factories.
/// Afterwards it will close the file streams.
///
/// Output graph is stored in memory
void graphfactory::RunGraphFactory() {

    nodeFileStreamIn.open(nodeFilePath,std::ios_base::app);
    verticeFileStreamIn.open(verticeFilePath,std::ios_base::app);
    RunNodeFactory();
    RunVerticeFactory();
    closeFiles();

}
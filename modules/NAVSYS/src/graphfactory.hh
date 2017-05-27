//
// Created by datz on 26-5-17.
//

#ifndef NAVSYS_GRAPHFACTORY_HH
#define NAVSYS_GRAPHFACTORY_HH

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include "graph.hh"
#include "node.hh"

using namespace std;

class graphfactory {
private:


    std::vector<Node> nodes;
    std::vector<Vertice> vertices;

    string nodeFilePath;
    string verticeFilePath;

    ifstream nodeFileStreamIn;
    ifstream verticeFileStreamIn;



    void addVertice(const Vertice vertice);
    void addNode(const Node node);
    bool containsNode(const Node node);
    bool containsVertice(const Vertice vertice);

    ///author jeremy
///
/// This function finds a node based on name .
///
/// /return iterator to node
    std::vector<Node>::iterator getNodeByName(std::string name);

    ///author jeremy
///
/// This function handle the parsing of lines found in the node file and the creation of nodes

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
    void RunNodeFactory();


///author jeremy
///
/// This function handle the parsing of lines found in the vertice file and the creation of vertices

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
    void RunVerticeFactory();

///author jeremy
///
/// This function closes all files opened by the factory.
///
/// Output files are closed
    void closeFiles();


    ///author jeremy
///
/// This function is used to start the graph factory
///
/// This function opens the fil streams in append mode
/// and calles the independent node and vertice factories.
/// Afterwards it will close the file streams.
///
/// Output graph is stored in memory
    void RunGraphFactory();

public:

    graphfactory(const std::string nodeFilePath, const std::string verticeFilePath);

    ///author jeremy
///
/// This function calles the necessary parts to create a graph.
///
/// /return graph
    Graph* createGraph();


};


#endif //NAVSYS_GRAPHFACTORY_HH

/**
 * \file
 * \brief     This file contains the implementations of the graphIO class,
 *            which is the class that handles all user input in regards to a graph.
 * \author    jeremy
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See LICENSE
 */
#include "graph-input.hh"

void GraphInput::getNodeEntryFromScreen(Graph * graph) {

    string name = "";
    string coordinateX = "";
    string coordinateY = "";
    cout << "Please enter node name: >";
    getline(cin, name);
    cout << "Please enter node coordinate x: >";
    getline(cin, coordinateX);
    cout << "Please enter node coordinate y: >";
    getline(cin, coordinateY);

    graph->addNode(Node(std::stof(coordinateX), std::stof(coordinateY), name ));

}


void GraphInput::getVerticeEntryFromScreen(Graph * graph) {

    string node1 = "";
    string node2 = "";
    string weight = "";

    cout << "Please enter name of from node x: >";
    getline(cin, node1);
    cout << "Please enter name of to node x: >";
    getline(cin, node2);
    cout << "Please enter path weight x: >";
    getline(cin, weight);

    /* based on the node names given as input, the information of those nodes are used
    * to create the nodes of the vertices needed for the construction of a vertice
    * this is big function because gettting an existing node element from the graph
    * always results in a iterator*, which cant be used. so now by using the iterator*
    * to call the get functions of the nodes they point to a new node is made with the same
    * data.
    */
    graph->addVertice(Vertice(  Node( graph->getNodeByName(node1)->getCoordinate().x,
                                      graph->getNodeByName(node1)->getCoordinate().y,
                                      graph->getNodeByName(node1)->getNodeName()),
                                Node( graph->getNodeByName(node1)->getCoordinate().x,
                                      graph->getNodeByName(node1)->getCoordinate().y,
                                      graph->getNodeByName(node1)->getNodeName()),
                                std::stoi(weight) ));

}
















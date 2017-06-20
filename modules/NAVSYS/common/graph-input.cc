/**
 * \file      graph-input.cc
 * \author    Jeremy
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See LICENSE
 */

#include "graph-input.hh"
#include <iostream>

void GraphInput::getNodeEntryFromScreen(Graph &graph) {
    std::string name = "";
    std::string coordinateX = "";
    std::string coordinateY = "";
    std::cout << "Please enter node name: >";
    getline(std::cin, name);
    std::cout << "Please enter node coordinate x: >";
    getline(std::cin, coordinateX);
    std::cout << "Please enter node coordinate y: >";
    getline(std::cin, coordinateY);

    graph.addNode(Node(std::stof(coordinateX), std::stof(coordinateY), name ));
    std::cout << "Node added to graph\n";
}


void GraphInput::getVerticeEntryFromScreen(Graph &graph) {
    std::string node1 = "";
    std::string node2 = "";
    std::string weight = "";

    std::cout << "Please enter name of from node x: >";
    getline(std::cin, node1);
    std::cout << "Please enter name of to node x: >";
    getline(std::cin, node2);
    std::cout << "Please enter path weight x: >";
    getline(std::cin, weight);

    /* based on the node names given as input, the information of those nodes 
     * are used to create the nodes of the vertices needed for the construction 
     * of a vertice this is big function because gettting an existing node 
     * element from the graph always results in a iterator*, which cant be used.
     * so now by using the iterator* to call the get functions of the nodes they
     * point to a new node is made with the same data.
     */
    graph.addVertice(Vertice(
        Node(
            graph.getNodeByName(node1).getCoordinate().x,
            graph.getNodeByName(node1).getCoordinate().y,
            graph.getNodeByName(node1).getName()),
        Node(
            graph.getNodeByName(node2).getCoordinate().x,
            graph.getNodeByName(node2).getCoordinate().y,
            graph.getNodeByName(node2).getName()),
        std::stoi(weight)));

    std::cout << "Vertice added to graph\n";
}

//
// Created by jeremy on 22-5-17.
//
//===-- graphinput.cc - graphinput class implementation -------*- C++ -*-===//
//
//                     The graphinput
//

//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains the implementations of the graphIO class, which is the
/// class that handles all user IO in regards to a graph.
///
//===----------------------------------------------------------------------===//

#include "graphinput.hh"


///author jeremy
///
/// This function can be used to get a node entry from the terminal.
/// It asks the user to input the data, which it uses to create a node class.
/// The created node class is then passed to the graph.
///
/// Output node is added to graph
void graphinput::getNodeEntryFromScreen(Graph * graph) {

    string name = "";
    string coordinateX = "";
    string coordinateY = "";
 //   string iD = "";
    cout << "Please enter node name: >";
    getline(cin, name);
    cout << "Please enter node coordinate x: >";
    getline(cin, coordinateX);
    cout << "Please enter node coordinate y: >";
    getline(cin, coordinateY);
//    cout << "Please enter node iD: >";
  //  getline(cin, iD);
    graph->addNode(Node(std::stof(coordinateX), std::stof(coordinateY), name ));

}

///author jeremy
///
/// This function can be used to get a vertice entry from the terminal.
/// It asks the user to input the data which, it uses to create a vertice class
/// The created vertice class is then passed to the graph
///
/// Output vertice is added to graph.
void graphinput::getVerticeEntryFromScreen(Graph * graph) {

    string node1 = "";
    string node2 = "";
    string weight = "";

    cout << "Please enter name of from node x: >";
    getline(cin, node1);
    cout << "Please enter name of to node x: >";
    getline(cin, node2);
    cout << "Please enter path weight x: >";
    getline(cin, weight);
    graph->addVertice(Vertice(  Node( graph->getNodeByName(node1)->getCoordinate().x,
                                      graph->getNodeByName(node1)->getCoordinate().y,
                                      graph->getNodeByName(node1)->getNodeName()),
                                Node( graph->getNodeByName(node1)->getCoordinate().x,
                                      graph->getNodeByName(node1)->getCoordinate().y,
                                      graph->getNodeByName(node1)->getNodeName()),
                                std::stoi(weight) ));

}















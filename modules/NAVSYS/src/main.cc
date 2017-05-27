/**
 * \file
 * \brief     INSERT A DESCRIPTION HERE
 * \author
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See LICENSE
 */
#include <iostream>
#include <algorithm>
#include "graph.hh"
#include "graphfactory.hh"
#include "graphinput.hh"



int main(int argc, char **argv) {

    std::string nodeFilePath = "../debug/node.txt";
    std::string verticeFilePath = "../debug/vertice.txt";

    graphinput input = graphinput();
    graphfactory factory = graphfactory(nodeFilePath, verticeFilePath);
    Graph * graph = factory.createGraph();


    try {
        std::cout<< "trying....\n";
        //input.getNodeEntryFromScreen(graph);
        //input.getVerticeEntryFromScreen(graph);
        graph->dumpGraphToDisk(nodeFilePath,verticeFilePath);

    }
    catch (const std::bad_alloc& e) {
        std::cout << "Allocation failed: " << e.what() << '\n';
    }


    std::cout << "exit\n";
    return 0;
}


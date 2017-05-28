/**
 * \file
 * \brief     INSERT A DESCRIPTION HERE
 * \author    INSERT YOUR NAME HERE
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See LICENSE
 */
#include <iostream>
//#include <algorithm>
#include "graph.hh"
#include "graphfactory.hh"
#include "graphinput.hh"



int main(int argc, char **argv) {

    std::string nodeFilePath = "../src/node.txt";
    std::string verticeFilePath = "../src/vertice.txt";

    //graphinput input = graphinput();
    graphfactory factory = graphfactory();
    Graph * graph = factory.createGraph(nodeFilePath,verticeFilePath);


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



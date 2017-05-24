/**
 * \file
 * \brief     INSERT A DESCRIPTION HERE
 * \author    INSERT YOUR NAME HERE
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See LICENSE
 */
#include <iostream>

#include <algorithm>
#include "graph.hh"




int main(int argc, char **argv) {

    string nodeFilePath = "../debug/node.txt";
    string verticeFilePath = "../debug/vertice.txt";

    Graph graph(nodeFilePath, verticeFilePath);

    try {
        graph.addNodeEntry();
        graph.addVerticeEntry();
        //graph.addVerticeEntry();
        graph.writeGraphToStorage();
    }
    catch (const std::bad_alloc& e) {
        std::cout << "Allocation failed: " << e.what() << '\n';
    }


    std::cout << "exit\n";


    return 0;
}



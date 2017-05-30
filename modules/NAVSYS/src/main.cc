/**
 * \file
 * \brief     main.cc
 * \author    jeremy
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See LICENSE
 */
#include <iostream>
#include <algorithm>
#include "graph.hh"
#include "graph-factory.hh"
#include "graph-input.hh"
#include "astar.hh"
int main(int argc, char **argv)
{

    std::string nodeFilePath = "../src/node.txt";
    std::string verticeFilePath = "../src/vertice.txt";

    //used for reading node or vertice data from the console
    GraphInput input = GraphInput();

    //graph factory
    GraphFactory factory = GraphFactory();
    Graph * g = factory.createGraph(nodeFilePath,verticeFilePath);


    cout<< "1::add node 2::add vertice 3::find shortest route q::save and exit\n";

    string choice = "";
    getline(cin,choice);
    while( choice != "1" || "2" || "3" || "q") {

        if(choice == "q"){
            g->dumpGraphToDisk(nodeFilePath,verticeFilePath);
            break;
        }
        else if (choice == "1") {
            input.getNodeEntryFromScreen(g);
        }
        else if (choice == "2") {
            input.getVerticeEntryFromScreen(g);
        }
        else if (choice == "3") {
            /*bug on second entry to this part of code
             * exit code 139
             * interrupt signal 11 SIGSEGV
             */
            std::cout<< "Select a start and end node from the list\n";
            /*
             * this find_if is used to print only the nodes with valid names
             */
            find_if(g->getNodes().begin(), g->getNodes().end(), [](Node & node){
                   if(node.getName() == "") {
                       return true;
                   }
                   else{
                       std::cout<< node ;
                       return false;
                   }
            });


            std::cout<< "start>\n";
            std::string start = "";
            getline(cin,start);

            std::cout<< "end>\n";
            std::string end   = "";
            getline(cin,end);


            std::vector<PathNode> path = aStar(*g, *g->getNodeByName(start), *g->getNodeByName(end));

            std::cout << "the path is:\n";

            for (auto it = path.begin(); it != path.end(); it++) {
                std::cout << *it << '\n';
            }
        }

        std::cout<< "1::add node 2::add vertice  q::save and exit\n";
        getline(cin,choice);

        /*
         * program crashes on re-entry to the last else if clause if a second attempt
         * to find the shortest path is made.
         * the following statement disables the choice "3" after the first iteration
         */
        if (choice == "3") choice.clear();
        
    }
    return 0;
}

    
        





//
// Created by jeremy on 22-5-17.
//

#ifndef NAVSYS_STORAGEMANAGER_HH
#define NAVSYS_STORAGEMANAGER_HH

#include <iostream>
#include <fstream>
#include <algorithm>
#include "node.hh"
#include "vertice.hh"
#include "graph.hh"
using namespace std;
class Graph;

class StorageMngr {
private:
    string nodeFilePath;
    string verticeFilePath;

    ifstream nodeFileStreamIn;
    ifstream verticeFileStreamIn;

    Graph * graph = nullptr;

    void RunNodeFactory();
    void RunVerticeFactory();

    void closeFiles();




public:
    StorageMngr(const string  nodeFilePath, const string  verticeFilePath);

    void storageSetGraph(Graph * graph);

    void getNodeEntryFromScreen();

    void getVerticeEntryFromScreen();

    void storeGraphOnDisk();

    void RunGraphFactory();


};

#endif //NAVSYS_STORAGEMANAGER_HH

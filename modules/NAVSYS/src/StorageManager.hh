//
// Created by jeremy on 22-5-17.
//
//===-- StorageManager.hh - StorageManager class definitions -------*- C++ -*-===//
//
//                     The storageManager
//

//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains the definitions of the StorageManager class, which is the
/// class that handles all IO in regards to a graph.
///
//===----------------------------------------------------------------------===//

#ifndef NAVSYS_STORAGEMANAGER_HH
#define NAVSYS_STORAGEMANAGER_HH

#include <iostream>
#include <fstream>
#include <algorithm>
#include "node.hh"
#include "vertice.hh"
#include "graph.hh"
using namespace std;

// forward declaration of Graph
// which is necesary for the compiler make this class
class Graph;

class StorageMngr {
private:

    string nodeFilePath;
    string verticeFilePath;

    ifstream nodeFileStreamIn;
    ifstream verticeFileStreamIn;

    Graph * graph = nullptr;


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
/// This function closes all files opened by the Storagemanager.
///
/// This function does noot close the FILE* used for the storage of the entire graph.
/// This function is only used to close the input file streams used by the factory functions.
///
/// Output files are closed
    void closeFiles();




public:

///author jeremy
///
/// \param nodeFilePath
/// \param verticeFilePath
///
/// The constructor for a graph storagemanager
///
    StorageMngr(const string  nodeFilePath, const string  verticeFilePath);


///author jeremy
///
/// \param tmp
/// This function sets the pointer to a graph in the storagemanager.
///
/// Output graph ptr is set.
    void storageSetGraph(Graph * graph);


///author jeremy
///
/// This function can be used to get a node entry from the terminal.
/// It asks the user to input the data, which it uses to create a node class.
/// The created node class is then passed to the graph.
///
/// Output node is added to graph
    void getNodeEntryFromScreen();


///author jeremy
///
/// This function can be used to get a vertice entry from the terminal.
/// It asks the user to input the data which, it uses to create a vertice class
/// The created vertice class is then passed to the graph
///
/// Output vertice is added to graph.
    void getVerticeEntryFromScreen();


///author jeremy
///
/// This function stores every node and vertice found in the graph to their respective files
/// by taking the neccesarry data and composing this to a formatted string. This string is then writed to the files.
/// This functions handles the opening and closing of the file descriptor itself.

/// Output graph is saved on disk.
    void storeGraphOnDisk();


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


};

#endif //NAVSYS_STORAGEMANAGER_HH

//
// Created by jeremy on 22-5-17.
//
//===-- graphinput.hh - graphinput class definitions -------*- C++ -*-===//
//
//                     The graphinput
//

//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains the definitions of the graphIO class, which is the
/// class that handles all IO in regards to a graph.
///
//===----------------------------------------------------------------------===//

#ifndef NAVSYS_GRAPHINPUT_HH
#define NAVSYS_GRAPHINPUT_HH

#include <iostream>
#include "node.hh"
#include "vertice.hh"
#include "graph.hh"


using namespace std;

class graphinput {
private:

public:

///author jeremy
///
/// This function can be used to get a node entry from the terminal.
/// It asks the user to input the data, which it uses to create a node class.
/// The created node class is then passed to the graph.
///
/// Output node is added to graph
    void getNodeEntryFromScreen(Graph * graph);


///author jeremy
///
/// This function can be used to get a vertice entry from the terminal.
/// It asks the user to input the data which, it uses to create a vertice class
/// The created vertice class is then passed to the graph
///
/// Output vertice is added to graph.
    void getVerticeEntryFromScreen(Graph * graph);

};

#endif //NAVSYS_GRAPHINPUT_HH

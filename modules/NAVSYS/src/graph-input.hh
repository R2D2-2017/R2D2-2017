/**
 * \file
 * \brief     This file contains the definitions of the graphIO class,
 *            which is the class that handles all user input in regards to a graph.
 * \author    jeremy
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See LICENSE
 */


#ifndef NAVSYS_GRAPHINPUT_HH
#define NAVSYS_GRAPHINPUT_HH

#include <iostream>
#include "node.hh"
#include "vertice.hh"
#include "graph.hh"



class GraphInput {
private:

public:


/**
 * \brief Description of getNodeEntryFromScreen
 *
 * This function can be used to get a node entry from the terminal.
 * It asks the user to input the data, which it uses to create a node class.
 * The created node class is then passed to the graph.
 * Output node is added to graph
 *
 * \param[in] graph*
 */
    void getNodeEntryFromScreen(Graph * graph);


/**
 * \brief Description of getNodeEntryFromScreen
 *
 * This function can be used to get a vertice entry from the terminal.
 * It asks the user to input the data, which it uses to create a vertice class.
 * The created vertice class is then passed to the graph.
 * Output vertice is added to graph.
 *
 * \param[in] graph*
 */
    void getVerticeEntryFromScreen(Graph * graph);

};

#endif //NAVSYS_GRAPHINPUT_HH


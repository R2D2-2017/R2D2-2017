/**
* \file      graphicsgraph.hh
* \brief     header for graphs in sfmlgraphics window
* \author    Leo Jenneskens
* \copyright Copyright (c) 2017, The R2D2 Team
* \license   See LICENSE
*/

#pragma once 

#include <vector>

#include "graphicsvertices.hh"
#include "graphicsnodes.hh"
#include "../common/graph.hh"

/**
 * \brief Draw the full graph on screen
 */
class GraphDrawer {
private:	
    std::vector<GraphNode> graphNodes;
    std::vector<GraphVertice> graphVertices;
    sf::RenderWindow & window;
    
public:
    /**
     * \brief Constructor with window
     *
     * This constructor can be used to draw a graph on while the window has to
     *  be created by the user.
     * 
     * \param[in,out] window The window to draw on
     */
    GraphDrawer(sf::RenderWindow & window);
    
    /**
     * \brief Draw function for graph
     *
     * This function will draw the nodes en vertices in the window given in the parameter.
     */
    void draw();
        
    /**
     * \brief Reload function
     *
     * This function will reload the graph the std::vectors
     * 
     * \param[in] g The graph to load
     */
    void reload(Graph * g);
        
    /**
     * \brief Clean function
     *
     * This function will clear the std::vectors
     */
    void clear();
	
};

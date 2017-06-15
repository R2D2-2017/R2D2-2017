/**
* \file      graphicsgraph.hh
* \brief     header for graphs in SFML-graphics window
* \author    Leo Jenneskens, René de Kluis, Koen de Groot
* \copyright Copyright (c) 2017, The R2D2 Team
* \license   See LICENSE
*/

#pragma once 

#include <vector>
#include <SFML/Graphics.hpp>

#include "graphicsvertices.hh" 
#include "graphicsnodes.hh" 
#include "graph.hh" 
#include "node.hh"

class GraphDrawer {
private:	
	std::vector<GraphNode> graphNodes;
	std::vector<GraphVertice> graphVertices;
	sf::RenderWindow & window;
public:
    /**
    * \brief Constructor.
    *
    * \param[in,out]    window      The SFML window
    *
    */
	GraphDrawer(sf::RenderWindow & window);

	/**
	*\brief Draw the graph on the SFML window.
	*
	* This function will draw the nodes en vertices in the window given in the parameter.
    * 
	*/
	void draw();
	    
    /**
	*\brief This function will reload the graph.
	*
	* In this function the vectors with Nodes and vertices will be reloaded and again initialised.
    *
    * \param[in,out]    g      Graph to be build
    * 
	*/
	void reload(Graph * g);
	    
    /**
	*\brief Clear the vectors with nodes and vertices
	*
	* This function will clear the std::vectors
    * 
	*/
	void clear();

    /**
    * \brief Get the selected GraphNode.
    * 
    * This function checks all the Graphnodes in the graph if they are selected. 
    * If one of these GraphNodes is selected the function returns the selected GraphNode.
    * In any other case the function will return a dummy GraphNode with the position (0, 0) and named "dummy".
    *
    * \return This function returns The selected GraphNode or Dummy GraphNode.
    *
    */
    GraphNode checkNodeClicked();
};

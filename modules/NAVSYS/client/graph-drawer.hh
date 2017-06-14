/**
* \file      graph-drawer.hh
* \brief     header for graphs in sfmlgraphics window
* \author    Leo Jenneskens, Arco Gelderblom
* \copyright Copyright (c) 2017, The R2D2 Team
* \license   See LICENSE
*/

#pragma once 

#include <vector>
#include "graph-vertice.hh" 
#include "graph-node.hh" 
#include "graph.hh"
#include "../common/pathnode.hh"

#include <SFML/Graphics.hpp>


class GraphDrawer{
private:	

	std::vector<GraphNode> graphNodes;
	std::vector<GraphVertice> graphVertices;
	sf::RenderWindow & window;
	int scaling = 65;

public:
	GraphDrawer(sf::RenderWindow & window);
	/**
	*draw function for graph
	*
	*This function will draw the nodes en vertices in the window given in the parameter.
	*/
	void draw();
	/**
	*reload function
	*
	*This function will reload the graph the std::vectors
	*/
	void reload(Graph * g);
	/**
	*clean function
	*
	*This function will clear the std::vectors
	*/
	void clear();

    /*
    * \brief Set the begin node for the path
    *
    * \param[in] nodeName The name of the node that is the begin
    */
	void setBeginNode(std::string nodeName);

    /*
    * \brief Set the end node for the path
    *
    * \param[in] nodeName The name of the node that is the end
    */
	void setEndNode(std::string nodeName);

    /*
    * \brief Highlight the path that can be taken with a blue color
    *
    * \param[in] path A vector containing the nodes of the path to follow
    */
	void highlightPath(std::vector<PathNode> path);

    GraphNode checkNodeClicked();
};

/**
* \file      graphicsgraph.hh
* \brief     header for graphes in sfmlgraphics window
* \author    Leo Jenneskens
* \copyright Copyright (c) 2017, The R2D2 Team
* \license   See LICENSE
*/
#pragma once 
#include <vector>
#include "graphicsvertices.hh" 
#include "graphicsnodes.hh" 
#include "graph.hh" 
#include "node.hh"

#include <SFML/Graphics.hpp>


class graphicalfactory {
private:	

	std::vector<graphnodes> graphicalnodes;
	std::vector<vertices>graphicalvertices;
	sf::RenderWindow window{ sf::VideoMode{ 1000, 1000}, "SFML window" };

public:

	/**
	*constructor of the grahicalfactory.
	*
	*in this constructor will a stored graph set in objects ready to print on an sfml window
	*
	*
	**/
	/**
	*draw function for graph
	*
	*This function will draw the nodes en vertices in the windwo given in the parameter.
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
	
};



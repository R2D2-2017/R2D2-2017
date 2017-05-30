/**
* \file      graphicsvertices.hh
* \brief     header for vertices between nodes in sfmlgraphics window
* \author    Leo Jenneskens
* \copyright Copyright (c) 2017, The R2D2 Team
* \license   See LICENSE
*/

#pragma once 

#include <SFML/Graphics.hpp>

class GraphVertice{
public:
	/**
	* constructor of the vertices class C	*
	*
	* this constructor ha two paramteters each containing the position of one of the nodes they are attached too.
	*/
	GraphVertice( sf::Vector2f positiona,sf::Vector2f positionb);
	/**
	* draw function
	*
	* function that will draw the vertices on the window out of the parameters
	*/
	void draw( sf::RenderWindow & window ) ;

private:
	sf::Vector2f positiona;
	sf::Vector2f positionb;

};



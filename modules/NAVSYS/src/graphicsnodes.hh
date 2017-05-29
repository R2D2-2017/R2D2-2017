/**
* \file      graphicsnodes.hh
* \brief     header for nodes in sfmlgraphics window
* \author    Leo Jenneskens
* \copyright Copyright (c) 2017, The R2D2 Team
* \license   See LICENSE
*/

#pragma once 

#include <SFML/Graphics.hpp>
#include "super.hpp"


class graphnodes: public super {
public:

	/**
	*costructor for the graphnodes class 
	*
	* the constructor contains twe parameters, The first one is the position of the node in the sfml window.
	* the second parameter is the size of the node in the window, this paramter has a default value of 10.
	*
	*/
	graphnodes( sf::Vector2f position,float size = 10.0);
	/**
	*draw function
	*
	*the draw function will draw the node on the window with the adress of the parameter. 
	*/
	void draw( sf::RenderWindow & window ) override;
	

	
	/**
	*function that wil return the position of the node in the window.
	*returning an sf::Vector2f
	*/
	sf::Vector2f getposition();

   
private:
	
	sf::Vector2f position;
	sf::CircleShape circle;

float size;
	

};



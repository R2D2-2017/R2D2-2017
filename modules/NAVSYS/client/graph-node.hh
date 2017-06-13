/**
* \file      graph-node.hh
* \brief     header for nodes in sfmlgraphics window
* \author    Leo Jenneskens, Arco Gelderblom
* \copyright Copyright (c) 2017, The R2D2 Team
* \license   See LICENSE
*/

#pragma once 

#include <SFML/Graphics.hpp>
class GraphNode{
private:
	
	sf::Vector2f position;
	sf::CircleShape circle;
	sf::Color color = sf::Color::White;

	float size;
	std::string name;
public:

	/**
	*constructor for the graphnodes class 
	*
	* the constructor contains twe parameters, The first one is the position of the node in the sfml window.
	* the second parameter is the size of the node in the window, this paramter has a default value of 10.
	*
	*/
	GraphNode( sf::Vector2f position, std::string name, float size = 10.0);
	/**
	*draw function
	*
	*the draw function will draw the node on the window with the adress of the parameter. 
	*/
	void draw( sf::RenderWindow & window ) ;
	
	/**
	* Get the name of the Node
	* return: returns a std string with the name
	*/
	std::string getName();
	
    void changeColor(sf::Color newColor);

	/**
	*function that wil return the position of the node in the window.
	*returning an sf::Vector2f
	*/
	sf::Vector2f getPosition();

   

	

};



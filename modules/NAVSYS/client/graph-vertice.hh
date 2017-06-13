/**
* \file      graph-vertice.hh
* \brief     header for vertices between nodes in sfmlgraphics window
* \author    Leo Jenneskens, Arco Gelderblom
* \copyright Copyright (c) 2017, The R2D2 Team
* \license   See LICENSE
*/

#pragma once 

#include <SFML/Graphics.hpp>

class GraphVertice{
	
private:
	sf::Vector2f positiona;
	sf::Vector2f positionb;
	sf::Color color = sf::Color::White;
	
public:
	/**
	* constructor of the vertices class C	*
	*
	* this constructor ha two paramteters each containing the position of one of the nodes they are attached too.
	*/
	GraphVertice(sf::Vector2f positiona,sf::Vector2f positionb);
	
	/**
	* draw function
	*
	* function that will draw the vertices on the window out of the parameters
	*/
	void draw(sf::RenderWindow & window);
    
    void changeColor(sf::Color newColor);

    /**
    * Checks whether the vertice is the desired one between the two nodes
    * param 1
    * param 2
    * return bool, 1 if right, 0 if wrong
    */
    bool checkVertice(sf::Vector2f positionNodeOne, sf::Vector2f positionNodeTwo);
};

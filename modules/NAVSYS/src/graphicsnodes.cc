/**
* \file      graphicsnodes.hh
* \brief     nodes in sfmlgraphics window
* \author    Leo Jenneskens
* \copyright Copyright (c) 2017, The R2D2 Team
* \license   See LICENSE
*/

#include <SFML/Graphics.hpp>
#include "graphicsnodes.hh"
#include <iostream>

GraphNode::GraphNode( sf::Vector2f position,float size) :

	position{ position },
	size{size}
	{
		circle.setFillColor(sf::Color::White);
	}

void GraphNode::draw( sf::RenderWindow & window )  {
	circle.setRadius(size);
	circle.setPosition(position);
	circle.setOrigin(size,size);
	circle.setOutlineColor(sf::Color::Red);
	circle.setOutlineThickness(2);
	
	window.draw(circle);
}

sf::Vector2f GraphNode::getPosition() {
	return sf::Vector2f(position.x+size,position.y+size);
}


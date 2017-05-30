/**
* \file      graphicsvertices.cc
* \brief     vertices between nodes in sfmlgraphics window
* \author    Leo Jenneskens
* \copyright Copyright (c) 2017, The R2D2 Team
* \license   See LICENSE
*/

#include <SFML/Graphics.hpp>
#include "graphicsvertices.hh"
#include <iostream>
#include "math.h"
#include "graphicsnodes.hh" 

GraphVertice::GraphVertice(sf::Vector2f positiona,sf::Vector2f positionb) :
	positiona(positiona),
	positionb(positionb)
{}

void GraphVertice::draw( sf::RenderWindow & window ){	
	sf::Vertex line[] = {sf::Vertex(sf::Vector2f(positiona.x,positiona.y)),sf::Vertex(sf::Vector2f(positionb.x,positionb.y))};
	window.draw(line,2,sf::Lines);
}









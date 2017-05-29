#include <SFML/Graphics.hpp>
#include "graphicsvertices.hh"
#include <iostream>
#include "math.h"
#include "graphicsnodes.hh" 
vertices::vertices(sf::Vector2f positiona,sf::Vector2f positionb) :
	positiona{ positiona},
	positionb{positionb}
{}
void vertices::draw( sf::RenderWindow & window ){
	
sf::Vertex line[] = {sf::Vertex(sf::Vector2f(positiona.x,positiona.y)),sf::Vertex(sf::Vector2f(positionb.x,positionb.y))};
	window.draw(line,2,sf::Lines);
}









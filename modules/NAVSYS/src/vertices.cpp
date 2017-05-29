#include <SFML/Graphics.hpp>
#include "vertices.hpp"
#include <iostream>
#include "math.h"
#include "graphnodes.hpp" 
vertices::vertices(sf::Vector2f positiona,sf::Vector2f positionb) :
	positiona{ positiona},
	positionb{positionb}
{}
void vertices::draw( sf::RenderWindow & window ){
	
sf::Vertex line[] = {sf::Vertex(sf::Vector2f(positiona.x,positiona.y)),sf::Vertex(sf::Vector2f(positionb.x,positionb.y))};
	window.draw(line,2,sf::Lines);
}









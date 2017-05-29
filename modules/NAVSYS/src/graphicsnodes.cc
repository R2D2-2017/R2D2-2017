#include <SFML/Graphics.hpp>
#include "graphicsnodes.hh"
#include <iostream>
graphnodes::graphnodes( sf::Vector2f position,float size) :

	position{ position },
	size{size}
{
		circle.setFillColor(sf::Color::White);

	}
void graphnodes::draw( sf::RenderWindow & window )  {
	circle.setRadius(size);
	circle.setPosition(position);
	circle.setOrigin(size,size);
	circle.setOutlineColor(sf::Color::Red);
	circle.setOutlineThickness(2);

	
	window.draw(circle);
}





sf::Vector2f graphnodes::getposition() {
	return sf::Vector2f(position.x+size,position.y+size);
}


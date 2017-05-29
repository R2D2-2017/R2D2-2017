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

bool graphnodes::pressed(sf::RenderWindow & window){
	
	
	sf::Vector2f m(sf::Mouse::getPosition(window).x,sf::Mouse::getPosition(window).y);
	std::cerr<<m.y<<" \n" ;
	if (circle.getGlobalBounds().contains(m)){
		circle.setFillColor(sf::Color::Blue);
		return true;
	}
	return false;
}



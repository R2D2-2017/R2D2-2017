#pragma once 

#include <SFML/Graphics.hpp>
#include "super.hpp"

class vertices: public super {
public:
	vertices( sf::Vector2f positiona,sf::Vector2f positionb);
	void draw( sf::RenderWindow & window ) override;

private:
	sf::Vector2f positiona;
	sf::Vector2f positionb;

};



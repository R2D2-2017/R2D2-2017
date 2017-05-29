#pragma once 

#include <SFML/Graphics.hpp>
#include "super.hpp"


class graphnodes: public super {
public:

	graphnodes( int id,sf::Vector2f position,float size = 10.0);

	void draw( sf::RenderWindow & window ) override;
	bool pressed(sf::RenderWindow & window);
	

	sf::Vector2f getposition();

   
private:
	int id;
	sf::Vector2f position;
	sf::CircleShape circle;

float size;
	

};



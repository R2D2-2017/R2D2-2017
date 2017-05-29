#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
class super {
public:
	bool within(float x, float a, float b) {
		return (x >= a) && (x <= b);
	}


private:
	 virtual void draw(sf::RenderWindow & window) = 0;
		
};


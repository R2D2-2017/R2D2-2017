#pragma once
#include <SFML/Graphics.hpp>

class Gestures{
private:
    sf::RenderWindow & window;
    sf::Vector2i mousePos;
    sf::Clock clock;
public:
    Gestures(sf::RenderWindow & window);
    sf::Vector2i getMouseDrag(const int updateInterval);
};

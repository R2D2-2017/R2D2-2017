#pragma once

#include "SFML/Graphics.hpp"

class Window : public sf::RenderWindow{
private:
    sf::Vector2f windowSize;
    sf::View view;
public:
    Window(sf::VideoMode mode, const sf::String title);
    void setViewPort(sf::Vector2f center, sf::Vector2f size);
    void setViewPos(sf::Vector2f pos);
    void setViewPos(sf::Vector2i pos);
};




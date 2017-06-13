#pragma once

#include "SFML/Graphics.hpp"

class Window : public sf::RenderWindow{
private:
    sf::Vector2f windowSize;
    sf::View view;
public:
    Window(sf::VideoMode mode, const sf::String title, sf::Uint32 = sf::Style::Default);

    void setViewPort(const sf::Vector2f center, const sf::Vector2f size);
    
    void moveViewPort(const sf::Vector2f distance);
    void moveViewPort(const sf::Vector2i distance);

    void setViewPos(const sf::Vector2f pos);
    void setViewPos(const sf::Vector2i pos);

    void updateView();
};




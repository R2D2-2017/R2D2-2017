#pragma once


#include <iostream>
#include <SFML/Graphics.hpp>
#include "Mouse.hh"

class Button {
private:
    sf::RenderWindow & window;
    sf::Vector2f position;
    sf::Vector2f size;
    int id;
    bool isFocused = false;
    bool isVisable;
    std::string fontName = "../client/arial.ttf";
    sf::Font font;
    sf::Text buttonText;
    sf::RectangleShape button;
    
public:
    Button(sf::RenderWindow & window, sf::Vector2f position, sf::Vector2f size, int id, std::string text, bool isVisable = true);
    void draw();
    void setFocus(bool b);
    bool getFocus();
    
    void setSize(sf::Vector2f newSize);
    void setText(std::string newText);
    void setPosition(sf::Vector2f newPosition);
    void setFont(std::string newFont);
    void setVisable(bool visable);

    bool isPressed();
    
    sf::Vector2f getPosition();
    int getId();
    sf::Vector2f getSize();
    sf::FloatRect getBounds();
};
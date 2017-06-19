#pragma once

#include <iostream>
#include <SFML\Graphics.hpp>


class MessageBox {
private:
    sf::RenderWindow & window;
    sf::Text messageText;
    sf::Font font;
    std::string fontName = "../client/arial.ttf";
    sf::Vector2f position;
    sf::View & viewPort;
    std::string message = "Succesfully started up";

public:
    MessageBox(sf::RenderWindow & window, sf::Vector2f position, sf::View viewPort);
    void update();
    void setMessage(std::string newMessage);

};
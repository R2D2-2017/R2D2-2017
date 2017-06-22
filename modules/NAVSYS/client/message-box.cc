/**
* \file      message-box.cc
* \author    Rene de Kluis
* \copyright Copyright (c) 2017, The R2D2 Team
* \license   See ../../LICENSE
*/

#include "message-box.hh"

#include <iostream>

MessageBox::MessageBox(sf::RenderWindow & window, sf::Vector2f position) :
    window(window)
{
    if (!font.loadFromFile(fontName)) {
        std::cerr << "Requested font could not be loaded.\n";
    }
    messageText.setFont(font);
    messageText.setPosition(position);
    messageText.setString(message);
    messageText.setColor(sf::Color::White);
    messageText.setScale({0.5f, 0.5f});
    clock.restart();
}


void MessageBox::draw() {
    const int waitTime = 5;
    if (clock.getElapsedTime() < sf::seconds(waitTime)) {
        window.draw(messageText);
    }
}

void MessageBox::setMessage(std::string newMessage) {
    message = newMessage;
    messageText.setString(message);
    clock.restart();
}


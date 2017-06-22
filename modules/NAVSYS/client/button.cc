/**
 * \file      button.cc
 * \author    Rene de Kluis, Koen de Groot
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See LICENSE
 */

#include "button.hh"
#include <iostream>
#include "mouse.hh"

Button::Button(sf::RenderWindow &window, sf::Vector2f position, 
               sf::Vector2f size, int id, std::string text, bool isVisable):
    window(window),
    position(position),
    size(size),
    id(id),
    isVisible(isVisible)
{
    button.setSize(size);
    button.setOutlineColor(sf::Color::Red);
    button.setOutlineThickness(outlineThickness);
    button.setPosition(position);

    if (!font.loadFromFile(fontName)) {
        std::cerr << "Requested font could not be loaded.\n";
    }
    buttonText.setFont(font);
    buttonText.setPosition(position);
    buttonText.setString(text);
    //Check for sfml version
    #if SFML_VERSION_MINOR == 1
        buttonText.setColor(sf::Color::Black);
    #else
        buttonText.setFillColor(sf::Color::Black);
    #endif
    buttonText.setScale(
        ((1 / buttonText.getGlobalBounds().width) * (size.x-(size.x/xScaleDivider))),
        ((1 / buttonText.getGlobalBounds().height) * (size.y/yScaleDivider))
    );

    if (!isVisible) {
        button.setFillColor(sf::Color::Transparent);
        button.setOutlineColor(sf::Color::Transparent);
        //Check for sfml version
        #if SFML_VERSION_MINOR == 1
            buttonText.setColor(sf::Color::Transparent);
        #else
            buttonText.setFillColor(sf::Color::Transparent);
        #endif
    }
}

void Button::draw() {
    if (isVisible) {
        if (pressedState) {
            button.setFillColor(sf::Color::Blue);
        }
        else {
            button.setFillColor(sf::Color::White);
        }
    }
    pressedState = false;
    window.draw(button);
    window.draw(buttonText);
}

void Button::setState(bool b) {
    pressedState = b;
}

void Button::setSize(sf::Vector2f newSize) {
    button.setSize(newSize);
    size = newSize;
}
void Button::setText(std::string newText) {
    buttonText.setString(newText);
}

void Button::setPosition(sf::Vector2f newPosition) {
    button.setPosition(newPosition);
    buttonText.setPosition(newPosition);
    position = newPosition;
}

void Button::setFont(std::string newFont) {
    font.loadFromFile(newFont);
}

void Button::setVisable(bool visable) {
    isVisible = visable;
    if (visable) {
        button.setFillColor(sf::Color::White);
        button.setOutlineColor(sf::Color::Red);
        //Check for sfml version
        #if SFML_VERSION_MINOR == 1
            buttonText.setColor(sf::Color::Black);
        #else
            buttonText.setFillColor(sf::Color::Black);
        #endif
    }
    else {
        button.setFillColor(sf::Color::Transparent);
        button.setOutlineColor(sf::Color::Transparent);
        //Check for sfml version
        #if SFML_VERSION_MINOR == 1
            buttonText.setColor(sf::Color::Transparent);
        #else
            buttonText.setFillColor(sf::Color::Transparent);
        #endif
    }
}

bool Button::isPressed() {
    if (getBounds().contains(getMousePosition(window))) {
        if (isVisible) {
            pressedState = true;
        }
    }
    return pressedState;
}

sf::Vector2f Button::getPosition(){
    return position;
}
int Button::getId(){
    return id;
}
sf::Vector2f Button::getSize(){
    return size;
}

sf::FloatRect Button::getBounds() {
    return button.getGlobalBounds();
}

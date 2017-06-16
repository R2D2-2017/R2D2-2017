/**
 * \file      mouse.cc
 * \author    René de Kluis, Koen de Groot
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See LICENSE
 */

#include "mouse.hh"

sf::Vector2f Vector2fFromVector2i(sf::Vector2i vector) {
    return sf::Vector2f(static_cast<float>(vector.x), 
                        static_cast<float>(vector.y));
}

sf::Vector2f getMousePosition(sf::RenderWindow & window) {
    return window.mapPixelToCoords(sf::Mouse::getPosition(window));
}
bool GetMouseClick() {
    return sf::Mouse::isButtonPressed(sf::Mouse::Left);
}


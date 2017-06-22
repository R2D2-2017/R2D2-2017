/**
 * \file      gestures.cc
 * \author    Stefan de Beer
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See LICENSE
 */

#include "gestures.hh"
#include <iostream>

Gestures::Gestures(sf::RenderWindow & window):
    window(window),
    mousePos(sf::Vector2i(0, 0))
{}

sf::Vector2i Gestures::getMouseDrag(const int updateInterval,
                                    const int waitForDrag) {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        if(pressClock.getElapsedTime().asMilliseconds() > waitForDrag){
            if (dragClock.getElapsedTime().asMilliseconds() > updateInterval) {
                dragClock.restart();
                sf::Vector2i distance = mousePos - sf::Mouse::getPosition(window); 
                mousePos = sf::Mouse::getPosition(window);
                return distance;
            }
        }
    } else {
        mousePos = sf::Mouse::getPosition(window);
        pressClock.restart();
    }
    return sf::Vector2i(0, 0);
}


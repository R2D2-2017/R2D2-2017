/**
 * \file      gestures.hh
 * \brief     This file constains a class for detecting gestures like mouse 
 *            movements.
 * \author    Stefan de Beer
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See LICENSE
 */

#pragma once
#include <SFML/Graphics.hpp>

/**
 * \brief A class for detecting gestures like mouse movements
 */
class Gestures{
private:
    sf::RenderWindow & window;
    sf::Vector2i mousePos;
    sf::Clock dragClock;
    sf::Clock pressClock;
public:
    /**
     * \brief the constructor Gesture class
     * \param[in] window the sf::RenderWindow in which to detect gestures
     */
    Gestures(sf::RenderWindow & window);
    /**
     * \brief this function detect how far the mouse has moved in the given 
     * update inteval when the left mouse button has been pressed. This function is used for dragging a window using the 
     * mouse.
     * \param  updateInterval The time in milliseconds between every mouse position read
     * \param  waitForFrag The time in milliseconds the left mouse button should be pressed before the function starts measuring the mouse movements.
     * \return how far the mouse has moved in the given update interval
     */
    sf::Vector2i getMouseDrag(const int updateInterval, const int waitForDrag);
};

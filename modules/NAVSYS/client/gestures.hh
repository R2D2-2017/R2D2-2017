/**
 * \file      gestures.hh
 * \brief     This file contains a class for detecting gestures like mouse
 *            movements.
 * \author    Stefan de Beer
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See LICENSE
 */

#pragma once
#include <SFML/Graphics.hpp>

/**
 * \brief A class for detecting gestures like mouse movements.
 */
class Gestures{
private:
    sf::RenderWindow & window;
    sf::Vector2i mousePos;
    sf::Clock clock;
public:
    /**
     * \brief Constructor
     * \param[in] window the sf::RenderWindow in which to detect gestures.
     */
    Gestures(sf::RenderWindow & window);

    /**
     * \brief This function detects how far the mouse has moved in the given
     * update inteval. This function can be used to drag a window using
     * you mouse.
     *
     * \return How far the mouse has moved in the given update interval as a
     * vector.
     */
    sf::Vector2i getMouseDrag(const int updateInterval);
};

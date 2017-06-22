/**
 * \file      mouse.cc
 * \brief     This file has global functions to receive information about the
 *            mouse.
 * \author    Ren� de Kluis, Koen de Groot
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See LICENSE
 */

#pragma once

#include <SFML/Graphics.hpp>

/**
 * \brief Converts a Vector2i to a Vector2f.
 *
 * This function converts a coordinate with two integer values to a coordinate with two floating point values.
 *
 * \param[in]    vector      coordinate with two integer values
 *
 * \return The position of the mouse as a coordinate of two floats.
 */
sf::Vector2f Vector2fFromVector2i(sf::Vector2i vector);


/**
* \brief Gets the position of the mouse.
*
* \param[in,out]    window      The SFML window
*
* \return The current position of the mouse.
*/
sf::Vector2f getMousePosition(sf::RenderWindow & window);


/**
* \brief Checks if the mousebutton is pressed.
*
* \return This function returns True if the mouse is pressed, otherwise it will return False.
*/
bool GetMouseClick();

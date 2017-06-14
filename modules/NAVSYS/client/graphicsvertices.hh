/**
* \file      graphicsvertices.hh
* \brief     header for vertices between nodes in sfmlgraphics window
* \author    Leo Jenneskens
* \copyright Copyright (c) 2017, The R2D2 Team
* \license   See LICENSE
*/

#pragma once 

#include <SFML/Graphics.hpp>

/**
 * \brief Make vertice viseble on screen
 */
class GraphVertice {
private:
    sf::Vector2f positiona;
    sf::Vector2f positionb;

public:
    /**
     * \brief Constructor of the vertices class
     *
     * This constructor ha two paramteters each containing the position of one of the nodes they are attached too.
     *
     * \param[in] positiona The position of the first vertice
     * \param[in] positionb The position of the second vertice
     */
    GraphVertice(sf::Vector2f positiona, sf::Vector2f positionb);

    /**
     * \brief Draw function
     *
     * Function that will draw the vertices on the window out of the parameters
     * \param[in,out] window The window to draw on
     */
    void draw(sf::RenderWindow & window);

};

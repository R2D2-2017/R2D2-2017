/**
 * \file      graph-vertice.hh
 * \brief     Header for vertice between nodes in a SFML graphics window.
 * \author    Leo Jenneskens, Arco Gelderblom
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See LICENSE
 */

#pragma once

#include <SFML/Graphics.hpp>

class GraphVertice{
private:
    sf::Vector2f positionA;
    sf::Vector2f positionB;

    /*
     * \brief The default color for a vertice is white.
     */
    sf::Color color = sf::Color::White;

public:
    /**
     * \brief Constructor
     *
     * This constructor has two paramteters each containing the position of one
     * of the nodes they are attached too.
     *
     * \param[in] positiona The starting position of the vertice.
     * \param[in] positionb The end position of the vertice.
     */
    GraphVertice(sf::Vector2f positionA,sf::Vector2f positionB);

    /**
     * \brief Draws the vertice.
     *
     * Function that draws the vertices on the window.
     *
     * \param[in] window The window where the vertice gets drawn on.
     */
    void draw(sf::RenderWindow & window);

    /*
     * \brief Assigns a new color to the vertice.
     *
     * This function is used to assign new colors to the vertice. Note that the
     * color must be an SFML color object. (sf::Color)
     *
     * \param[in] newColor The color to apply to the vertice.
     */
    void changeColor(sf::Color newColor);

    /**
     * \brief Checks whether the vertice is the one between the two nodes specified
     *
     * Based on sf::Vector2f variables (which are used for x and y coordinates)
     * this function will check whether the vertice is the one connecting these
     * nodes, the order in which the nodes are presented does not make a
     * difference to the function.
     *
     * \param[in] positionNodeOne Position of the first node
     * \param[in] positionNodeTwo Position of the second node
     * \return Returns 1 if the vertice is indeed the vertice connecting the
     *         nodes, otherwise returns 0
     */
    bool checkVertice(sf::Vector2f positionNodeOne, sf::Vector2f positionNodeTwo);
};

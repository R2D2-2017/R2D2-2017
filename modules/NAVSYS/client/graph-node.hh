/**
 * \file      graph-node.hh
 * \brief     Header for nodes in a SFML graphics window
 * \author    Leo Jenneskens, Arco Gelderblom, Ren� de Kluis, Koen de Groot
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See LICENSE
 */

#pragma once

#include <SFML/Graphics.hpp>

class GraphNode {
private:
    sf::Vector2f position;
    sf::CircleShape circle;
    static const unsigned int characterSize = 30;
    static constexpr float positionOffset = 20;
    static const int outlineThickness = 2;

    /**
     * \brief The default color for a node is white.
     */
    sf::Color color = sf::Color::White;

    bool isFocused = false;

    /**
     * \brief A float variable containing the size of the node.
     *
     * The constructor sets this value to 10.0 by default.
     */
    float size;

    /**
     * \brief A string variable containing the name of the node.
     */
    std::string name;

public:
    /**
     * \brief Constructor
     *
     * \param[in] position Position of the GraphNode
     * \param[in] name     Name of the GraphNode
     * \param[in] size   Size of the GraphNode, which has a default value of 10
     *
     */
    GraphNode( sf::Vector2f position, std::string name, float size = 10.0);

    /**
     * \brief Draws the node in the SFML window.
     *
     * \param[in] window The SFML window
     */
    void draw( sf::RenderWindow & window ) ;

    /**
     * \brief Gets the name of the GraphNode.
     *
     * \return The name of the node as a std::string.
     */
    std::string getName();

    /**
     * \brief Gets the global bounds of a GraphNode.
     *
     * The bounds of the buttons are in the following order:
     * {X, Y, Height, Width}.
     *
     * \return The global bounds of the GraphNode.
     *
     */
    sf::FloatRect getBounds();

    /**
     * \brief Check if the GraphNode is selected.
     *
     * \param[in]    window      The SFML window
     *
     * \return This function returns True if the GraphNode is pressed,
     *         otherwise it will return False.
     *
     */
    bool isPressed(sf::RenderWindow & window);

    /**
     * \brief Assigns a new color to the node.
     *
     * This function is used to assign new colors to the node. Note that the
     * color must be an SFML color object. (sf::Color)
     *
     * \param[in] newColor The new color to assign to the node.
     */
    void changeColor(sf::Color newColor);

    /**
     * \brief Gets the position of the node.
     *
     * \return The position of the node as a sf::Vector2f.
     */
    sf::Vector2f getPosition();
};

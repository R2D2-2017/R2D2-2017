/**
* \file      graphicsnodes.hh
* \brief     header for nodes in sfmlgraphics window
* \author    Leo Jenneskens
* \copyright Copyright (c) 2017, The R2D2 Team
* \license   See LICENSE
*/

#pragma once 

#include <SFML/Graphics.hpp>

/**
 * \brief Make node viseble with sfml on screen
 */
class GraphNode {
private:
    sf::Vector2f position;
    sf::CircleShape circle;
    
    float size;
    std::string name;
    
public:
    /**
     * \brief Constructor for the graphnodes class 
     *
     * The constructor contains twe parameters, The first one is the position of the node in the sfml window.
     * The second parameter is the size of the node in the window, this paramter has a default value of 10.
     *
     * \param[in] position The position of the node
     * \param[in] name The name of the node
     * \param[in] size The size of the node in the window (default == 10)
     */
    GraphNode( sf::Vector2f position, std::string name, float size = 10.0);

    /**
     * \brief Draw function
     *
     * The draw function will draw the node on the window with the adress of the parameter.
     * 
     * \param[in,out] window The window to draw on
     */
    void draw( sf::RenderWindow &window ) ;
	
    /**
     * \brief Get position variable
     * 
     * Function that wil return the position of the node in the window.
     * 
     * \return sf::Vector2f with the position of the node
     */
    sf::Vector2f getPosition();

};

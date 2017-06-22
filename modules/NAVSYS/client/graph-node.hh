/**
 * \file      graph-node.hh
 * \brief     header for nodes in sfmlgraphics window
 * \author    Leo Jenneskens, Arco Gelderblom, Rene de Kluis, Koen de Groot
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
    /*
     * \brief The default color for a Vertic is white
     */
    sf::Color color = sf::Color::White;
    
    bool isFocused = false;

    /*
     * \brief The size of the node
     *
     * The size gets a default initialization of 10.0 in the constructor of 
     * this class
     */
    float size;

    /*
     * \brief The name of the node
     */
    std::string name;
public:
    /**
     * \brief constructor for the graphnodes class 
     *
     * \param[in] position Position of the GraphNode
     * \param[in] name     Name of the GraphNode
     * \param[in] size   Size of the GraphNode, which has a default value of 10
     *
     */
    GraphNode( sf::Vector2f position, std::string name, float size = 10.0);

    /**
     * \brief Draw function
     * 
     * \param[in] window Draws the node on this sfml window
     */
    void draw( sf::RenderWindow & window ) ;

    /**
     * \brief Get the name of the GraphNode
     *
     * \return The name of the node as an std::string
     */
    std::string getName();

    /**
     * \brief Get the global bounds of a GraphNode.
     *
     * The bounds of the buttons are in the following order:
     * {X, Y, Height, Width}
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
   	
    /*
     * \brief Assign a new color to the node
     *
     * This function is used to assign new colors to the node. Note that the 
     * color must be an SFML color object. (sf::Color)
     *
     * \param[in] newColor Assign 'newColor' to the node
     */
    void changeColor(sf::Color newColor);

    /**
     * \brief Get the position of the node
     *
     * \return get the position of the node as an sfml vector
     */
    sf::Vector2f getPosition();
	
	    /**
	* \brief Get the "real" non graphical position X coordinate of the node
	*/
    int getRealPositionX();
	
	/**
	* \brief Get the "real" non graphical position Y coordinate of the node
	*/
    int getRealPositionY();
};

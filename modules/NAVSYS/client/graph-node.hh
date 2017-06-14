/**
* \file      graph-node.hh
* \brief     header for nodes in sfmlgraphics window
* \author    Leo Jenneskens, Arco Gelderblom
* \copyright Copyright (c) 2017, The R2D2 Team
* \license   See LICENSE
*/

#pragma once 

#include <SFML/Graphics.hpp>

class GraphNode{
private:
	
	sf::Vector2f position;
	sf::CircleShape circle;
    /*
    * \brief The default color for a Vertic is white
    */
	sf::Color color = sf::Color::White;
    
    bool isFocused = false;
	/*
    * \brief The size of the node
    *
    * The size gets a default initialization of 10.0 in the constructor of this class
    */
    float size;
    /*
    * \brief The name of the node
    */
	std::string name;
public:
	/**
	*constructor for the graphnodes class 
	*
	* the constructor contains twe parameters, The first one is the position of the node in the sfml window.
	* the second parameter is the size of the node in the window, this paramter has a default value of 10.
	*
	*/
	GraphNode( sf::Vector2f position, std::string name, float size = 10.0);
	/**
	*draw function
	*
	*the draw function will draw the node on the window with the adress of the parameter. 
	*/
	void draw( sf::RenderWindow & window ) ;
	
	/**
	* \brief Get the name of the Node
	*/
	std::string getName();

    sf::FloatRect getBounds();

    bool isPressed(sf::RenderWindow & window);
   	
    /*
    * \brief Assign a new color to the node
    *
    * This function is used to assign new colors to the node. Note that the color must be
    * an SFML color object. (sf::Color)
    *
    * \param[in] newColor Assign 'newColor' to the node
    */
    void changeColor(sf::Color newColor);

	/**
	* \brief Get the position of the node
	*/
	sf::Vector2f getPosition();
};

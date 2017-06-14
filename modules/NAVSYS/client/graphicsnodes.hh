/**
* \file      graphicsnodes.hh
* \brief     Header for nodes in SFML-graphics window
* \author    Leo Jenneskens, René de KLuis, Koen de Groot
* \copyright Copyright (c) 2017, The R2D2 Team
* \license   See LICENSE
*/

#pragma once 

#include <SFML/Graphics.hpp>
#include "mouse.hh"

class GraphNode{
private:
	sf::Vector2f position;
	sf::CircleShape circle;
    bool isFocused = false;
	float size;
	std::string name;
public:

	/**
	*\brief constructor for the graphnodes class 
    *
    * \param[in]    position    Position of the GraphNode
    * \param[in]    name        Name of the GraphNode
    * \param[in]    size        Size of the GraphNode, which has a default value of 10
	*
	*/
	GraphNode( sf::Vector2f position, std::string name, float size = 10.0);



	/**
	*\brief Draw function
	*
	* The draw function will draw the node on the window with the adress of the parameter. 
	*/
	void draw( sf::RenderWindow & window ) ;
	

	
	/**
	* \brief This function wil return the position of the node in the window.
    *
	* \return The position of the GraphNode
	*/
	sf::Vector2f getPosition();


    /**
    * \brief Get the global bounds of a GraphNode.
    *
    * The bounds of the buttons are in the following order:\n
    * {X, Y, Height, Width}
    * 
    * \return The global bounds of the GraphNode.
    *
    */
    sf::FloatRect getBounds();


    /**
    * \brief Check if the GraphNode is selected.
    *
    * \param[in,out]    window      The SFML window
    *
    * \return This function returns True if the GraphNode is pressed, otherwise it will return False.
    *
    */
    bool isPressed(sf::RenderWindow & window);


    /**
    * \brief Get the name of the GraphNode.
    *
    * \return The name of the GraphNode.
    *
    */
    std::string getName();
   

	

};



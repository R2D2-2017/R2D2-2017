/**
* \file      graph-node.cc
* \brief     nodes in sfmlgraphics window
* \author    Leo Jenneskens, Arco Gelderblom, René de Kluis, Koen de Groot
* \copyright Copyright (c) 2017, The R2D2 Team
* \license   See LICENSE
*/

#include "graph-node.hh"
#include <iostream>
#include "mouse.hh"

GraphNode::GraphNode( sf::Vector2f position,  std::string name, float size) :
	position{position},
	size{size},
	name{name}
	{
		circle.setFillColor(color);
	}

void GraphNode::draw( sf::RenderWindow & window ) {
    sf::Font font;
    if (!font.loadFromFile("../client/BebasNeue.otf"))
    {
        std::cerr<< "font error\n";
    }
    sf::Text txt;
    txt.setFont(font);
    txt.setString(name);
    txt.setCharacterSize(30);
    txt.setStyle(sf::Text::Bold);
    txt.setColor(sf::Color::Green);
    txt.setPosition(position.x+20,position.y+20);
	window.draw(txt);

	circle.setRadius(size);
	circle.setPosition(position);
	circle.setOrigin(size,size);
    circle.setFillColor(color);
	circle.setOutlineColor(sf::Color::Black);
	circle.setOutlineThickness(2);
	window.draw(circle);
}

std::string GraphNode::getName() {
	return name;
}

void GraphNode::changeColor(sf::Color newColor) {
    color = newColor;
}

sf::Vector2f GraphNode::getPosition() {
	return sf::Vector2f(position.x+size,position.y+size);
}

sf::FloatRect GraphNode::getBounds() {
    sf::FloatRect boundingBox(position.x-size, position.y-size, size*2, size*2);
    return boundingBox;
}

bool GraphNode::isPressed(sf::RenderWindow & window) {
    if (getBounds().contains(getMousePosition(window))) {
        circle.setFillColor(sf::Color::Yellow);
        isFocused = true;
        return true;
    }
    circle.setFillColor(sf::Color::White);
    isFocused = false;
    
    return false;
}

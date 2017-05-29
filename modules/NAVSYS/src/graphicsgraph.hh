#pragma once 
#include <vector>
#include "graphicsvertices.hh" 
#include "graphicsnodes.hh" 
#include "graph.hh" 
#include "node.hh"

#include <SFML/Graphics.hpp>


class graphicalfactory {
private:	
Graph * g;
	std::vector<graphnodes> graphicalnodes;
	std::vector<vertices>graphicalvertices;
	
public:
graphicalfactory(Graph * g );

void draw(sf::RenderWindow & window);
	

	

void draw_path(sf::RenderWindow & window, Node * begin, Node * end);


	






};



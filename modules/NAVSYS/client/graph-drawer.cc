/**
* \file      graph-drawer.cc
* \brief     graphs in sfmlgraphics window
* \author    Leo Jenneskens, Arco Gelderblom
* \copyright Copyright (c) 2017, The R2D2 Team
* \license   See LICENSE
*/
#include "graphicsgraph.hh"

GraphDrawer::GraphDrawer(sf::RenderWindow & window):
		window( window )
{}

void GraphDrawer::draw(){
	for(auto it = graphNodes.begin(); it != graphNodes.end(); ++it) {
		it->draw(window);
	}
	for(auto it = graphVertices.begin(); it != graphVertices.end(); ++it) {
		it->draw(window);
	}

	window.display();
}

void GraphDrawer::reload(Graph * g){

    int scaling = 65;
	clear();
	std::vector<Node> nodeVector = g->getNodes();	
	for(auto it = nodeVector.begin(); it != nodeVector.end(); ++it) {
		graphNodes.push_back(GraphNode(sf::Vector2f(it->getCoordinate().x*scaling,it->getCoordinate().y*scaling),it->getName() ));
	}
	std::vector<Vertice> verticeVector = g->getVertices();	
	for(auto it = verticeVector.begin(); it != verticeVector.end(); ++it) {
		graphVertices.push_back(GraphVertice(sf::Vector2f(it->getCurrent()->getCoordinate().x*scaling,it->getCurrent()->getCoordinate().y*scaling),sf::Vector2f(it->getNeighbour()->getCoordinate().x*scaling,it->getNeighbour()->getCoordinate().y*scaling)));
	}
}

void GraphDrawer::clear(){
	graphNodes.clear();
	graphVertices.clear();
}

void GraphDrawer::setBeginNode(std::string nodeName) {
    for (auto node = graphNodes.begin(); node != graphNodes.end(); ++node) {
        if (node->getName() == nodeName) {
            node->changeColor(sf::Color::Green);
            break;
        }
    }
    draw();
}

void GraphDrawer::setEndNode(std::string nodeName) {
    for (auto node = graphNodes.begin(); node != graphNodes.end(); ++node) {
        if (node->getName() == nodeName) {
            node->changeColor(sf::Color::Red);
            break;
        }
    }
    draw();
}
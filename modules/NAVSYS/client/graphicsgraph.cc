/**
* \file      graphicsgraph.cc
* \brief     graphs in SFML-graphics window
* \author    Leo Jenneskens, René de Kluis, Koen de Groot
* \copyright Copyright (c) 2017, The R2D2 Team
* \license   See LICENSE
*/
#include "graphicsgraph.hh"

GraphDrawer::GraphDrawer(sf::RenderWindow & window):
		window( window )
{}

void GraphDrawer::draw(){
	for(auto & it : graphNodes) {
		it->draw(window);
	}
	for(auto it = graphVertices.begin(); it != graphVertices.end(); ++it) {
		it->draw(window);
	}
}

void GraphDrawer::reload(Graph * g){

    int scaling = 65;
	clear();
	std::vector<Node> nodeVector = g->getNodes();	
	for(auto it = nodeVector.begin(); it != nodeVector.end(); ++it) {
		graphNodes.push_back(new GraphNode(sf::Vector2f(it->getCoordinate().x*scaling,it->getCoordinate().y*scaling),it->getName() ));
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

GraphNode GraphDrawer::checkNodeClicked(){
    GraphNode dummy({ 0,0 },"dummy");
    for (auto & indexer : graphNodes) {
        if (indexer->isPressed(window)) {
            dummy =  *indexer;
        }
    }
    return dummy;
}
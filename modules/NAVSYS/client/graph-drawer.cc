/**
* \file      graph-drawer.cc
* \brief     graphs in sfmlgraphics window
* \author    Leo Jenneskens, Arco Gelderblom
* \copyright Copyright (c) 2017, The R2D2 Team
* \license   See LICENSE
*/
#include "graph-drawer.hh"

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

void GraphDrawer::highlightPath(std::vector<PathNode> path) {
    for (unsigned int i = 0; i < path.size()-1; i++) {
        for(auto vertice = graphVertices.begin(); vertice != graphVertices.end(); ++vertice) {
            if (vertice->checkVertice(sf::Vector2f(path[i].getCoordinate().x*scaling,path[i].getCoordinate().y*scaling),
                                  sf::Vector2f(path[i+1].getCoordinate().x*scaling,path[i+1].getCoordinate().y*scaling))) {
                vertice->changeColor(sf::Color::Blue);
                draw();
            }
        }
    }
}

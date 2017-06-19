/**
 * \file      graph-drawer.cc
 * \author    Leo Jenneskens, Arco Gelderblom
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See LICENSE
 */

#include "graph-drawer.hh"
#include <algorithm>

GraphDrawer::GraphDrawer(sf::RenderWindow & window):
    window(window)
{}

void GraphDrawer::draw() {
    for (auto & it : graphNodes) {
        it.draw(window);
    }
    for (auto & it : graphVertices) {
        it.draw(window);
    }
}

void GraphDrawer::reload(Graph * g) {
    clear();
    std::vector<Node> nodeVector = g->getNodes();	
    for (auto & node : nodeVector) {
        graphNodes.push_back(
            GraphNode(
                sf::Vector2f(
                    node.getCoordinate().x*scaling,
                    node.getCoordinate().y*scaling),
                node.getName()));
    }
    std::vector<Vertice> verticeVector = g->getVertices();	
    for (auto & vertice : verticeVector) {
        graphVertices.push_back(GraphVertice(
            sf::Vector2f(
                vertice.getCurrent()->getCoordinate().x*scaling,
                vertice.getCurrent()->getCoordinate().y*scaling
            ),
            sf::Vector2f(
                vertice.getNeighbour()->getCoordinate().x*scaling,
                vertice.getNeighbour()->getCoordinate().y*scaling
            )));
    }
}

void GraphDrawer::clear() {
    graphNodes.clear();
    graphVertices.clear();
}

void GraphDrawer::setBeginNode(std::string nodeName) {
    // search through the vector for the node and change it's color to green
    for (auto node = graphNodes.begin(); node != graphNodes.end(); ++node) {
        if (node->getName() == nodeName) {
            node->changeColor(sf::Color::Green);
            break;
        }
    }
    draw();
}

void GraphDrawer::setEndNode(std::string nodeName) {
    // search through the vector for the node and change it's color to red
    for (auto node = graphNodes.begin(); node != graphNodes.end(); ++node) {
        if (node->getName() == nodeName) {
            node->changeColor(sf::Color::Red);
            break;
        }
    }
    draw();
}

void GraphDrawer::highlightPath(std::vector<PathNode> path) {
    // loop through the path
    for (size_t i = 0; i < path.size()-1; ++i) {
        for (auto vertice = graphVertices.begin();
            vertice != graphVertices.end(); ++vertice) {
            // check per vertice whether it is the right one
            // if so, highlight it by changing the color to blue
            if (vertice->checkVertice(
                sf::Vector2f(path[i].getCoordinate().x*scaling,
                    path[i].getCoordinate().y*scaling),
                sf::Vector2f(path[i+1].getCoordinate().x*scaling,
                    path[i+1].getCoordinate().y*scaling))) {
                vertice->changeColor(sf::Color::Blue);
                draw();
            }
        }
    }
}

GraphNode GraphDrawer::checkNodeClicked() {
    GraphNode dummy({ 0,0 },"dummy");
    for (auto & indexer : graphNodes) {
        if (indexer.isPressed(window)) {
            dummy = indexer;
        }
    }
    return dummy;
}

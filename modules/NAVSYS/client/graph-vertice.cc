/**
 * \file      graph-vertice.cc
 * \author    Leo Jenneskens, Arco Gelderblom
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See LICENSE
 */

#include "graph-vertice.hh"

GraphVertice::GraphVertice(sf::Vector2f positionA,sf::Vector2f positionB):
    positionA(positionA),
    positionB(positionB)
{}

void GraphVertice::draw(sf::RenderWindow & window) {
    sf::Vertex line[] = {
        sf::Vertex(sf::Vector2f(positionA.x,positionA.y), color),
        sf::Vertex(sf::Vector2f(positionB.x,positionB.y), color)
    };
    window.draw(line,2,sf::Lines);
}

void GraphVertice::changeColor(sf::Color newColor) {
    color = newColor;
}

bool GraphVertice::checkVertice(sf::Vector2f positionNodeOne, 
                                sf::Vector2f positionNodeTwo) {
    if ((positionNodeOne == positionA) && (positionNodeTwo == positionB)) {
        return 1;
    }
    else if ((positionNodeOne == positionB) && 
             (positionNodeTwo == positionA)) {
        return 1;
    }
    return 0;
}

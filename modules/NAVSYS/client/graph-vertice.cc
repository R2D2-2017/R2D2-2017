/**
 * \file      graph-vertice.cc
 * \author    Leo Jenneskens, Arco Gelderblom, Rik Honcoop
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See LICENSE
 */

#include "graph-vertice.hh"

GraphVertice::GraphVertice(sf::Vector2f positiona,sf::Vector2f positionb):
    positiona(positiona),
    positionb(positionb)
{}

void GraphVertice::draw(sf::RenderWindow & window) {
    sf::Vertex line[] = {
        sf::Vertex(sf::Vector2f(positiona.x,positiona.y), color),
        sf::Vertex(sf::Vector2f(positionb.x,positionb.y), color)
    };
    window.draw(line,2,sf::Lines);
}

void GraphVertice::changeColor(sf::Color newColor) {
    color = newColor;
}

bool GraphVertice::checkVertice(sf::Vector2f positionNodeOne, 
                                sf::Vector2f positionNodeTwo) {
    if ((positionNodeOne == positiona) && (positionNodeTwo == positionb)) {
        return 1;
    }
    else if ((positionNodeOne == positionb) && 
             (positionNodeTwo == positiona)) {
        return 1;
    }
    return 0;
}

int GraphVertice::getRealPositionAY(){
    return (int)positiona.y;
}

int GraphVertice::getRealPositionAX(){
    return (int)positiona.x;
}

int GraphVertice::getRealPositionBY(){
    return (int)positionb.y;
}

int GraphVertice::getRealPositionBX(){
    return (int)positionb.x;
}

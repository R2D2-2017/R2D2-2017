/**
 * \file      vectice.cc
 * \author    Robert Bezem, Tim IJntema
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See LICENSE
 */

#include "vertice.hh"

Vertice::Vertice():
    node1(),
    node2(),
    weight(1)
{}

Vertice::Vertice(const Node &node1, const Node &node2, int weight):
    node1(node1),
    node2(node2),
    weight(weight)
{}


std::ostream &operator<<(std::ostream &os, const Vertice &vertice) {
    os << "Vertice with nodes: " << vertice.node1 << " & " << vertice.node2;
    return os;
}

bool Vertice::operator==(const Vertice &rhs) const {
    return node1 == rhs.node1 &&
           node2 == rhs.node2 &&
           weight == rhs.weight;
}

bool Vertice::operator!=(const Vertice &rhs) const {
    return !(rhs == *this);
}

Node * Vertice::getNeighbour() {
    return &node2;
}

Node * Vertice::getCurrent() {
    return &node1;
}

int Vertice::getWeight() {
    return weight;
}

sf::Packet & operator<<(sf::Packet & lhs, const Vertice & vertice) {
    lhs << vertice.node1 << vertice.node2 << vertice.weight;
    return lhs;
}

sf::Packet & operator>>(sf::Packet & lhs, Vertice & vertice) {
    lhs >> vertice.node1 >> vertice.node2 >> vertice.weight;
    return lhs;
}

sf::Packet & operator<<(sf::Packet & lhs, 
                        const std::vector<Vertice> & vertices) {
    lhs << (sf::Uint32)vertices.size();
    for (auto vertice : vertices) {
        lhs << vertice;
    }
    return lhs;
}

sf::Packet & operator>>(sf::Packet & lhs, std::vector<Vertice> & vertices) {
    int vectorSize;
    lhs >> vectorSize;
    
    Vertice vertice;
    for (int i = 0; i < vectorSize; ++i) {
        lhs >> vertice;
        vertices.push_back(vertice);
    }
    return lhs;
}

//
// Created by Robert on 5/19/17.
//

#include "vertice.hh"
Vertice::Vertice(const Node &node1, const Node &node2, int weight)
    : node1(node1), node2(node2), weight(weight) {}

std::ostream &operator<<(std::ostream &os, const Vertice &vertice) {
    os << "Vertice with nodes: " << vertice.node1 << " & " << vertice.node2;
    return os;
}

bool Vertice::operator==(const Vertice &rhs) const {
    return node1 == rhs.node1 &&
        node2 == rhs.node2 && weight == rhs.weight;
}

bool Vertice::operator!=(const Vertice &rhs) const {
    return !(rhs == *this);
}

Node * Vertice::getNeighbour()
{
    return &node2;
}

Node * Vertice::getCurrent()
{
    return &node1;
}

int Vertice::getWeight()
{
    return weight;
}

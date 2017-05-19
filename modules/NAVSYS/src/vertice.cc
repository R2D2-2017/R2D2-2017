//
// Created by Robert on 5/19/17.
//

#include "vertice.hh"
Vertice::Vertice(const Node &node1, const Node &node2)
    : node1(node1), node2(node2) {}
std::ostream &operator<<(std::ostream &os, const Vertice &vertice) {
    os << "Vertice with nodes: " << vertice.node1 << " & " << vertice.node2;
    return os;
}
bool Vertice::operator==(const Vertice &rhs) const {
    return node1 == rhs.node1 &&
        node2 == rhs.node2;
}
bool Vertice::operator!=(const Vertice &rhs) const {
    return !(rhs == *this);
}

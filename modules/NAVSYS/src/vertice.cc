//
// Created by Robert and jeremy on 5/19/17.
//

#include "vertice.hh"

Vertice::Vertice(const std::vector<Node>::iterator node1, const std::vector<Node>::iterator &node2, int weight)
        : node1(node1), node2(node2), weight(weight) {}

std::ostream &operator<<(std::ostream &os, const Vertice &vertice) {
    os << "Vertice with nodes: " << vertice.node1->getNodeName() << " & " << vertice.node2->getNodeName() << " with weight: " << vertice.weight << "\n";
    return os;
}
bool Vertice::operator==(const Vertice &rhs) const {
    return node1 == rhs.node1 &&
        node2 == rhs.node2 && weight == rhs.weight;
}
bool Vertice::operator!=(const Vertice &rhs) const {
    return !(rhs == *this);
}

std::vector<Node>::iterator Vertice::getIteratorNode2() {
    return node1;
}

std::vector<Node>::iterator Vertice::getIteratorNode1() {
    return node2;
}

int Vertice::getWeight() {
    return weight;
}

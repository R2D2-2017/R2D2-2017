//
// Created by Robert  on 5/19/17 and jeremy.
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

///author jeremy
///
/// This function can be used to get the iterator pointing to node2 of the vertice.
///
/// This function is used  in the storage of vertices to get the information of the nodes part
/// part of the vertice .
///
/// Output node iterator pointing to node2 returned.
std::vector<Node>::iterator Vertice::getIteratorNode2() {
    return node1;
}

///author jeremy
///
/// This function can be used to get the iterator pointing to node1 of the vertice.
///
/// This function is used  in the storage of vertices to get the information of the nodes part
/// part of the vertice .
///
/// Output node iterator pointing to node1 returned.
std::vector<Node>::iterator Vertice::getIteratorNode1() {
    return node2;
}

///author jeremy
///
/// This function can be used to get the weight of the vertice.
///
/// This function is used  in the storage of vertices to get the weight of the vertice.
///
/// Output vertice weight returned.
int Vertice::getWeight() {
    return weight;
}

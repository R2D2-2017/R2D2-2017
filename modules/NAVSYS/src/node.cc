//
// Created by Robert  5/19/17.
//
#include "node.hh"
Node::Node(const Coordinate &coordinate, const std::string &name)
    : coordinate(coordinate), name(name) {}
Node::Node(const float x, const float y,  const std::string &name)
    : coordinate(x, y),  name(name) {}
std::ostream &operator<<(std::ostream &os, const Node &node) {
    os << "Node";
    if (node.name != "")
        os << " [" << node.name  <<"]";
    os << " @ " << node.coordinate << "\n";
    return os;
}
bool Node::operator==(const Node &rhs) const {
    return coordinate == rhs.coordinate &&
           name == rhs.name;

}
bool Node::operator!=(const Node &rhs) const {
    return !(rhs == *this);
}
float Node::euclideanDistance(const Node &other) const {
    return coordinate.euclideanDistance(other.coordinate);
}


Coordinate Node::getCoordinate()
{
    return coordinate;

}

std::string Node::getNodeName() const{
    return name;
}



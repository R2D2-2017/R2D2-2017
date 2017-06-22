/**
 * \file      node.cc
 * \author    Robert Bezem
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See LICENSE
 */

#include "node.hh"

Node::Node():
    coordinate(0, 0),
    name("")
{}

Node::Node(const Coordinate &coordinate, const std::string &name):
    coordinate(coordinate),
    name(name)
{}

Node::Node(const float x, const float y,  const std::string &name):
    coordinate(x, y),
    name(name)
{}

Node::Node(const Node & otherNode):
    coordinate(otherNode.getCoordinate()),
    name(otherNode.getName())
{}

std::ostream &operator<<(std::ostream &os, const Node &node) {
    os << "Node";
    if (node.name != "") {
        os << " [" << node.name  << "]";
    }
    os << " @ " << node.coordinate << "\n";
    return os;
}

bool Node::operator==(const Node &rhs) const {
    return coordinate == rhs.coordinate && name == rhs.name;
}

bool Node::operator!=(const Node &rhs) const {
    return !(rhs == *this);
}

float Node::euclideanDistance(const Node &other) const {
    return coordinate.euclideanDistance(other.coordinate);
}

Coordinate Node::getCoordinate() const {
    return coordinate;
}

std::string Node::getName() const {
    return name;
}

sf::Packet & operator<<(sf::Packet & lhs, const Node & node) {
    lhs << node.coordinate << node.name;
    return lhs;
}

sf::Packet & operator>>(sf::Packet & lhs, Node & node) {
    lhs >> node.coordinate >> node.name;
    return lhs;
}

sf::Packet & operator<<(sf::Packet & lhs, const std::vector<Node> & nodes) {
    lhs << static_cast<sf::Uint32> (nodes.size());
    for (auto node : nodes) {
        lhs << node;
    }
    return lhs;
}

sf::Packet & operator>>(sf::Packet & lhs, std::vector<Node> & nodes) {
    int vectorSize;
    lhs >> vectorSize;
    
    Node node;
    for (int i = 0; i < vectorSize; ++i) {
        lhs >> node;
        nodes.push_back(node);
    }
    return lhs;
}

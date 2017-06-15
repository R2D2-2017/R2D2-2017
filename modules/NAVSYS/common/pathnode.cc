/**
* \file      pathnode.cc
* \author    Luuk Steeman
* \copyright Copyright (c) 2017, The R2D2 Team
* \license   See LICENSE
*/

#include "pathnode.hh"

PathNode::PathNode():
    pathDistance(0)
{}

PathNode::PathNode(Node n, Node goal, float g) :
    Node(n.getCoordinate(), n.getName()),
    pathDistance(g)
{
    calcPriority(goal);
}

void PathNode::calcPriority(Node goal) {
    priority = pathDistance + euclideanDistance(goal);
}

void PathNode::setPathDistance(float dist) {
    pathDistance = dist;
}

float PathNode::getPriority() {
    return priority;
}

float PathNode::getPathDistance() {
    return pathDistance;
}

void PathNode::setParent(std::shared_ptr<PathNode> dad) {
    parent = dad;
}

std::shared_ptr<PathNode> PathNode::getParent() {
    return parent;
}

std::ostream &operator<<(std::ostream & os, PathNode node) {
	os << "Node: ";
	if (node.name != "") {
		os << "[" << node.name << "]";
	}

	os << " @ " << node.coordinate;
	return os;
}

sf::Packet & operator<<(sf::Packet & lhs, const PathNode & node) {
    lhs << node.pathDistance << node.priority << node.coordinate << node.name;
    return lhs;
}

sf::Packet & operator>>(sf::Packet & lhs, PathNode & node) {
    lhs >> node.pathDistance >> node.priority >> node.coordinate >> node.name;
    return lhs;
}

sf::Packet & operator<<(sf::Packet & lhs, const std::vector<PathNode> & pathVector) {
    lhs << (sf::Uint32)pathVector.size();
    for (auto node : pathVector) {
        lhs << node;
    }
    return lhs;
}


sf::Packet & operator>>(sf::Packet & lhs, std::vector<PathNode> & pathVector) {
    int vectorSize;
    lhs >> vectorSize;
    
    PathNode node;
    for (int i = 0; i < vectorSize; ++i) {
        lhs >> node;
        pathVector.push_back(node);
    }
    return lhs;
}

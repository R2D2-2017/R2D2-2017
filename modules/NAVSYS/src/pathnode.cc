/**
* \file      pathnode.cc
* \author    Luuk Steeman
* \copyright Copyright (c) 2017, The R2D2 Team
* \license   See LICENSE
*/

#include "pathnode.hh"

PathNode::PathNode(Node n, Node goal, float g) :
    // sets the Node
    Node(n),
    // sets the coordinate
    coordinate(n.getCoordinate()),
    // sets g
    g(g)
{
    //calculate initial f
    calcF(goal);
}

void PathNode::calcF(Node goal)
{
    f = g + euclideanDistance(goal);
}

void PathNode::setG(float dist)
{
    g = dist;
}

float PathNode::getF()
{
    return f;
}

float PathNode::getG()
{
    return g;
}

void PathNode::setParent(std::shared_ptr<PathNode> dad)
{
    parent = dad;
}

std::shared_ptr<PathNode> PathNode::getParent()
{
    return parent;
}

/**
* \file      pathnode.cc
* \author    Luuk Steeman
* \copyright Copyright (c) 2017, The R2D2 Team
* \license   See LICENSE
*/

#include "pathnode.hh"

PathNode::PathNode(Node n, Node goal, float g) :
    // sets the Node
    Node(n.getCoordinate()),
    // sets g
    pathDistance(pathDistance)
{
    //calculate initial f
    calcPriority(goal);
}

void PathNode::calcPriority(Node goal)
{
    priority = pathDistance + euclideanDistance(goal);
}

void PathNode::setPathDistance(float dist)
{
    pathDistance = dist;
}

float PathNode::getPriority()
{
    return priority;
}

float PathNode::getPathDistance()
{
    return pathDistance;
}

void PathNode::setParent(std::shared_ptr<PathNode> dad)
{
    parent = dad;
}

std::shared_ptr<PathNode> PathNode::getParent()
{
    return parent;
}

#include "pathnode.hh"

PathNode::PathNode(Node n, Node goal, float g) :
	Node(n),
	coordinate(n.getCoordinate()),
	g(g)
{
	calcf(goal);
}

void PathNode::calcf(Node goal)
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
#include "pathnode.hh"

PathNode::PathNode(Node n, float g = 0) :
	Node(n),
	coordinate(n.getCoordinate()),
	g(g)
{}

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
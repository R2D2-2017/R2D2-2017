#pragma once

#include "node.hh"

class PathNode : public Node
{
private:
	float g;
	float h;
	float f = 0;
	Coordinate coordinate;

public:
	PathNode(Node n, float g = 0);

	void calcf(Node goal);
	void setG(float dist);
	
	float getG();

	float getF();

};
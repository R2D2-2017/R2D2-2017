#pragma once

#include "node.hh"

class PathNode : public Node
{
private:
	float g;
	float h;
	float f = 0;
	Coordinate coordinate;

	PathNode * parent = nullptr;

public:
	PathNode(Node n, Node goal, float g = 0);
	~PathNode() = default;

	void calcf(Node goal);
	void setG(float dist);
	
	float getG();

	float getF();

	void setParent(PathNode * dad);

	PathNode * getParent();

};
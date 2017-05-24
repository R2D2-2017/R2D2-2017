#pragma once

#include <memory>
#include "node.hh"

class PathNode : public Node
{
private:
	float g;
	float h;
	float f = 0;
	Coordinate coordinate;

	std::shared_ptr<PathNode> parent = nullptr;

public:
	PathNode(Node n, Node goal, float g = 0);
	~PathNode() = default;

	void calcf(Node goal);
	void setG(float dist);
	
	float getG();

	float getF();

	void setParent(std::shared_ptr<PathNode> dad);

	std::shared_ptr<PathNode> getParent();

};
#include "Astar.hh"

std::vector<Node> Astar(Graph * g, Node *start, Node *goal)
{
	std::vector<PathNode> closed_nodes;
	std::vector<PathNode> opened_nodes;
	std::vector<Node> nodes = g->getNodes();
	std::vector<Vertice> vertices = g->getVertices();
	std::vector<Vertice> curvertice;
	PathNode * current;
	float lowest_f;
	std::vector<Node> path;

	float path_dist = 0;
	
	opened_nodes.push_back(PathNode(*start));

	while (!opened_nodes.empty())
	{

		// find the PathNode with lowest f value
		// set it to current
		lowest_f = std::numeric_limits<float>::infinity();
		for (auto it = opened_nodes.begin(); it != opened_nodes.end(); it++)
		{
			it->calcf(*goal);
			if (it->getF() < lowest_f)
			{
				lowest_f = it->getF();
				current = &(*it);
			}
		}
		
		// check to see if current is the goal
		if (current == goal)
		{
			return path;
		}

		// remove current from the opened nodes list and add it to closed
		// shows that the node has been visited
		closed_nodes.push_back(*current);
		opened_nodes.erase(std::remove(opened_nodes.begin(), opened_nodes.end(), *current), opened_nodes.end());
		
		// check which node corresponds with this PathNode
		// add vertices to the list of curvertice based on that

		for (auto it = nodes.begin(); it != nodes.end(); it++)
		{
			if (current->getCoordinate == it->getCoordinate())
			{
				for (auto i = vertices.begin(); i != vertices.end(); i++)
				{
					if (i->getCurrent(*it))
					{
						curvertice.push_back(*i);
					}
				}
				break;
			}
		}

		// open nodes in vertice neighbouring to current node
		// set their g based on vertice weight and previous nodes g

		for (auto it = curvertice.begin(); it != curvertice.end(); it++)
		{
			opened_nodes.push_back(PathNode(*(it->getNeighbour()), float(it->getWeight) + current->getG()));
		}


	}
}
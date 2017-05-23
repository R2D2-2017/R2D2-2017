#include "Astar.hh"

std::vector<Node> Astar(Graph g, Node *start, Node *goal)
{
	Graph closed_nodes;
	Graph opened_nodes;
	Node * current;
	float lowest_f;
	std::vector<Node> path;

	float path_dist = 0;

	opened_nodes.addNode(*start);

	while (!opened_nodes.getNodes().empty())
	{
		lowest_f = std::numeric_limits<float>::infinity();
		for (auto it = opened_nodes.getNodes().begin(); it != opened_nodes.getNodes().end(); it++)
		{
			float low_f = calcf(*it, *goal, path_dist);
			if (low_f < lowest_f)
			{
				lowest_f = low_f;
				current = &(*it);
			}
		}
		
		if (current == goal)
		{
			return path;
		}

		closed_nodes.addNode(*current);
		opened_nodes.removeNode(*current);


	}
}

float calcf(Node n, Node goal, float g)
{
	return n.euclideanDistance(goal) + g;
}
#include "Astar.hh"

std::vector<PathNode> Astar(Graph * g, Node *start, Node *goal)
{
	std::vector<PathNode> closed_nodes;
	std::vector<PathNode> opened_nodes;
	std::vector<Node> nodes = g->getNodes();
	std::vector<Vertice> vertices = g->getVertices();
	std::vector<Vertice> curvertice;
	PathNode * current;
	float lowest_f;
	bool breaker;
	bool in = false;


	float path_dist = 0;
	
	opened_nodes.push_back(PathNode(*start, *goal));

	while (!opened_nodes.empty())
	{

		// find the PathNode with lowest f value
		// set it to current
		lowest_f = std::numeric_limits<float>::infinity();
		for (auto it = opened_nodes.begin(); it != opened_nodes.end(); it++)
		{
			if (it->getF() < lowest_f)
			{
				lowest_f = it->getF();
				current = &(*it);
			}
		}
		
		// check to see if current is the goal
		if (current == goal)
		{
			return reconstruct(current);
		}

		// remove current from the opened nodes list and add it to closed
		// shows that the node has been visited
		closed_nodes.push_back(*current);
		opened_nodes.erase(std::remove(opened_nodes.begin(), opened_nodes.end(), *current), opened_nodes.end());
		
		// check which node corresponds with this PathNode
		// add vertices to the list of curvertice based on that

		for (auto it = nodes.begin(); it != nodes.end(); it++)
		{
			if (current->getCoordinate() == it->getCoordinate())
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
			breaker = false;

			// check if the neighbouring nodes are already closed
			for (auto i = closed_nodes.begin(); i != closed_nodes.end(); i++)
			{
				if (it->getNeighbour()->getCoordinate() == i->getCoordinate())
				{
					breaker = true;
					break;
				}
			}

			// skip this node if it's already closed
			if (breaker)
			{
				continue;
			}

			// check if the node is already opened 
			for (auto i = opened_nodes.begin(); i != opened_nodes.end(); i++)
			{
				in = false;
				if (it->getNeighbour()->getCoordinate() == i->getCoordinate())
				{
					in = true;
					break;
				}
			}

			// calculate the g if the neighbouring nodes are connected through the current node
			float tentative_g = current->getG() + it->getWeight();


			float cur_g;
			for (auto i = opened_nodes.begin(); i != opened_nodes.end(); i++)
			{
				if (i->getCoordinate() == it->getNeighbour()->getCoordinate())
				{
					cur_g = i->getG();
					break;
				}
			}

			// open the node, setting its g

			if (!in)
			{
				opened_nodes.push_back(PathNode(*(it->getNeighbour()), *goal, float(it->getWeight()) + current->getG()));
			}
			// this path is slower than the current node continue to the next neighbour
			else if (tentative_g >= cur_g)
			{
				continue;
			}

			for (auto i = opened_nodes.begin(); i != opened_nodes.end(); i++)
			{
				if (i->getCoordinate() == it->getNeighbour()->getCoordinate())
				{
					i->setParent(current);
					i->setG(tentative_g);
					i->calcf(*goal);
				}
			}
		}
		
	}
}

std::vector<PathNode> reconstruct(PathNode * current)
{
	std::vector<PathNode> path;

	while (current->getParent() != nullptr)
	{
		path.push_back(*current);
		current = current->getParent();
	}
	return path;
}

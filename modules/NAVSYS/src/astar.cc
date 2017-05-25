#include "astar.hh"

vector<PathNode> Astar(Graph * g, Node *start, Node *goal)
{
	// set container variables for use during algorithm
    vector<shared_ptr<PathNode>> closedNodes;
	vector<shared_ptr<PathNode>> openedNodes;
	vector<PathNode> path;

	// Get all the info on the graph
    vector<Node> nodes = g->getNodes();
    vector<Vertice> vertices = g->getVertices();
    vector<Vertice> curVertice;
    shared_ptr<PathNode> current;

	// set variables to use during algorithm
    bool breaker;
    bool in = false;
	float lowestF;
    float path_dist = 0;
    
    openedNodes.push_back(make_shared<PathNode>(PathNode(*start, *goal)));

    while (!openedNodes.empty())
    {
	   
		// find the PathNode with lowest f value
		// set it to current
		lowestF = std::numeric_limits<float>::infinity();
		for (auto it = openedNodes.begin(); it != openedNodes.end(); it++)
		{
			if (it->get()->getF() < lowestF)
			{
				lowestF = it->get()->getF();
				current = *it;
			}
		}

        if (current->getCoordinate() == goal->getCoordinate())
        {
			path = reconstruct(current);
			for (auto i = openedNodes.begin(); i != openedNodes.end(); i++)
			{
				*i = nullptr;
			}
			for (auto i = closedNodes.begin(); i != closedNodes.end(); i++)
			{
				*i = nullptr;
			}
			current = nullptr;
            return path;
        }

        // remove current from the opened nodes list and add it to closed
        // shows that the node has been visited
        closedNodes.push_back(current);
		openedNodes.erase(std::remove(openedNodes.begin(), openedNodes.end(), current), openedNodes.end());
        
        // check which vertice has a N1 with the same coordinates as current pathnode
		// add that vertice to current vertices

		for (auto it = vertices.begin(); it != vertices.end(); it++)
		{
			if (it->getCurrent()->getCoordinate() == current->getCoordinate())
			{
				curVertice.push_back(*it);
			}
		}

        // open nodes in vertice neighbouring to current node
        // set their g based on vertice weight and previous nodes g

        for (auto it = curVertice.begin(); it != curVertice.end(); it++)
        {
            breaker = false;

            // check if the neighbouring nodes are already closed
            for (auto i = closedNodes.begin(); i != closedNodes.end(); i++)
            {
                if (it->getNeighbour()->getCoordinate() == i->get()->getCoordinate())
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
            for (auto i = openedNodes.begin(); i != openedNodes.end(); i++)
            {
                in = false;
                if (it->getNeighbour()->getCoordinate() == i->get()->getCoordinate())
                {
                    in = true;
                    break;
                }
            }

            // calculate the g if the neighbouring nodes are connected through the current node
            float tentative_g = current->getG() + it->getWeight();


            float cur_g;
            for (auto i = openedNodes.begin(); i != openedNodes.end(); i++)
            {
                if (i->get()->getCoordinate() == it->getNeighbour()->getCoordinate())
                {
                    cur_g = i->get()->getG();
                }
            }

            // open the node, setting its g

            if (!in)
            {
                openedNodes.push_back(make_shared<PathNode>(PathNode(*(it->getNeighbour()), *goal, float(it->getWeight()) + current->getG())));
            }
            // this path is slower than the current node continue to the next neighbour
            else if (tentative_g >= cur_g)
            {
                continue;
            }

            for (auto i = openedNodes.begin(); i != openedNodes.end(); i++)
            {
                if (i->get()->getCoordinate() == it->getNeighbour()->getCoordinate())
                {
                    i->get()->setParent(current);
                    i->get()->setG(tentative_g);
                    i->get()->calcF(*goal);
                }
            }
        }
    }
	return path;
}

vector<PathNode> reconstruct(shared_ptr<PathNode> current)
{
    vector<PathNode> path;

    path.push_back(*current);

    while (current->getParent() != nullptr)
    {
        current = current->getParent();
        path.push_back(*current);

    }
    reverse(path.begin(), path.end());
	current = nullptr;
    return path;
}

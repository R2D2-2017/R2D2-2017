#include "astar.hh"

std::vector<std::shared_ptr<PathNode>> Astar(Graph * g, Node *start, Node *goal)
{
    std::vector<std::shared_ptr<PathNode>> closedNodes;
    std::vector<std::shared_ptr<PathNode>> openedNodes;
    std::vector<Node> nodes = g->getNodes();
    std::vector<Vertice> vertices = g->getVertices();
    std::vector<Vertice> curVertice;
    std::shared_ptr<PathNode> current;
    float lowestF;
    bool breaker;
    bool in = false;

    float path_dist = 0;
    
    openedNodes.push_back(std::make_shared<PathNode>(PathNode(*start, *goal)));

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
        
        // check to see if current is the goal
        if (current->getCoordinate() == goal->getCoordinate())
        {
            return reconstruct(current);
        }

        // remove current from the opened nodes list and add it to closed
        // shows that the node has been visited
        closedNodes.push_back(current);
        openedNodes.erase(std::remove(openedNodes.begin(), openedNodes.end(), current), openedNodes.end());
        
        // check which node corresponds with this PathNode
        // add vertices to the list of curVertice based on that

        for (auto it = nodes.begin(); it != nodes.end(); it++)
        {
            if (current->getCoordinate() == it->getCoordinate())
            {
                for (auto i = vertices.begin(); i != vertices.end(); i++)
                {
                    if (i->getCurrent(*it))
                    {
                        curVertice.push_back(*i);
                    }
                }
                break;
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
                openedNodes.push_back(std::make_shared<PathNode>(PathNode(*(it->getNeighbour()), *goal, float(it->getWeight()) + current->getG())));
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
}

std::vector<std::shared_ptr<PathNode>> reconstruct(std::shared_ptr<PathNode> current)
{
    std::vector<std::shared_ptr<PathNode>> path;

    path.push_back(current);

    while (current->getParent() != nullptr)
    {
        current = current->getParent();
        path.push_back(current);

    }
    std::reverse(path.begin(), path.end());
    return path;
}

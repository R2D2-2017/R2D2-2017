#include "astar.hh"

vector<PathNode> aStar(Graph * g, Node *start, Node *goal)
{
    // set container variables for use during algorithm

    // closedNodes are the nodes which have been visited
    vector<shared_ptr<PathNode>> closedNodes;

    // openedNodes are the nodes which have been looked at from other nodes
    // but not yet visited.
    vector<shared_ptr<PathNode>> openedNodes;

    // the path to return once the algorithm is done
    vector<PathNode> path;

    // Get all the information from the graph
    vector<Node> nodes = g->getNodes();
    vector<Vertice> vertices = g->getVertices();

    // curVertice is where the vertices the current node is part of are temporarily stored.
    vector<Vertice> curVertice;

    // current is the node the algorithm is currently looking out from, towards its neighbours
    shared_ptr<PathNode> current;

    // set variables to use during algorithm

    // closed shows if the neighbour being looked at is already closed or not.
    bool closed;

    // opened shows if the neighbour being looked at is already opened or not.
    bool opened = false;

    // lowestF determines what the lowestF is of the neighbours of the current node.
    float lowestF;
    
    // open the start node
    openedNodes.push_back(make_shared<PathNode>(PathNode(*start, *goal)));

    // Algorithm loop
    while (!openedNodes.empty())
    {
       
        // find the neighbouring PathNode with lowest f value
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

        // if the current pathnode is the goal node
        // reconstruct the path from current
        // set all shared_ptrs in the opened- and closedNodes vectors to nullptr to free memory
        // set current to nullptr to free memory
        // return the path
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

        // close the current node to show that this node has already been visited
        closedNodes.push_back(current);
        openedNodes.erase(std::remove(openedNodes.begin(), openedNodes.end(), current), openedNodes.end());
        
        // check which vertices the current node is part of as the origin node
        // add those to the curVertice vector as relevant vertices
        for (auto it = vertices.begin(); it != vertices.end(); it++)
        {
            if (it->getCurrent()->getCoordinate() == current->getCoordinate())
            {
                curVertice.push_back(*it);
            }
        }

        // check if the neighbouring nodes have already been closed
        // ignore them if they are
        for (auto it = curVertice.begin(); it != curVertice.end(); it++)
        {
            closed = false;

            // check if the neighbouring nodes are already closed
            for (auto i = closedNodes.begin(); i != closedNodes.end(); i++)
            {
                if (it->getNeighbour()->getCoordinate() == i->get()->getCoordinate())
                {
                    closed = true;
                    break;
                }
            }

            // skip this node if it's already closed
            if (closed)
            {
                continue;
            }

            // check if the node is already opened 
            for (auto i = openedNodes.begin(); i != openedNodes.end(); i++)
            {
                opened = false;
                if (it->getNeighbour()->getCoordinate() == i->get()->getCoordinate())
                {
                    opened = true;
                    break;
                }
            }

            // calculate what g would be if the neighbour is connected through the current node
            float tentativeG = current->getG() + it->getWeight();

            // get what the neighbouring nodes current g is.
            float curG;
            for (auto i = openedNodes.begin(); i != openedNodes.end(); i++)
            {
                if (i->get()->getCoordinate() == it->getNeighbour()->getCoordinate())
                {
                    curG = i->get()->getG();
                }
            }

            // open the node if it isn't opened yet, setting its g based on the vertice weight and the current nodes g
            if (!opened)
            {
                openedNodes.push_back(make_shared<PathNode>(PathNode(*(it->getNeighbour()), *goal, float(it->getWeight()) + current->getG())));
            }
            
            // check if the new possible path is faster or not, if not skip this neighbour.
            else if (tentativeG >= curG)
            {
                continue;
            }

            // The new path is the fastest possible path so far
            // Set the neighbours parent to the current, set the new g and recalculate f
            for (auto i = openedNodes.begin(); i != openedNodes.end(); i++)
            {
                if (i->get()->getCoordinate() == it->getNeighbour()->getCoordinate())
                {
                    i->get()->setParent(current);
                    i->get()->setG(tentativeG);
                    i->get()->calcF(*goal);
                }
            }
        }
    }
    return path;
}

vector<PathNode> reconstruct(shared_ptr<PathNode> current)
{
    // The path to be returned
    vector<PathNode> path;

    // Add the goal node first
    path.push_back(*current);

    // Keep adding nodes until the current node doesn't have a parent.
    while (current->getParent() != nullptr)
    {
        current = current->getParent();
        path.push_back(*current);

    }

    // Reverse the path to show it in the correct order from start to goal
    reverse(path.begin(), path.end());

    // set the pointer to nullptr
    current = nullptr;

    // return the found path
    return path;
}

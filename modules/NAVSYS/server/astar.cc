/**
* \file      astar.hh
* \author    Luuk Steeman
* \copyright Copyright (c) 2017, The R2D2 Team
* \license   See LICENSE
*/

#include "astar.hh"

#include <algorithm>
#include <limits>
#include <queue>

#include <iostream>

#include "../common/vertice.hh"
#include "../common/coordinate.hh"

/*
 Current output:
 
 
 Starting server
current: 
lowestf: 6.7082 S
tentativeG: 7
curg: 0
openedNodes now:
name: A
closedNodes now:
name: S


tentativeG: 2
curg: 0
openedNodes now:
name: A
name: B
closedNodes now:
name: S


tentativeG: 3
curg: 0
openedNodes now:
name: A
name: B
name: C
closedNodes now:
name: S


current: S
lowestf: 14.2801 A
lowestf: 8.08276 B
lowestf: 7.24264 C
tentativeG: 10
curg: 7


tentativeG: 5
curg: 2




tentativeG: 5
curg: 0
openedNodes now:
name: A
name: B
name: L
closedNodes now:
name: S
name: C




current: C
lowestf: 14.2801 A
lowestf: 8.08276 B
lowestf: 6.41421 L
tentativeG: 12
curg: 7


tentativeG: 7
curg: 2










tentativeG: 9
curg: 0
openedNodes now:
name: A
name: B
name: I
closedNodes now:
name: S
name: C
name: L


tentativeG: 9
curg: 0
openedNodes now:
name: A
name: B
name: I
name: J
closedNodes now:
name: S
name: C
name: L


current: L
lowestf: 14.2801 A
lowestf: 8.08276 B
tentativeG: 9
curg: 7












tentativeG: 6
curg: 9
openedNodes now:
name: A
name: I
name: J
closedNodes now:
name: S
name: C
name: L
name: B


tentativeG: 6
curg: 9
openedNodes now:
name: A
name: I
name: J
closedNodes now:
name: S
name: C
name: L
name: B


tentativeG: 5
curg: 7
openedNodes now:
name: A
name: I
name: J
closedNodes now:
name: S
name: C
name: L
name: B


tentativeG: 6
curg: 0
openedNodes now:
name: A
name: I
name: J
name: D
closedNodes now:
name: S
name: C
name: L
name: B


tentativeG: 3
curg: 0
openedNodes now:
name: A
name: I
name: J
name: D
name: H
closedNodes now:
name: S
name: C
name: L
name: B


tentativeG: 6
curg: 6




current: B
lowestf: 12.2801 A
lowestf: 8 I
lowestf: 6 J
current reconstruc: J
path:
S --> B --> J --> print het path alleen als er een cout achter staat??????



 */

std::vector<PathNode> aStar(Graph & g, Node &start, Node &goal) {
    // set container variables for use during algorithm
    // closedNodes are the nodes which have been visited
    std::vector<std::shared_ptr<PathNode>> closedNodes;

    // openedNodes are the nodes which have been looked at from other nodes
    // but not yet visited.
    std::vector<std::shared_ptr<PathNode>> openedNodes;

    // the path to return once the algorithm is done
    std::vector<PathNode> path;

    // Get all the information from the graph
    std::vector<Node> nodes = g.getNodes();
    std::vector<Vertice> vertices = g.getVertices();

    // curVertice is where the vertices the current node is part of are 
    // temporarily stored.
    std::vector<Vertice> curVertice;

    // current is the node the algorithm is currently looking out from, 
    // towards its neighbours
    std::shared_ptr<PathNode> current = std::make_shared<PathNode>(PathNode(Node(), Node()));

    // set variables to use during algorithm

    // closed shows if the neighbour being looked at is already closed or not.
    bool closed;

    // opened shows if the neighbour being looked at is already opened or not.
    bool opened = false;

    // lowestF determines what the lowestF is of the neighbours of the current 
    // node.
    float lowestF;

    // open the start node
    openedNodes.push_back(std::make_shared<PathNode>(PathNode(start, goal)));

    // Algorithm loop
    while (!openedNodes.empty()) {
        std::cout << "current: " << current->getName() << '\n';
        // find the neighbouring PathNode with lowest f value
        // set it to current
        lowestF = std::numeric_limits<float>::infinity();
        for (auto it = openedNodes.begin(); it != openedNodes.end(); it++) {
            if (it->get()->getPriority() < lowestF) {
                lowestF = it->get()->getPriority();
                current = *it;
                std::cout << "lowestf: " << lowestF << ' ' << current->getName() << '\n';
            }
        }

        /* if the current pathnode is the goal node reconstruct the path from 
           current, set all shared_ptrs in the opened- and closedNodes vectors 
           to nullptr to free memory set current to nullptr to free memory 
           return the path
        */
        if (current->getCoordinate() == goal.getCoordinate()) {
            std::cout << "current reconstruc: " << current->getName() << '\n';
            path = reconstruct(current);
            std::cout << "path:\n";
            for (auto pathnode : path) {
                std::cout << pathnode.getName() << " --> ";
            }
            std::cout << "print het path alleen als er een cout achter staat??????\n";
            return path;
        }

        // close the current node to show that this node has already been 
        // visited
        closedNodes.push_back(current);
        openedNodes.erase(std::remove(openedNodes.begin(), openedNodes.end(), 
                                      current), openedNodes.end());

        // check which vertices the current node is part of as the origin node
        // add those to the curVertice vector as relevant vertices
        for (auto it = vertices.begin(); it != vertices.end(); it++) {
            if (it->getCurrent()->getCoordinate() == current->getCoordinate()) {
                curVertice.push_back(*it);
            }
        }

        // check if the neighbouring nodes have already been closed
        // ignore them if they are
        for (auto it = curVertice.begin(); it != curVertice.end(); it++) {
            closed = false;

            // check if the neighbouring nodes are already closed
            for (auto i = closedNodes.begin(); i != closedNodes.end(); i++) {
                if (it->getNeighbour()->getCoordinate() 
                    == i->get()->getCoordinate()) {
                    closed = true;
                    break;
                }
            }

            // skip this node if it's already closed
            if (closed) {
                std::cout << "\n\n";
                continue;
            }

            // check if the node is already opened
            for (auto i = openedNodes.begin(); i != openedNodes.end(); i++) {
                opened = false;
                if (it->getNeighbour()->getCoordinate() 
                    == i->get()->getCoordinate()) {
                    opened = true;
                    break;
                }
            }
            
            // calculate what g would be if the neighbour is connected through 
            // the current node
            float tentativeG = current->getPathDistance() + it->getWeight();
            std::cout << "tentativeG: " << tentativeG << '\n';
            // get what the neighbouring nodes current g is.
            float curG = 0;
            for (auto i = openedNodes.begin(); i != openedNodes.end(); i++) {
                if (i->get()->getCoordinate() 
                    == it->getNeighbour()->getCoordinate()) {
                    curG = i->get()->getPathDistance();
                }
            }
            std::cout << "curg: " << curG << '\n';

            // open the node if it isn't opened yet, setting its g based on the 
            // vertice weight and the current nodes g
            if (!opened) {
                openedNodes.push_back(std::make_shared<PathNode>(
                                      PathNode(*(it->getNeighbour()), 
                                      goal, 
                                      float(
                                        it->getWeight()) + 
                                        current->getPathDistance())
                                      ));
            }

            // check if the new possible path is faster or not, if not skip this neighbour.
            else if (tentativeG >= curG) {
                std::cout << "\n\n";
                continue;
            }

            // The new path is the fastest possible path so far
            // Set the neighbours parent to the current, set the new g and 
            // recalculate f
            for (auto i = openedNodes.begin(); i != openedNodes.end(); i++) {
                if (i->get()->getCoordinate() 
                    == it->getNeighbour()->getCoordinate()) {
                    i->get()->setParent(current);
                    i->get()->setPathDistance(tentativeG);
                    i->get()->calcPriority(goal);
                }
            }
            
            //extra output
            std::cout << "openedNodes now:\n";
            for (auto & node : openedNodes){
                std::cout << "name: " << node->getName() << '\n';
            }
            std::cout << "closedNodes now:\n";
            for (auto & node : closedNodes){
                std::cout << "name: " << node->getName() << '\n';
            }
            
            std::cout << "\n\n";
        }
    }
    return path;
}

std::vector<PathNode> reconstruct(std::shared_ptr<PathNode> current) {
    // The path to be returned
    std::vector<PathNode> path;

    // Add the goal node first
    path.push_back(*current);

    // Keep adding nodes until the current node doesn't have a parent.
    while (current->getParent() != nullptr) {
        current = current->getParent();
        path.push_back(*current);
    }

    // Reverse the path to show it in the correct order from start to goal
    std::reverse(path.begin(), path.end());

    // set the pointer to nullptr
    current = nullptr;

    // return the found path
    return path;
}

/*
(A)-(B)[3]
(A)-(D)[4]
(A)-(S)[7]
(B)-(A)[3]
(B)-(D)[4]
(B)-(H)[1]
(B)-(I)[4]
(B)-(S)[2]
(C)-(L)[2]
(C)-(S)[3]
(D)-(A)[4]
(D)-(B)[4]
(D)-(F)[5]
(E)-(G)[2]
(E)-(K)[5]
(F)-(D)[5]
(F)-(H)[3]
(G)-(E)[2]
(G)-(H)[2]
(H)-(B)[1]
(H)-(F)[3]
(H)-(G)[2]
(I)-(B)[4]
(I)-(J)[6]
(I)-(K)[4]
(I)-(L)[4]
(J)-(I)[6]
(J)-(K)[4]
(J)-(L)[4]
(K)-(E)[5]
(K)-(I)[4]
(K)-(J)[4]
(L)-(C)[2]
(L)-(I)[4]
(L)-(J)[4]
(S)-(A)[7]
(S)-(B)[2]
(S)-(C)[3]


werkend met alleen
(B)-(S)[2]
(S)-(B)[2]
(I)-(B)[4]
(B)-(I)[4]
(J)-(I)[6]
(I)-(J)[6]
 */
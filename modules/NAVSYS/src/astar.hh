/**
* \file      astar.hh
* \brief     header for functions used by astar algorithm
* \author    Luuk Steeman
* \copyright Copyright (c) 2017, The R2D2 Team
* \license   See LICENSE
*/

#pragma once

#include <algorithm>
#include <limits>
#include <queue>
#include "coordinate.hh"
#include "graph.hh"
#include "node.hh"
#include "pathnode.hh"
#include "vertice.hh"

using namespace std;

/**
* A* algorithm that finds a fast path from start node to goal node
* aStar() is the implementation of the A* pathfinding algorithm
* This algorithm uses the euclidian distance between a node and the goal node
* to predict which node will lead to the fastest path.
* This causes A* to be a very fast and efficient algorithm, but can miss the fastest path at times
* However, the path found is often still the fastest or only slightly slower than the optimal.
* \param g a pointer to the graph in which to search
* \param start a pointer to the chosen starting node
* \param goal a pointer to the chose goal node
* \return a vector of PathNodes showing the path from start to goal
*/
vector<PathNode> aStar(Graph * g, Node *start, Node *goal);

/**
* Reconstructs the path based on PathNodes parents starting from current
* reconstruct() is called when aStar() has found the goal node
* It's called with the current node is the goal node.
* It then loops back from current node through all the parents,
* adding them to a vector of PathNodes until the start PathNode is hit.
* It then reverses the vector to make sure the path is in the correct order.
* \param current The PathNode from which to reconstruct the path.
* \return The vector of PathNodes depicting the fastest path from start- to goal node
*/
vector<PathNode> reconstruct(shared_ptr<PathNode> current);

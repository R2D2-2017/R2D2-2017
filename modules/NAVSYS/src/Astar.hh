#pragma once

#include "vertice.hh"
#include "graph.hh"
#include "coordinate.hh"
#include "node.hh"
#include "pathnode.hh"
#include <algorithm>
#include <limits>

std::vector<Node> Astar(Graph G, Node * start, Node * goal);

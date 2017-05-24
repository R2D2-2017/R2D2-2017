#pragma once

#include "vertice.hh"
#include "graph.hh"
#include "coordinate.hh"
#include "node.hh"
#include "pathnode.hh"
#include <algorithm>
#include <limits>

std::vector<PathNode> Astar(Graph * g, Node *start, Node *goal);

std::vector<PathNode> reconstruct(PathNode * current);
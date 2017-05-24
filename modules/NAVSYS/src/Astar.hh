#pragma once

#include "vertice.hh"
#include "graph.hh"
#include "coordinate.hh"
#include "node.hh"
#include "pathnode.hh"
#include <algorithm>
#include <limits>

std::vector<std::shared_ptr<PathNode>> Astar(Graph * g, Node *start, Node *goal);

std::vector<std::shared_ptr<PathNode>> reconstruct(std::shared_ptr<PathNode> current);
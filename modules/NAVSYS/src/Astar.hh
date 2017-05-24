#pragma once

#include <algorithm>
#include <limits>
#include "coordinate.hh"
#include "graph.hh"
#include "node.hh"
#include "pathnode.hh"
#include "vertice.hh"

std::vector<std::shared_ptr<PathNode>> Astar(Graph * g, Node *start, Node *goal);

std::vector<std::shared_ptr<PathNode>> reconstruct(std::shared_ptr<PathNode> current);

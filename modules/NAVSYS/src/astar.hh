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

vector<PathNode> Astar(Graph * g, Node *start, Node *goal);

vector<PathNode> reconstruct(shared_ptr<PathNode> current);

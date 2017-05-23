#pragma once

#include "vertice.hh"
#include "graph.hh"
#include "coordinate.hh"
#include "node.hh"
#include <limits>

std::vector<Node> Astar(Graph G, Node * start, Node * goal);

float calcf(Node n, Node goal, float g);
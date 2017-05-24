//
// Created by Robert and jeremy on 5/19/17.
//

#ifndef NAVIGATIONSYSTEM_VERTICE_HH
#define NAVIGATIONSYSTEM_VERTICE_HH

#include <ostream>
#include <vector>
#include "node.hh"
class Vertice {
private:
    std::vector<Node>::iterator  node1;
    std::vector<Node>::iterator  node2;
  int weight;
public:
    Vertice(const std::vector<Node>::iterator node1, const std::vector<Node>::iterator &node2, int weight = 1);
  friend std::ostream &operator<<(std::ostream &os, const Vertice &vertice);
  bool operator==(const Vertice &rhs) const;
  bool operator!=(const Vertice &rhs) const;
    std::vector<Node>::iterator getIteratorNode1();
    std::vector<Node>::iterator getIteratorNode2();
    int getWeight();
};

#endif //NAVIGATIONSYSTEM_VERTICE_HH

//
// Created by Robert on 5/19/17.
//

#ifndef NAVIGATIONSYSTEM_VERTICE_HH
#define NAVIGATIONSYSTEM_VERTICE_HH

#include <ostream>
#include "node.hh"
/**
 * \brief Vertice class
 * \details
 * Class that describes a vertice between two nodes
 */
class Vertice {
private:
  Node node1;
  Node node2;
  int weight;
public:
  Vertice(const Node &node1, const Node &node2, int weight = 1);
  friend std::ostream &operator<<(std::ostream &os, const Vertice &vertice);
  bool operator==(const Vertice &rhs) const;
  bool operator!=(const Vertice &rhs) const;
};

#endif //NAVIGATIONSYSTEM_VERTICE_HH

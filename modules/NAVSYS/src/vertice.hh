//
// Created by Robert  on 5/19/17 and jeremy.
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

///author jeremy
///
    /// This function can be used to get the iterator pointing to node1 of the vertice.
///
/// This function is used  in the storage of vertices to get the information of the nodes part
/// part of the vertice .
///
/// Output node iterator pointing to node1 returned.
    std::vector<Node>::iterator getIteratorNode1();

///author jeremy
///
    /// This function can be used to get the iterator pointing to node2 of the vertice.
///
/// This function is used  in the storage of vertices to get the information of the nodes part
/// part of the vertice .
///
/// Output node iterator pointing to node2 returned.
    std::vector<Node>::iterator getIteratorNode2();

///author jeremy
///
/// /// This function can be used to get the weight of the vertice.
///
/// This function is used  in the storage of vertices to get the weight of the vertice.
///
/// Output vertice weight returned.
    int getWeight();
};

#endif //NAVIGATIONSYSTEM_VERTICE_HH

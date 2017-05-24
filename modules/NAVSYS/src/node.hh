//
// Created by Robert and jeremy on 5/19/17.
//

#ifndef NAVIGATIONSYSTEM_NODE_HH
#define NAVIGATIONSYSTEM_NODE_HH

#include <ostream>
#include "coordinate.hh"
class Node {
private:
    Coordinate coordinate;
    int id;
    std::string name;


public:
    Node(const Coordinate &coordinate, int id, const std::string &name = "");
    Node(const float x, const float y, int id, const std::string &name = "");
    friend std::ostream &operator<<(std::ostream &os, const Node &node);
    bool operator==(const Node &rhs) const;
    bool operator!=(const Node &rhs) const;
    float euclideanDistance(const Node &other) const;
    int getNodeId() const;
    std::string getNodeName();
    std::string getCoordinate();
};
#endif //NAVIGATIONSYSTEM_NODE_HH

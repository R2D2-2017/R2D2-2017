//
// Created by Robert and jeremy on 5/19/17.
//

#ifndef NAVIGATIONSYSTEM_NODE_HH
#define NAVIGATIONSYSTEM_NODE_HH

#include <ostream>
#include "coordinate.hh"

/**
 * \brief Node class
 * \details
 * Node class used in the constructions of a \ref Graph and \ref Vertice classes
 */
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

///author jeremy
///
    /// This function can be used to get the id of a node
///
///
/// Output node id  returned
    int getNodeId() const;

///author jeremy
///
    /// This function can be used to get the name of a node.
///
///
/// Output node name returned.
    std::string getNodeName();

///author jeremy
///
    /// This function can be used to get a string representation for a node.
///
/// This function is used for the writing of a nodes coordinate to the node file.
///
/// Output string representation returned.
    std::string getCoordinate();
};


#endif //NAVIGATIONSYSTEM_NODE_HH

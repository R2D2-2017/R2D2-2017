//
// Created by Robert and jeremy on 5/19/17.
//
#include "node.hh"
Node::Node(const Coordinate &coordinate, int id, const std::string &name)
    : coordinate(coordinate), id(id), name(name) {}
Node::Node(const float x, const float y, int id, const std::string &name)
    : coordinate(x, y), id(id), name(name) {}
std::ostream &operator<<(std::ostream &os, const Node &node) {
    os << "Node";
    if (node.name != "")
        os << " Id: " << node.getNodeId() << " [" << node.name  <<"]";
    os << " @ " << node.coordinate << "\n";
    return os;
}
bool Node::operator==(const Node &rhs) const {
    return id == rhs.id;

}
bool Node::operator!=(const Node &rhs) const {
    return !(rhs == *this);
}
float Node::euclideanDistance(const Node &other) const {
    return coordinate.euclideanDistance(other.coordinate);
}


///author jeremy
///
/// This function can be used to get the id of a node.
///
///
/// Output node id  returned.
 int  Node::getNodeId() const {
    return id;
}

///author jeremy
///
/// This function can be used to get the name of a node.
///
///
/// Output node name returned.
std::string Node::getNodeName() {
    return name;
}

///author jeremy
///
/// This function can be used to get a string representation for a node.
///
/// This function is used for the writing of a nodes coordinate to the node file.
///
/// Output string representation returned.
std::string Node::getCoordinate() {
    std::string tmp = "[";
    tmp+=std::to_string((int)coordinate.x);
    tmp+=",";
    tmp+=std::to_string((int)coordinate.y);
    tmp+= "]";
    return tmp;
}


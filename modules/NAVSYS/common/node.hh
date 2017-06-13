/**
 * \file
 * \brief     This file contains the \see Node graph
 * \author    Robert
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See LICENSE
 */

#pragma once
#include <ostream>
#include <string>
#include "coordinate.hh"

/**
 * \brief Node class
 * \details
 * Node class used in the constructions of a \ref Graph and \ref Vertice classes
 */
class Node {
protected:
  Coordinate coordinate;
  std::string name;
  
public:
    Node();
    Node(const Coordinate &coordinate, const std::string &name = "");
    Node(const float x, const float y, const std::string &name = "");
    Node(const Node &otherNode);
    friend std::ostream &operator<<(std::ostream &os, const Node &node);
    bool operator==(const Node &rhs) const;
    bool operator!=(const Node &rhs) const;
    float euclideanDistance(const Node &other) const;
    Coordinate getCoordinate() const;
    std::string getName() const;

    friend sf::Packet & operator<<(sf::Packet & lhs, const Node & node);
    friend sf::Packet & operator>>(sf::Packet & lhs, Node & node);
};

sf::Packet & operator<<(sf::Packet & lhs, const std::vector<Node> & nodes);
sf::Packet & operator>>(sf::Packet & lhs, std::vector<Node> & nodes);
/**
 * \file      node.hh
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
    /**
     * \brief Default constructor
     */
    Node();
    
    /**
     * \brief Constructor with coordinate and name
     * \param[in] coordinate The coordinate of the Node
     * \param[in] name The name of the Node
     */
    Node(const Coordinate &coordinate, const std::string &name = "");
    
    /**
     * \brief Check if node is in graph
     * \param[in] x The x value of the nodes coordinates
     * \param[in] y The y value of the nodes coordinates
     * \param[in] name The name of the node
     */
    Node(const float x, const float y, const std::string &name = "");
    
    /**
     * \brief Copy constructor
     * \param[in] otherNode The node to copy
     */
    Node(const Node &otherNode);
    
    /**
     * \brief Compare two nodes using operator==
     * \param[in] rhs The node to compare to
     * \return True if the nodes are having the same values
     */
    bool operator==(const Node &rhs) const;
    
    /**
     * \brief Compare two nodes using operator!=
     * \param[in] rhs The node to compare to
     * \return True if the nodes are not having the same values
     */
    bool operator!=(const Node &rhs) const;
    
    /**
     * \brief Calculating the euclidean distance
     * \param[in] other The other node used in the calculation
     * \return The calculated distance
     */
    float euclideanDistance(const Node &other) const;
    
    /**
     * \brief Get the coordinate of a node
     * \return The coordinate of a node
     */
    Coordinate getCoordinate() const;
    
    /**
     * \brief Get the name of a node
     * \return The name of a node
     */
    std::string getName() const;
    
    /**
     * \brief Put node in ostream
     * \param[in,out] os The ostream to put the node into
     * \param[in] node The node to put into the ostream
     * \return The ostream package with the node
     */
    friend std::ostream &operator<<(std::ostream &os, const Node &node);

    /**
     * \brief Put node in sf::Packet
     * \param[in,out] lhs The sf::Packet to put the node into
     * \param[in] node The node to put into the sf::Packet
     * \return The sf::Packet package with the node
     */
    friend sf::Packet & operator<<(sf::Packet & lhs, const Node & node);
    
    /**
     * \brief Get node from sf::Packet
     * \param[in,out] lhs The sf::Packet get the node from
     * \param[out] node The node to get from the sf::Packet
     * \return The sf::Packet package without the node
     */
    friend sf::Packet & operator>>(sf::Packet & lhs, Node & node);
};

/**
 * \brief Put node vector in sf::Packet
 * \param[in,out] lhs The sf::Packet to put the vector into
 * \param[in] nodes The vector to put into the sf::Packet
 * \return The sf::Packet package with the vector
 */
sf::Packet & operator<<(sf::Packet & lhs, const std::vector<Node> & nodes);

/**
 * \brief Get node vector from sf::Packet
 * \param[in,out] lhs The sf::Packet get the vector from
 * \param[out] node The vector to get from the sf::Packet
 * \return The sf::Packet package without the vector
 */
sf::Packet & operator>>(sf::Packet & lhs, std::vector<Node> & nodes);
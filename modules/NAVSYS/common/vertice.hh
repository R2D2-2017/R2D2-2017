/**
 * \file      vector.hh
 * \brief     This file contains the \see Vertice class
 * \author    Robert
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See LICENSE
 */

#pragma once

#include <ostream>
#include <vector>

#include "node.hh"

/**
 * \brief Vertice class
 * 
 * \details
 * Class that describes a vertice between two nodes
 */
class Vertice {
private:
    Node &node1;
    Node &node2;
    int weight;
    
public:
    /**
     * \brief Default constructor
     */
    Vertice();
    
    /**
     * \brief Constructor with two nodes and a weight for the vertice
     * 
     * \param[in] node1 The first node for the vertice
     * \param[in] node2 The second node for the vertice
     * \param[in] weight The weight of the vertice
     */
    Vertice(const Node &node1, const Node &node2, int weight = 1);
    
    /**
     * \brief Put vertice in ostream
     * 
     * \param[in] os The ostream to put the vertice into
     * \param[in] vertice The vertice to put into the ostream
     * 
     * \return The ostream package with the vertice
     */
    friend std::ostream &operator<<(std::ostream &os, const Vertice &vertice);
    
    /**
     * \brief Compare two vertices
     * 
     * \param[in] rhs The vertice to compare
     * 
     * \return True if the two vertices are the same
     */
    bool operator==(const Vertice &rhs) const;
    
    /**
     * \brief Compare using operator!=
     * 
     * \param[in] vertice The vertice to compare
     * 
     * \return True if the two vertices are not the same
     */
    bool operator!=(const Vertice &rhs) const;
    
    /**
     * \brief Get the second node
     * 
     * \return The second node
     */
    Node * getNeighbour();
    
    /**
     * \brief Get the first node
     * 
     * \return The first node
     */
    Node * getCurrent();
    
    /**
     * \brief Get the weigth of a vertice
     * 
     * \return The weight of the vertice
     */
    int getWeight();
    
    /**
     * \brief Put node in sf::Packet
     * 
     * \param[in,out] lhs The sf::Packet to put the node into
     * \param[in] vertice The node to put into the sf::Packet
     * 
     * \return The sf::Packet package with the node
     */
    friend sf::Packet & operator<<(sf::Packet & lhs, const Vertice & vertice);
    
    /**
     * \brief Get vertice from sf::Packet
     * 
     * \param[in,out] lhs The sf::Packet get the vertice from
     * \param[out] vertice The vertice to get from the sf::Packet
     * 
     * \return The sf::Packet package without the vertice
     */
    friend sf::Packet & operator>>(sf::Packet & lhs, Vertice & vertice);

};

/**
 * \brief Put vertice vector in sf::Packet
 * 
 * \param[in,out] lhs The sf::Packet to put the vector into
 * \param[in] nodes The vector to put into the sf::Packet
 * 
 * \return The sf::Packet package with the vector
 */
sf::Packet & operator<<(sf::Packet & lhs, const std::vector<Vertice> & vertices);

/**
 * \brief Get vertice vector from sf::Packet
 * 
 * \param[in,out] lhs The sf::Packet get the vector from
 * \param[out] node The vector to get from the sf::Packet
 * 
 * \return The sf::Packet package without the vector
 */
sf::Packet & operator>>(sf::Packet & lhs, std::vector<Vertice> & vertices);
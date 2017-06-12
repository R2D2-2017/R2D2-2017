/**
 * \file
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
 * \details
 * Class that describes a vertice between two nodes
 */
class Vertice {
private:
    Node node1;
    Node node2;
    int weight;
    
public:
    Vertice();
    Vertice(const Node &node1, const Node &node2, int weight = 1);
    friend std::ostream &operator<<(std::ostream &os, const Vertice &vertice);
    bool operator==(const Vertice &rhs) const;
    bool operator!=(const Vertice &rhs) const;
    Node * getNeighbour();
    Node * getCurrent();
    int getWeight();
    
    friend sf::Packet & operator<<(sf::Packet & lhs, const Vertice & vertice);
    friend sf::Packet & operator>>(sf::Packet & lhs, Vertice & vertice);

};



sf::Packet & operator<<(sf::Packet & lhs, const std::vector<Vertice> & vertices);
sf::Packet & operator>>(sf::Packet & lhs, std::vector<Vertice> & vertices);
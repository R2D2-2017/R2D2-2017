/**
* \file      patnode.hh
* \brief     PathNode inherits Node and adds extra variables necessary to calculate the fastest path
* 
* PathNode inherits the Node class and adds a couple of variables and functions.
* Because it inherits the Node class, it can be printed just like regular Nodes
* \author    Luuk Steeman
* \copyright Copyright (c) 2017, The R2D2 Team
* \license   See LICENSE
*/

#pragma once

#include <memory>
#include <ostream>
#include <vector>

#include "node.hh"

/**
 * \brief Hold path from one node to another
 */
class PathNode : public Node {
private:
    /**
     * \brief The total vertice weight from the start node to this node
     * 
     * pathDistance is the total weight of all vertices passed when going to this node from the starting node
     * pathDistance changes depending on what path is taken towards this node
     */
    float pathDistance;

    /**
     * \brief piority of this node, calculated with f = g + h
     * 
     * priority shows how important this node is to the path, lower priority is more important
     * priority is calculated on object construction and when the parent is set
     * This makes sure that priority is always correct
     */
    float priority = 0;

    /**
     * \brief parent is a shared_ptr<PathNode> to the node with the shortest g result
     * 
     * Parent is a shared_ptr<PathNode> which points to the node the algorithm came from before visiting this node
     * parent can change when this node is encountered from a different node where this nodes g would be smaller
     */
    std::shared_ptr<PathNode> parent = nullptr;

public:
    /**
     * \brief Default constructor
     */
    PathNode();
    
    /**
     * \brief PathNode constructor
     * 
     * The constructor sets the PathNodes name and coordinates based on the original node of which it is a copy.
     * 
     * \param[in] n The node this pathnode will base its name and coordinates on
     * \param[in] goal The goal node used to calculate f
     * \param[in] g The total path distance to this node from start to calculate f
     */
    PathNode(Node n, Node goal, float g = 0);

    /**
     * \brief CalcPriority calculates priority
     * 
     * \param[in] goal The goal node
     */
    void calcPriority(Node goal);

    /**
     * \brief Sets pathDistance
     * 
     * \param[in] dist The total pathDistance to this node
     */
    void setPathDistance(float dist);
    
    /**
     * \brief Get the objects pathdistance pathDistance
     * 
     * \return The distance of the path
     */
    float getPathDistance();

    /**
     * \brief Get the priority of a pathnode
     * 
     * \return The priority of a pathnode
     */
    float getPriority();

    /**
     * \brief Sets the parent to a new PathNode
     * 
     * SetParent changes the object parent is pointing to to the new parent
     * 
     * \param[in] dad The new parent
     */
    void setParent(std::shared_ptr<PathNode> dad);

    /**
     * \brief Get the parent node of a node
     * 
     * \return The parent of this node
     */
    std::shared_ptr<PathNode> getParent();

    /**
     * \brief Put pathnode in ostream
     * 
     * \param[in,out] os The ostream to put the pathnode into
     * \param[in] node The pathnode to put into the ostream
     * 
     * \return The ostream package with the pathnode
     */
    friend std::ostream &operator<<(std::ostream & os, PathNode node);
    
    /**
     * \brief Put pathnode in sf::Packet
     * 
     * \param[in,out] lhs The sf::Packet to put the pathnode into
     * \param[in] node The pathnode to put into the sf::Packet
     * 
     * \return The sf::Packet package with the pathnode
     */
    friend sf::Packet & operator<<(sf::Packet & lhs, const PathNode & node);
    
    /**
     * \brief Get pathnode from sf::Packet
     * 
     * \param[in,out] lhs The sf::Packet get the pathnode from
     * \param[out] node The pathnode to get from the sf::Packet
     * 
     * \return The sf::Packet package without the pathnode
     */
    friend sf::Packet & operator>>(sf::Packet & lhs, PathNode & node);
};

/**
 * \brief Put pathnode vector in sf::Packet
 * 
 * \param[in,out] lhs The sf::Packet to put the vector into
 * \param[in] nodes The vector to put into the sf::Packet
 * 
 * \return The sf::Packet package with the vector
 */
sf::Packet & operator<<(sf::Packet & lhs, const std::vector<PathNode> & pathVector);

/**
 * \brief Get pathnode vector from sf::Packet
 * 
 * \param[in,out] lhs The sf::Packet get the vector from
 * \param[out] node The vector to get from the sf::Packet
 * 
 * \return The sf::Packet package without the vector
 */
sf::Packet & operator>>(sf::Packet & lhs, std::vector<PathNode> & pathVector);

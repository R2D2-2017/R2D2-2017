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
#include <string>
#include "node.hh"

class PathNode : public Node
{
private:
    
    /**
    * The total vertice weight from the start node to this node
    * pathDistance is the total weight of all vertices passed when going to this node from the starting node
    * pathDistance changes depending on what path is taken towards this node
    */
    float pathDistance;

    /**
    * piority of this node, calculated with f = g + h
    * priority shows how important this node is to the path, lower priority is more important
    * priority is calculated on object construction and when the parent is set
    * This makes sure that priority is always correct
    */
    float priority = 0;

    /**
    * parent is a shared_ptr<PathNode> to the node with the shortest g result
    * parent is a shared_ptr<PathNode> which points to the node the algorithm came from before visiting this node
    * parent can change when this node is encountered from a different node where this nodes g would be smaller
    */
    std::shared_ptr<PathNode> parent = nullptr;

public:
    /**
    * PathNode constructor
    * The constructor sets the PathNodes name and coordinates based on the original node of which it is a copy.
    * \param n the node this pathnode will base its name and coordinates on
    * \param goal the goal node used to calculate f
    * \param g the total path distance to this node from start to calculate f
    */
    PathNode(Node n, Node goal, float g = 0);

    /**
    * calcPriority calculates priority
    * \param goal the goal node
    */
    void calcPriority(Node goal);

    /**
    * sets pathDistance
    * \param dist The total pathDistance to this node
    */
    void setPathDistance(float dist);
    
    /**
    * returns pathDistance
    * \return  pathDistance
    */
    float getPathDistance();

    /**
    * returns priority
    * \return priority
    */
    float getPriority();

    /**
    * Sets the parent to a new PathNode
    * setParent changes the object parent is pointing to to the new parent
    * \param dad the new parent
    */
    void setParent(std::shared_ptr<PathNode> dad);

    /**
    * Returns parent
    * \return the parent of this node
    */
    std::shared_ptr<PathNode> getParent();

    friend std::ostream &operator<<(std::ostream & os, PathNode node);
        
    friend sf::Packet & operator<<(sf::Packet & lhs, const std::vector<PathNode> & pathVector);
    friend sf::Packet & operator>>(sf::Packet & lhs, std::vector<PathNode> & pathVector);
    friend sf::Packet & operator<<(sf::Packet & lhs, const PathNode & node);
    friend sf::Packet & operator>>(sf::Packet & lhs, PathNode & node);
};

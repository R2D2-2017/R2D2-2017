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
#include "node.hh"

class PathNode : public Node
{
private:
    
    /**
    * The total vertice weight from the start node to this node
    * g is the total weight of all vertices passed when going to this node from the starting node
    * g changes depending on what path is taken towards this node
    */
    float g;

    /**
    * The euclidian (as the crow flies) distance to the end node
    * h is the straight distance between this node and the end node, calculated with the pythagorian theorem
    * In this class, it's calculated by calling the euclideanDistance(const Node &other) function from node
    * Which in turn calls the euclideanDistance(const Coordinate &rhs) function of coordinate
    */
    float h;

    /**
    * f is the priority of this node, calculated with f = g + h
    * f is used to determine how high a nodes priority is, a lower f is a higher priority
    * f is calculated on object construction and when the parent is set
    * This makes sure that f is always correct
    */
    float f = 0;

    /**
    * coordinate is the PathNodes location
    */
    Coordinate coordinate;

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
    * calcF calculates f
    * \param goal the goal node
    */
    void calcF(Node goal);

    /**
    * sets G
    * \param dist The total g distance to this node
    */
    void setG(float dist);
    
    /**
    * returns g
    * \return  g
    */
    float getG();

    /**
    * returns f
    * \return f
    */
    float getF();

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

};

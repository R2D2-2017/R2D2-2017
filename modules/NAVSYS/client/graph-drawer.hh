/**
 * \file      graph-drawer.hh
 * \brief     header for graphs in sfmlgraphics window
 * \author    Leo Jenneskens, René de Kluis, Koen de Groot, Arco Gelderblom
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See LICENSE
 */

#pragma once 

#include <vector>
#include <SFML/Graphics.hpp>
#include "graph-vertice.hh" 
#include "graph-node.hh" 
#include "graph.hh"
#include "../common/pathnode.hh"


class GraphDrawer {
private:
    std::vector<GraphNode> graphNodes;
    std::vector<GraphVertice> graphVertices;
    sf::RenderWindow & window;
    const int scaling = 65;
public:
    /**
     * \brief Constructor.
     *
     * \param[in,out]    window      The SFML window
     *
     */
    GraphDrawer(sf::RenderWindow & window);

    /**
     * \brief Draw the graph on the SFML window.
     *
     * This function will draw the nodes en vertices in the window given in the
     * constructor of the class.
     * 
     */
    void draw();

    /**
     * \brief This function will reload the graph.
     *
     * In this function the vectors with Nodes and vertices will be reloaded 
     * and again initialised.
     *
     * \param[in,out]    g      Graph to be build
     * 
     */
    void reload(Graph * g);

    /**
     * \brief Clear the vectors with nodes and vertices
     *
     * calling this function will empty the vectors 
     * storing the node en vertice vectors
     *
     */
    void clear();

    /**
     * \brief Set the begin node for the path
     *
     * \param[in] nodeName The Unique name of the node that is the begin
     */
    void setBeginNode(std::string nodeName);

    /**
     * \brief Set the end node for the path
     *
     * \param[in] nodeName The Unique name of the node that is the end
     */
    void setEndNode(std::string nodeName);

    /**
     * \brief Highlight the path that can be taken with a blue color
     *
     * \param[in] path A vector containing the nodes of the path to follow
     */
    void highlightPath(std::vector<PathNode> path);

    /**
     * \brief Get the selected GraphNode.
     * 
     * This function checks all the Graphnodes in the graph if they are 
     * selected. If one of these GraphNodes is selected the function returns
     * the selected GraphNode. In any other case the function will return a 
     * dummy GraphNode with the position (0, 0) and named "dummy".
     *
     * \return This function returns The selected GraphNode or Dummy GraphNode.
     *
     */
    GraphNode checkNodeClicked();
};

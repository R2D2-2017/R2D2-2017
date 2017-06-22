/**
 * \file      graph-drawer.hh
 * \brief     Header for drawing graphs in a SFML graphics window.
 * \author    Leo Jenneskens, René de Kluis, Koen de Groot, Arco Gelderblom
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See LICENSE
 */

#pragma once

#include <memory>
#include <SFML/Graphics.hpp>
#include "graph-vertice.hh"
#include "graph-node.hh"
#include "graph.hh"
#include "pathnode.hh"

struct clickedNode {
    std::unique_ptr<GraphNode> node = nullptr;
    bool clicked = false;
};

class GraphDrawer {
private:
    std::vector<GraphNode> graphNodes;
    std::vector<GraphVertice> graphVertices;
    sf::RenderWindow & window;
    const int scaling = 65;
public:
    /**
     * \brief Constructor
     *
     * \param[in]    window      The SFML window
     *
     */
    GraphDrawer(sf::RenderWindow & window);

    /**
     * \brief Draw the graph on the SFML window.
     *
     * This function draws the nodes en vertices on the window given in the
     * constructor of the class.
     */
    void draw();

    /**
     * \brief This function reloads the graph.
     *
     * This function reinitializes the nodes and vertice.
     *
     * \param[in,out]    g      Graph to be build
     *
     */
    void reload(Graph & g);

    /**
     * \brief Clears the vectors containing nodes and vertice.
     *
     * This function empties the vectors
     * containing the nodes en vertice.
     *
     */
    void clear();

    /**
     * \brief Sets the begin node for the path.
     *
     * \param[in] nodeName The unique name of the start node.
     */
    void setBeginNode(std::string nodeName);

    /**
     * \brief Sets the end node for the path.
     *
     * \param[in] nodeName The unique name of the end node.
     */
    void setEndNode(std::string nodeName);

    /**
     * \brief Highlights the path that can be taken with a blue color.
     *
     * \param[in] path A vector containing the nodes of the path to follow.
     */
    void highlightPath(std::vector<PathNode> path);

    /**
     * \brief Gets a clickedNode
     *
     * This function checks if any of the nodes in the graph has been selected.
     * If one of the nodes has been selected, the function returns a
     * clickedNode struct.
     *
     * \return A clickedNode struct containing the clicked node.
     *
     */
     clickedNode checkNodeClicked();
};

/**
 * \file 
 * \brief     Header for client side connection code for NAVSYS API
 * \author    Philippe Zwietering, Arco Gelderblom
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See ../../LICENSE
 */

#pragma once

#include <SFML/Network.hpp>
#include <SFML/System/Vector2.hpp>
#include <string>

#include "../common/graph-factory.hh"
#include "graph-drawer.hh"
#include "../common/graph-input.hh"
#include "button.hh"
#include "mouse.hh"
#include "../common/graph.hh"
#include "../common/protocol.hh"

#include <exception>



enum class button {ShutDown,StartNode,EndNode};

/**
 * \brief Client class
 *
 * This class should contain all the functionality a navigation system should ever want to have.
 *  It makes a connection with a server object via TCP and in the future will handle user input.
 */
class Client {
private:
	sf::IpAddress ipAddress;
	uint16_t port;
	sf::TcpSocket socket;
    sf::Vector2f buttonSize = {100,30};
    Graph g;

    /**
     * \brief Send a sf packet with error checking
     * 
     * \param[in] p The packet to be send
     */
    void sendPacket(sf::Packet & p);
    
    /**
     * \brief Receive a packet and check if it has been received correctly
     * 
     * \param[in] p The packet to put the received data in
     */
    void checkPacketCorrectlyReceived(sf::Packet & p);
    
	/**
	* \brief Methode that checks if a selected start node can be startnode
	*
	* \param[in] nodes this is a vector of graphnodes that contain the position and name of the nodes
	* \param[in] vertices this is a vector og graphvertices
	* \param[in] node name that needs te be compaired to a node is nodes
	* \param[out] boolean check true if node can be start node
	*/
    bool checkIfNodesCanBeStartNode(std::vector<GraphNode> nodes, std::vector<GraphVertice> vertices, std::string nodeName);
    
	/**
	* \brief Methode that checks if a slected end node can be a endNode
	*
	* \param[in] nodes this is a vector of graphnodes that contain the position and name of the nodes 
	* \param[in] vertices this is a vector og graphvertices 
	* \param[in] node name that needs te be compaired to a node is nodes
	* \param[out] boolean check true if node can be end node
	*/
    bool checkIfNodesCanBeEndNode(std::vector<GraphNode> nodes, std::vector<GraphVertice> vertices, std::string nodeName);
    
    
	/**
	* \brief connects/reconnects to the server is methode is called.
	*
	*/
    void connectToServer();
    
public:

    /**
     * \brief Client constructor
     *
     * \param[in] ipAddress sf::IpAddress, the IP address of the server
     * \param[in] port uint16_t, the port of the server
     */
    Client(sf::IpAddress ipAddress, uint16_t port);
    
    

    /**
     * \brief Runs the client
     *
     * Runs all the client things. Only functionality right now is connecting with a server,
     *  asking for a graph and displaying all server messages on screen.
     */
    void run();
    
    /**
     * \brief Requests the database from the server
     *
     * this function sends the requests for  the data contained in the node and vertices file.
     */
    void getDatabaseFromServer();

    /**
     * \brief Requests the path from the server
     *
     * this function sends the requests for  the path between two nodes.
     */
    void requestPath(StartEndNodeData nodes);
    
    /**
     * \brief Request data from the database using a command
     *
     * \param[in] cmd The command to send 
     */
    void requestDatabaseUsingCommand(const command & cmd);


    /**
     * \brief Execute a command corresponding with the pressed button.
     *
     * \param[in,out]    window          The SFML window
     * \param[in]        buttonId        The ID of the selected button
     * \param[in]        clickedNode     The selected GraphNode
     */
    void buttonAction(sf::RenderWindow & window, int buttonId, GraphNode clickedNode);
};

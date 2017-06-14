/**
 * \file
 * \brief     Header for client side connection code for NAVSYS API
 * \author    Philippe Zwietering
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See ../../LICENSE
 */

#pragma once

#include <SFML/Network.hpp>
#include <iostream>
#include <fstream>
#include <string>

#include "../common/graph-factory.hh"
#include "graph-drawer.hh"
#include "../common/graph-input.hh"
#include "../common/protocol.hh" 
#include "Button.hh"
#include "Mouse.hh"

enum class button {ShutDown,StartNode,EndNode};

/**
 * \brief Client class
 *
 * This class should contain all the functionality a navigation system should ever want to have. It makes a connection with a server object via TCP and in the future will handle user input.
 */
class Client{
private:
	sf::IpAddress ipAddress;
	uint16_t port;
	sf::TcpSocket socket;
    Graph g;
    sf::Vector2f buttonSize = {100,30};
        /**
         * \brief Send a sf packet with error checking
         * 
         * \param[in] p The packet to be send
         */
        void sendPacket(sf::Packet & p);
        
        void checkPacketCorrectlyReceived(sf::Packet & p);
public:
/**
 * \brief Client constructor
 *
 * \param[in]     ipAddress		sf::IpAddress, the IP address of the server
 * \param[in]	  port			uint16_t, the port of the server
 */
	Client(sf::IpAddress ipAddress, uint16_t port);

/**
 * \brief Runs the client
 *
 * Runs all the client things. Only functionality right now is connecting with a server, asking for a graph and displaying all server messages on screen.
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
        
    void requestDatabaseUsingCommand(const command & cmd);
	void requestPath(std::string startNode, std::string endNode);

    void buttonAction(sf::RenderWindow & window, int buttonId, GraphNode clickedNode);
};


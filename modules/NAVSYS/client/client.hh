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
#include "graphicsgraph.hh"


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

 * \brief Requests  nodes from the server
 *
 * Sends a request for nodes from the server, by just sending a sf::Packet with a std::string.
 */
	void requestNodes();

    /**
 * \brief Requests vertices from the server
 *
 * Sends a request for vertices to the server, by just sending a sf::Packet with a std::string.
 */
    void requestVertices();

	/**
* \brief Requests the database from the server
*
* this function sends the requests for  the data contained in the node and vertices file.

*/
    void getDatabaseFromServer();

};


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
#include <string>

class Client{
private:
	sf::IpAddress ipAddress;
	uint16_t port;
	sf::TcpSocket socket;
	sf::Socket::Status connectionStatus;

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
 * \brief Requests a graph from the server
 *
 * Sends a request for a graph from the server, by just sending a sf::Packet with a std::string.
 */
	void requestGraph();
};
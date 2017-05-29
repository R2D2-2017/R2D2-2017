/**
 * \file
 * \brief     Header for client side connection code for NAVSYS API
 * \author    Philippe Zwietering
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See ../../LICENSE
 */

#ifndef NAVIGATIONSYSTEM_CLIENT
#define NAVIGATIONSYSTEM_CLIENT

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
	Client(const sf::IpAddress ipAddress, uint16_t port);
	void run();
	void requestGraph();
};

#endif //CLIENT
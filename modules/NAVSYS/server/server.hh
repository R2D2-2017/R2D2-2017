/**
 * \file
 * \brief     Header for server side code for NAVSYS API
 * \author    Philippe Zwietering
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See ../../LICENSE
 */

#ifndef NAVIGATIONSYSTEM_SERVER
#define NAVIGATIONSYSTEM_SERVER

#include <SFML/Network.hpp>
#include <vector>
#include <memory>
#include <string>
#include <iostream>

class Server{
private:
    uint16_t port;
    sf::TcpListener socketListener;
    std::vector<sf::TcpSocket*> connectedClientSockets;
    sf::SocketSelector socketSelector;

public:
    Server(const uint16_t port);
    void broadcastMessage(const std::string & message);
    void run();
    void handleInput(const std::string & input);
};

#endif //SERVER
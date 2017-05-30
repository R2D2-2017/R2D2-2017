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
/**
 * \brief Server constructor
 *
 * \param[in]     port    the port the server needs to check for, uint16_t
 */
    Server(const uint16_t port);

/**
 * \brief Broadcasts a message to all available clients
 *
 * This functions doesn't check yet if clients are still connected, so it can return with error messages if clients have already left.
 * \param[in]     message    message that needs to broadcast, std::string
 */
    void broadcastMessage(const std::string & message);

/**
 * \brief Runs the server
 *
 * This function gets called in the main, and handles everything that might happen. It isn't perfect yet, a lot of functionality is still missing.
 */
    void run();

/**
 * \brief Handles client input
 *
 * This functions only handles a graph request right now, which is just a dummy.
 * 
 * \param[in]     input    std::string that states the message received from a client
 */
    void handleInput(const std::string & input);
};

#endif //SERVER
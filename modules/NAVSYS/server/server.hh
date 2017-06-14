/**
 * \file
 * \brief     Header for server side code for NAVSYS API
 * \author    Philippe Zwietering
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See ../../LICENSE
 */

#pragma once

#include <SFML/Network.hpp>
#include <vector>
#include <memory>
#include <string>

#include "../common/pathnode.hh"
#include "../common/protocol.hh"
#include "../common/graph.hh"
#include "../common/graph-factory.hh"

typedef std::shared_ptr<sf::TcpSocket> sharedSocketPtr_t;

/**
 * \brief Server class
 *
 * This class handles everything an API server should do, it accepts new clients over TCP and sends messages to them after requests.
 */
class Server{
private:
    uint16_t port;
    sf::TcpListener socketListener;
    std::vector<sharedSocketPtr_t> connectedClientSockets;
    sf::SocketSelector socketSelector;
    Graph g;

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
    template <typename T>
    void broadcastMessage(const command &cmd, const T & message);

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

    void handleInput(sf::Packet & p);
    
};



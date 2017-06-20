/**
 * \file      server.hh
 * \brief     Header for server side code for NAVSYS API
 * \author    Philippe Zwietering, Tim IJntema
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See ../../LICENSE
 */

#pragma once

#include <SFML/Network.hpp>
#include <memory>

#include "../common/protocol.hh"
#include "../common/graph.hh"

typedef std::shared_ptr<sf::TcpSocket> sharedSocketPtr_t;

/**
 * \brief Server class
 *
 * This class handles everything an API server should do, it accepts new clients 
 * over TCP and sends messages to them after requests.
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
     * \param[in] port The port the server needs to check for, uint16_t
     */
    Server(const uint16_t port);

    /**
     * \brief Broadcasts a message to all available clients
     *
     * This functions doesn't check yet if clients are still connected, so it 
     * can return with error messages if clients have already left.
     *
     * \param[in] message Message that needs to broadcast, std::string
     */
    template <typename T>
    void broadcastMessage(const command &cmd, const T & message);

    /**
     * \brief Runs the server
     *
     * This function holds the main loop of the server. If you want to edit the
     * functionality of the server that can be done here.
     */
    void run();

    /**
     * \brief Handles all client input
     *
     * This function handles any input from the client. It should receive a
     *  command using a packet followed by possibly some data that should come
     *  with that command. Some processing is done and the function sends a
     *  command back to the client to make sure the client knows what he wanted
     *  to do has been done. 
     *
     * \param[in] p  The packet containing the command and data for that command
     */
    void handleInput(sf::Packet & p);

};

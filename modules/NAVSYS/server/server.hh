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
    std::vector<sharedSocketPtr_t> disconnectClients;

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
     * This functions sends a message to all connected clients
     *
     * \param[in] message Message that needs to be broadcasted
     */
    template <typename T>
    void broadcastMessage(const command &cmd, const T &message);
    
    /**
     * \brief Send a message to a specific client
     * 
     * \param[in] client The client to send the message to
     * \param[in] cmd The command to send to the client
     * \param[in] message The message to send to the client
     */
    template <typename T>
    void sendMessageToClient(sharedSocketPtr_t &client, const command &cmd, const T &message);

    /**
     * \brief Runs the server
     *
     * This function gets called in the main, and handles everything that might 
     * happens.
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
     * \param[in] client The client that send the packet
     */
    void handleInput(sf::Packet & p, sharedSocketPtr_t & client);

};

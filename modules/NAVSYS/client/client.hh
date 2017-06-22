/**
 * \file      client.hh
 * \brief     Header for client side connection code for NAVSYS API
 * \author    Philippe Zwietering, Arco Gelderblom, Tim IJntema
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See ../../LICENSE
 */

#pragma once

#include <SFML/Network.hpp>
#include "../common/graph.hh"
#include "../common/protocol.hh"

enum class button {ShutDown,StartNode,EndNode};

/**
 * \brief Client class
 *
 * This class contains (almost) all of the functionalities a navigation system
 * should ever want to have. It makes a connection with a server object via TCP
 * and handles user input.
 */
class Client {
private:
    sf::IpAddress ipAddress;
    uint16_t port;
    sf::TcpSocket socket;
    const sf::Vector2f buttonSize = {100, 30};
    Graph g;

    /**
     * \brief Sends a sf::Packet with error checking.
     *
     * \param[in] p The packet to be send.
     */
    void sendPacket(sf::Packet & p);

    /**
     * \brief Receives a packet and checks if it has been received correctly.
     *
     * \param[in] p The packet to put the received data in.
     */
    void receivePacket(sf::Packet & p);
public:

    /**
     * \brief Client constructor with an ip and a port to connect to
     *
     * \param[in] ipAddress sf::IpAddress, the IP address of the server
     * \param[in] port uint16_t, the port of the server
     */
    Client(sf::IpAddress ipAddress, uint16_t port);

    /**
     * \brief Runs the client
     */
    void run();

    /**
     * \brief Requests the graph from the server
     *
     * This function sends the requests for the data contained in the node and
     * vertices file.
     */
    void getGraphFromServer();

    /**
     * \brief Requests a path from the server
     *
     * This function sends the requests for the path between two nodes.
     *
     * \param[in] nodes The start and end nodes to send to the server.
     */
    void requestPath(const StartEndNodeData &nodes);

    /**
     * \brief Request data from the database using a command.
     *
     * \param[in] cmd The command to send.
     */
    void requestGraphUsingCommand(const command &cmd);
};

/**
 * \file      client.hh
 * \brief     Header for client side connection code for NAVSYS API
 * \author    Philippe Zwietering, Arco Gelderblom
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
 * This class should contain all the functionality a navigation system should 
 * ever want to have. It makes a connection with a server object via TCP and 
 * handles user input
 */
class Client {
private:
	sf::IpAddress ipAddress;
	uint16_t port;
	sf::TcpSocket socket;
    sf::Vector2f buttonSize = {100,30};
    Graph g;

    /**
     * \brief Send a sf packet with error checking
     * 
     * \param[in] p The packet to be send
     */
    void sendPacket(sf::Packet & p);
    
    /**
     * \brief Receive a packet and check if it has been received correctly
     * 
     * \param[in] p The packet to put the received data in
     */
    void checkPacketCorrectlyReceived(sf::Packet & p);
public:

    /**
     * \brief Client constructor
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
     * \brief Requests the database from the server
     *
     * This function sends the requests for the data contained in the node and 
     * vertices file.
     */
    void getDatabaseFromServer();

    /**
     * \brief Requests the path from the server
     *
     * This function sends the requests for  the path between two nodes.
     */
    void requestPath(StartEndNodeData nodes);
    
    /**
     * \brief Request data from the database using a command
     *
     * \param[in] cmd The command to send 
     */
    void requestDatabaseUsingCommand(const command & cmd);
};

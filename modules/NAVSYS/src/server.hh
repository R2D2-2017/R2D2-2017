/**
 * \file
 * \brief     Header for server side code for NAVSYS API
 * \author    Philippe Zwietering
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See ../../LICENSE
 */

#ifndef SERVER
#define SERVER

#include <sfml/Network.hpp>
#include <vector>
#include <memory>
#include <string>

class Server{
private:
    uint16_t port;
    sf::TcpListener socketListener;
    std::vector<std::shared_ptr<sf::TcpSocket>> connectedClientSockets;
    sf::SocketSelector socketSelector;

public:
    Server(const uint16_t port);
    void broadcastMessage(const std::string & message);
    void run();
    void killEveryLittleThingIsGonnaBeAlright();
    void handleInput();
};

#endif //SERVER
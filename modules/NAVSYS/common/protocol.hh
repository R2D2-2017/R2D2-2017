#pragma once

#include <type_traits>
#include <SFML/Network.hpp>

enum class command {
    none,//due to initialization warning
    requestNodes,
    responseNodes,
    
    requestVertices,
    responseVertices,
    
    requestPath,
    responsePath
};

sf::Packet & operator>>(sf::Packet & lhs, command & c);
sf::Packet & operator<<(sf::Packet & lhs, const command & c);

struct StartEndNodeData {
    std::string startNode = "";
    std::string endNode = "";
    
    friend sf::Packet & operator>>(sf::Packet & lhs, StartEndNodeData & nodes);
    friend sf::Packet & operator<<(sf::Packet & lhs, const StartEndNodeData & nodes);
};


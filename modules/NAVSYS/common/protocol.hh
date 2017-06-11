#pragma once

#include <type_traits>
#include <SFML/Network.hpp>

enum class command {
    none,//due to initialization warning
    requestNodes,
    requestVertices,
    requestPath,
    responsePath
};

sf::Packet & operator>>(sf::Packet & lhs, command c);

sf::Packet & operator<<(sf::Packet & lhs, const command & c);

struct path {
    std::string startNode = "";
    std::string endNode = "";
    
    friend sf::Packet & operator>>(sf::Packet & lhs, path nodes);
    friend sf::Packet & operator<<(sf::Packet & lhs, const path & nodes);
};


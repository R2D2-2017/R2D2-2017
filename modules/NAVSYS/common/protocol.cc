#include "protocol.hh"

sf::Packet & operator>>(sf::Packet & lhs, command & c) {
    int i = 0;
    lhs >> i;
    c = static_cast<command>(i);
    return lhs;
}

sf::Packet & operator<<(sf::Packet & lhs, const command & c) {
    lhs << static_cast<int>(c);
    return lhs;
}

sf::Packet & operator>>(sf::Packet & lhs, StartEndNodeData & nodes) {
    lhs >> nodes.startNode >> nodes.endNode;
    return lhs;
}

sf::Packet & operator<<(sf::Packet & lhs, const StartEndNodeData & nodes) {
    lhs << nodes.startNode << nodes.endNode;
    return lhs;
}
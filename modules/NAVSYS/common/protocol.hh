/**
 * \file      protocol.hh
 * \brief     This file contains the command enum and start en end note structur
 * \author    Tim IJntema
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See LICENSE
 */

#pragma once

#include <SFML/Network.hpp>

/**
 * \brief Commands available to the client and server
 */
enum class command {
    none,/** \brief Command::none exists due to an initialization warning from the compiler */
    requestNodes,/** \brief Request nodes vector from the server */
    responseNodes,/** \brief Response from the server paired with a nodes vector */
    
    requestVertices,/** \brief Request vertice vector from the server */
    responseVertices,/** \brief Response from the server paired with a vertice vector */
    
    requestPath,/** \brief Request a path from a startnode to an end node from the server */
    responsePath/** \brief Response from server paired with a vector with PathNode type containing the path from start to end */
};

/**
 * \brief Operator>> to get a command type from a sf::Packet
 * 
 * \param [in] lhs The sf::packet containing the command
 * \param [out] c The command retreived from the packet
 * 
 * \return The packet with the command substracted from it
 */
sf::Packet & operator>>(sf::Packet & lhs, command & c);

/**
 * \brief Operator<< to put a command type into a sf::Packet
 * 
 * \param [in] lhs The sf::packet without the command
 * \param [in] c The data to be put into the packet
 * 
 * \return The packet with the data added to it
 */
sf::Packet & operator<<(sf::Packet & lhs, const command & c);

/**
 * \brief Struct containing a start and end node as a string
 */
struct StartEndNodeData {
    std::string startNode = "";
    std::string endNode = "";
    
    /**
     * \brief Operator>> to put a StartEndNodeData type into a sf::Packet
     * 
     * \param [in] lhs The sf::packet containing the data
     * \param [out] nodes The data retreived from the packet
     * 
     * \return The packet with the data substracted from it
     */
    friend sf::Packet & operator>>(sf::Packet & lhs, StartEndNodeData & nodes);
    
    /**
     * \brief Operator<< to put a StartEndNodeData type into a sf::Packet
     * 
     * \param [in] lhs The sf::packet without the data
     * \param [in] nodes The data to be put into the packet
     * 
     * \return The packet with the data added to it
     */
    friend sf::Packet & operator<<(sf::Packet & lhs, const StartEndNodeData & nodes);
};


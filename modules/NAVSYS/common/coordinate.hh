/**
 * \file      coordinate.hh
 * \brief     This file contains the coordinate class definition
 * \author    Robert Bezem
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See LICENSE
 */
#pragma once
#include <ostream>
#include <SFML/Network.hpp>

/**
 * \brief 2D Coordinate class
 * 
 * \details
 * Coordinate class for coordinates on a 2d plane.
 */
class Coordinate {
public:
    /**
     * \brief Instantiate a Coordinate
     * 
     * \param[in] x X position
     * \param[in] y Y position
     */
    Coordinate(float x, float y);

    /**
     * \brief X position of Coordinate
     */
    float x;
    
    /**
     * \brief Y position of Coordinate
     */
    float y;

    /**
     * \brief Compare coordinates with operator==
     *
     * \param[in] rhs The coordinate to compare
     */
    bool operator==(const Coordinate &rhs) const;

    /**
     * \brief Compare coordinates with operator!=
     *
     * \param[in] rhs The coordinate to compare
     */
    bool operator!=(const Coordinate &rhs) const;

    /**
     * \brief Add and assign with operator+=
     *
     * \param[in] rhs The coordinate to add
     */
    Coordinate &operator+=(const Coordinate &rhs);

    /**
     * \brief Add two coordinates with operator+
     *
     * \param[in] lhs The fist coordinate the other is added to
     * \param[in] rhs The coordinate to add to the first coordinate
     */
    friend Coordinate operator+(Coordinate lhs, const Coordinate &rhs);

    /**
     * \brief Substract and assign with operator-=
     *
     * \param[in] rhs The coordinate to substract
     */
    Coordinate &operator-=(const Coordinate &rhs);

    /**
     * \brief Add two coordinates with operator-
     *
     * \param[in] lhs The fist coordinate the other is substracted from
     * \param[in] rhs The coordinate to substract from the first coordinate
     */
    friend Coordinate operator-(Coordinate lhs, const Coordinate &rhs);

    /**
     * \brief Print out a coordinate with operator<<
     *
     * \param[out] os The output stream the coordinate is put in to
     * \param[in] coordinate The coordinate to put into the output stream
     */
    friend std::ostream &operator<<(std::ostream &os, const Coordinate &coordinate);

    /**
     * \brief Get the euclidean distance between Coordinates
     * 
     * \details
     * Returns the euclidean distance calculated with the following function:
     * \f$(x_1,y_1)\f$ and \f$(x_2,y_2)\f$
     * 
     * \param[in] rhs Other coordinate
     * 
     * \return Distance between Coordinates
     */
    float euclideanDistance(const Coordinate &rhs) const;
    
    /**
     * \brief Put a coordinate in a network packet
     *
     * \param[in] lhs The packet to put the coordinate in
     * \param[in] coordinate The coordinate to add to the packet
     */
    friend sf::Packet & operator<<(sf::Packet & lhs, const Coordinate & coordinate);
    
    /**
     * \brief Pull a coordinate from a network packet
     *
     * \param[in] lhs The packet pull the coordinate from
     * \param[in] coordinate The coordinate pull from the packet
     */
    friend sf::Packet & operator>>(sf::Packet & lhs, Coordinate & coordinate);
};

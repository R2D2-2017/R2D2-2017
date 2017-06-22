/**
 * \file      coordinate.hh
 * \brief     This file contains the coordinate class definition.
 * \author    Robert Bezem
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See LICENSE
 */

#pragma once
#include <ostream>
#include <SFML/Network.hpp>

/**
 * \brief 2D Coordinate class.
 *
 * \details Coordinate class for coordinates on a 2d plane.
 */
class Coordinate {
public:
    /**
     * \brief Instantiate a Coordinate.
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
     * \brief Gets the euclidean distance between Coordinates
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
    * Operators for sending and receiving a sf::Packet containing a coordinate.
    */
    friend sf::Packet & operator<<(sf::Packet & lhs,
                                   const Coordinate & coordinate);

    friend sf::Packet & operator>>(sf::Packet & lhs, Coordinate & coordinate);

    /**
    * Operators
    */
    bool operator==(const Coordinate &rhs) const;

    bool operator!=(const Coordinate &rhs) const;

    Coordinate &operator+=(const Coordinate &rhs);

    friend Coordinate operator+(Coordinate lhs, const Coordinate &rhs);

    Coordinate &operator-=(const Coordinate &rhs);

    friend Coordinate operator-(Coordinate lhs, const Coordinate &rhs);

    friend std::ostream & operator<<(std::ostream &os,
                                    const Coordinate &coordinate);
};

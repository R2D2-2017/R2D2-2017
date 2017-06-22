/**
 * \file      coordinate.cc
 * \author    Robert Bezem
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See LICENSE
 */

#include "coordinate.hh"
#include <math.h>

Coordinate::Coordinate(float x, float y):
    x(x),
    y(y)
{}

bool Coordinate::operator==(const Coordinate &rhs) const {
    return x == rhs.x && y == rhs.y;
}

bool Coordinate::operator!=(const Coordinate &rhs) const {
    return !(rhs == *this);
}

std::ostream &operator<<(std::ostream &os, const Coordinate &coordinate) {
    os << "[" << coordinate.x << "," << coordinate.y << "]";
    return os;
}

Coordinate &Coordinate::operator+=(const Coordinate &rhs) {
    x += rhs.x;
    y += rhs.y;
    return *this;
}

Coordinate operator+(Coordinate lhs, const Coordinate &rhs) {
    lhs += rhs;
    return lhs;
}

Coordinate &Coordinate::operator-=(const Coordinate &rhs) {
    x -= rhs.x;
    y -= rhs.y;
    return *this;
}

Coordinate operator-(Coordinate lhs, const Coordinate &rhs) {
    lhs -= rhs;
    return lhs;
}

float Coordinate::euclideanDistance(const Coordinate &rhs) const {
    return static_cast<float> (sqrt(pow(x - rhs.x, 2) + pow(y - rhs.y, 2)));
}

sf::Packet &operator<<(sf::Packet & lhs, const Coordinate &coordinate) {
    lhs << coordinate.x << coordinate.y;
    return lhs;
}

sf::Packet &operator>>(sf::Packet &lhs, Coordinate &coordinate) {
    lhs >> coordinate.x >> coordinate.y;
    return lhs;
}

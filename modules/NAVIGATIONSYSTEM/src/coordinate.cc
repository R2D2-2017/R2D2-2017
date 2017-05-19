//
// Created by Robert on 5/19/17.
//
#include <math.h>
#include "coordinate.hh"

Coordinate::Coordinate(float x, float y)
    : x(x), y(y) {}

bool Coordinate::operator==(const Coordinate &rhs) const {
    return x == rhs.x &&
        y == rhs.y;
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
    return (float) sqrt(pow(x + rhs.x, 2) + pow(y + rhs.y, 2));
}




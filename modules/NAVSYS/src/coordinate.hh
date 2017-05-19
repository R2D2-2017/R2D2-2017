//
// Created by Robert on 5/19/17.
//

#ifndef NAVIGATIONSYSTEM_COORDINATE_HH
#define NAVIGATIONSYSTEM_COORDINATE_HH

#include <ostream>

class Coordinate {
public:
  Coordinate(float x, float y);

  float x;
  float y;

  bool operator==(const Coordinate &rhs) const;

  bool operator!=(const Coordinate &rhs) const;

  Coordinate &operator+=(const Coordinate &rhs);

  friend Coordinate operator+(Coordinate lhs, const Coordinate &rhs);

  Coordinate &operator-=(const Coordinate &rhs);

  friend Coordinate operator-(Coordinate lhs, const Coordinate &rhs);

  friend std::ostream &operator<<(std::ostream &os, const Coordinate &coordinate);

  float euclideanDistance(const Coordinate &rhs) const;

};

#endif //NAVIGATIONSYSTEM_COORDINATE_HH

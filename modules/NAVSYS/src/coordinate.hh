//
// Created by Robert on 5/19/17.
//

#ifndef NAVIGATIONSYSTEM_COORDINATE_HH
#define NAVIGATIONSYSTEM_COORDINATE_HH

#include <ostream>
/**
 * \brief 2D Coordinate class
 * \details
 * Coordinate class for coordinates on a 2d plane.
 */
class Coordinate {
public:
  /**
   * Instantiate a Coordinate
   * \param x X position
   * \param y Y position
   */
  Coordinate(float x, float y);

  /**
   * X position of Coordinate
   */
  float x;
  /**
   * Y position of Coordinate
   */
  float y;

  bool operator==(const Coordinate &rhs) const;

  bool operator!=(const Coordinate &rhs) const;

  Coordinate &operator+=(const Coordinate &rhs);

  friend Coordinate operator+(Coordinate lhs, const Coordinate &rhs);

  Coordinate &operator-=(const Coordinate &rhs);

  friend Coordinate operator-(Coordinate lhs, const Coordinate &rhs);

  friend std::ostream &operator<<(std::ostream &os, const Coordinate &coordinate);

  /**
   * \brief Get the euclidean distance between Coordinates
   * \details
   * Returns the euclidean distance calculated with the following function:
   * \f$(x_1,y_1)\f$ and \f$(x_2,y_2)\f$
   * \param rhs Other coordinate
   * \return Distance between Coordinates
   */
  float euclideanDistance(const Coordinate &rhs) const;

};

#endif //NAVIGATIONSYSTEM_COORDINATE_HH

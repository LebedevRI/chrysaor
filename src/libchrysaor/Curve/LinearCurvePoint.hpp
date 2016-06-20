/*
 *    This file is part of chrysaor.
 *    copyright (c) 2016 Roman Lebedev.
 *
 *    chrysaor is free software: you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation, either version 3 of the License, or
 *    (at your option) any later version.
 *
 *    chrysaor is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with chrysaor.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include "Curve/AbstractCurvePoint.hpp"
#include <iostream> // for operator<<, basic_ostream, basic...

class LinearCurvePoint : public AbstractCurvePoint {
private:
  /**
  * @brief point value
  */
  double y_;

public:
  explicit operator double() const;

  using AbstractCurvePoint::interpolate;

  /**
  * @brief linearly interpolates between 2 datapoints
  *
  * @param a left datapoint (x0, y0)
  * @param b right datapoint (x1, y1), x1 > x0
  * @param x x coordinate, in the interval (x0, x1)
  *
  * \f$\frac{y - y_0}{x - x_0} = \frac{y_1 - y_0}{x_1 - x_0}\f$
  *
  * Solving this equation for y, which is the unknown value at x, gives
  *
  * \f$y = y_0 + (y_1-y_0)\frac{x - x_0}{x_1-x_0}\f$
  *
  * @see https://en.wikipedia.org/wiki/Linear_interpolation
  *
  * @return double y
  */
  static double interpolate(const LinearCurvePoint &a,
                            const LinearCurvePoint &b, double x);
  double interpolate(const LinearCurvePoint &b, double x) const;

  friend std::ostream &operator<<(std::ostream &os,
                                  const LinearCurvePoint &obj);

  LinearCurvePoint(double x, double y);
};

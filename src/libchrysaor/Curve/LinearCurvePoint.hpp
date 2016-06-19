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
  static double interpolate(const LinearCurvePoint &a,
                            const LinearCurvePoint &b, double x);
  double interpolate(const LinearCurvePoint &b, double x) const;

  friend std::ostream &operator<<(std::ostream &os,
                                  const LinearCurvePoint &obj);

  LinearCurvePoint(double x, double y);
};

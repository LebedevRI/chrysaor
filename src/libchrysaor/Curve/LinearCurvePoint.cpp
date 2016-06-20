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

#include "Curve/LinearCurvePoint.hpp"
#include "Curve/AbstractCurvePoint.hpp" // for AbstractCurvePoint
#include <cassert>                      // for assert
#include <cmath>                        // for isfinite
#include <iostream>                     // for operator<<, ostream, basic_o...

// converter returns the y-coordinate of current point
LinearCurvePoint::operator double() const { return (y_); }

AbstractCurvePoint::operator LinearCurvePoint() {
  return LinearCurvePoint(x_,
                          0.0 /* unused. FIXME: this must be the wrong way */);
}

double LinearCurvePoint::interpolate(const LinearCurvePoint &a,
                                     const LinearCurvePoint &b, double x) {
  assert(std::isfinite(x));
  assert(std::isfinite(a.x_));
  assert(std::isfinite(a.y_));
  assert(std::isfinite(b.x_));
  assert(std::isfinite(b.y_));

  assert(a != b);
  assert(a < b);

  assert(x <= b.x_);
  assert(a.x_ <= x);

  assert((b.x_ - a.x_) != 0.0);

  const double t = ((x - a.x_) / (b.x_ - a.x_));
  assert(std::isfinite(t));

  assert(t <= 1.0);
  assert(0.0 <= t);

  const double y = ((1.0 - t) * a.y_ + t * b.y_);
  assert(y <= b.y_);
  assert(a.y_ <= y);

  return y;
}

double LinearCurvePoint::interpolate(const LinearCurvePoint &b,
                                     double x) const {
  return interpolate(*this, b, x);
}

std::ostream &operator<<(std::ostream &os, const LinearCurvePoint &obj) {
  return os << "x: " << obj.x_ << "; y: " << obj.y_;
}

LinearCurvePoint::LinearCurvePoint(double x, double y)
    : AbstractCurvePoint(x), y_(y) {}

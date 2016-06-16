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

#include "CubicCurvePoint.hpp"

double CubicCurvePoint::operator()() const { return (x_); }
double CubicCurvePoint::operator*() const { return (x_); }

// converter returns the y-coordinate of current point
CubicCurvePoint::operator double() const { return (y_); }

//
// void operator=(const CubicCurvePoint & b) { x = b.x; y = b.y;
// outTangent = b.outTangent; inTangent = b.inTangent; }

// all comparison is key-based.

bool CubicCurvePoint::operator==(const CubicCurvePoint &b) const {
  return (x_ == b.x_);
}
bool CubicCurvePoint::operator<(const CubicCurvePoint &b) const {
  return (x_ < b.x_);
}

bool CubicCurvePoint::operator!=(const CubicCurvePoint &b) const {
  return !(operator==(b));
}
bool CubicCurvePoint::operator>(const CubicCurvePoint &b) const {
  return !(operator<(b));
}

bool CubicCurvePoint::operator<=(const CubicCurvePoint &b) const {
  return !(operator>(b));
}
bool CubicCurvePoint::operator>=(const CubicCurvePoint &b) const {
  return !(operator<(b));
}

CubicCurvePoint::CubicCurvePoint(double x, double y, double outTangent,
                                 double inTangent)
    : x_(x), y_(y), outTangent_(outTangent), inTangent_(inTangent) {}

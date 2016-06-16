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

#include "CubicCurve.hpp"
#include "CubicCurvePoint.hpp" // for CubicCurvePoint
#include <cassert>             // for assert
#include <cstddef>             // for size_t
#include <initializer_list>    // for initializer_list
#include <iterator>            // for reverse_iterator
#include <set>                 // for set, _Rb_tree_const_iterator

double CubicCurve::operator[](const double x) const {
  assert(!curve_.empty());

  const CubicCurvePoint xpt(x, -1.0, -1.0, -1.0);

  if (xpt <= *curve_.begin())
    return *curve_.begin();
  else if (xpt >= *curve_.rbegin())
    return *curve_.rbegin();
  else {
    // will hold closest points, so that [min-k min p map map+n]
    CubicCurvePoint min = *curve_.begin();
    CubicCurvePoint max = *curve_.begin();

    for (const auto &point : curve_) {
      if (xpt == point)
        return point;

      min = max;
      max = point;

      // found
      if (min < xpt && xpt < max)
        break;
    }

    // FIXME: actually evaluate the Unity-like expression!
    return (static_cast<double>(min) + static_cast<double>(max)) / 2.0;
  }
}

std::size_t CubicCurve::size() const { return curve_.size(); }

CubicCurve::CubicCurve() : curve_() {}

CubicCurve::CubicCurve(std::initializer_list<CubicCurvePoint> __l)
    : curve_(__l) {}

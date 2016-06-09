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

#include "src/CubicCurvePoint.hpp" // for CubicCurvePoint
#include <cassert>                 // for assert
#include <cstddef>                 // for size_t
#include <initializer_list>        // for initializer_list
#include <iterator>                // for reverse_iterator
#include <set>                     // for set, _Rb_tree_const_iterator
#include <vector>                  // for vector

/*
 * @brief mimics Unity's AnimationCurve
 * http://answers.unity3d.com/answers/1136791/view.html
 *
 * Unity define a curve with 2 keyframes, each composed of
 * a point and a tangent. I guess the simplest curve matching that
 * is a third degree polynomial (a cubic function).
 * Given the 2 points and tangents, it is possible to compute
 * the polynomial coefficients simply by solving the following equation system:
 * (1) a*p1x^3 + b*p1x^2 + c*p1x + d = p1y
 * (2) a*p2x^3 + b*p2x^2 + c*p2x + d = p2y
 * (3) 3*a*p1x^2 + 2*b*p1x + c = tp1
 * (4) 3*a*p2x^2 + 2*b*p2x + c = tp2
 */
class CubicCurve {
private:
  /**
  * @brief the curve
  */
  std::set<CubicCurvePoint> curve_;

public:
  double operator[](const double x) const {
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

  std::size_t size() const { return curve_.size(); }

  CubicCurve() : curve_() {}

  CubicCurve(std::initializer_list<CubicCurvePoint> __l) : curve_(__l) {}

  template <typename _InputIterator>
  CubicCurve(_InputIterator __first, _InputIterator __last)
      : curve_(__first, __last) {}
};
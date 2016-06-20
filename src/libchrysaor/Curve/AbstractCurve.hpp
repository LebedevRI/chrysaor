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
#include <cassert>          // for assert
#include <cstddef>          // for size_t
#include <initializer_list> // for initializer_list
#include <set>              // for set

template <typename PointType> class AbstractCurve {
private:
  /**
  * @brief the curve
  */
  std::set<PointType> curve_;

public:
  double operator[](const double x) const {
    assert(!curve_.empty());

    AbstractCurvePoint xpt(x);

    if (xpt <= *curve_.begin())
      return static_cast<double>(*curve_.begin());
    else if (xpt >= *curve_.rbegin())
      return static_cast<double>(*curve_.rbegin());
    else {
      auto it_max = curve_.upper_bound(xpt);

      assert(!((*it_max) <= xpt));
      assert(xpt != (*it_max));
      assert(xpt < (*it_max));

      auto it_min = std::prev(it_max, 1);

      assert(!((*it_min) > xpt));
      assert((*it_min) <= xpt);

      assert((*it_min) < (*it_max));
      assert((*it_min) != (*it_max));

      if (xpt == (*it_min))
        return static_cast<double>(*it_min);

      return (*it_min).interpolate(*it_max, x);
    }
  }

  std::size_t size() const { return curve_.size(); }

  AbstractCurve() : curve_() {}

  AbstractCurve(std::initializer_list<PointType> __l) : curve_(__l) {}

  template <typename _InputIterator>
  AbstractCurve(_InputIterator __first, _InputIterator __last)
      : curve_(__first, __last) {}
};

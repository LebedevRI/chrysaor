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
    else if (curve_.find(xpt) != curve_.end())
      return static_cast<double>(*curve_.find(xpt));
    else {
      auto it_max = curve_.upper_bound(xpt);
      auto it_min = std::prev(it_max, 1);

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

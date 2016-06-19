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

#include "Curve/LinearCurvePoint.hpp"   // for LinearCurvePoint
#include "Curve/AbstractCurvePoint.hpp" // for AbstractCurvePoint
#include <algorithm>                    // for next_permutation, sort
#include <gtest/gtest.h>                // for AssertHelper, ASSERT_EQ, TEST
#include <limits>                       // for numeric_limits

TEST(LinearCurvePoint, TestConstructor) {
  const double x = 0.0;
  const double y = 1.0;

  ASSERT_NO_THROW({ LinearCurvePoint foo(x, y); });
}

/**
 * @brief this will test the comparison of points.
 *
 * the points are compared by their x-coordinate only.
 */
TEST(LinearCurvePoint, TestComparisonOperators) {
  const double NaN = std::numeric_limits<double>::signaling_NaN();
  LinearCurvePoint foo(0.0, NaN);
  LinearCurvePoint bar(1.0, NaN);

  ASSERT_EQ(foo, foo);
  ASSERT_EQ(bar, bar);

  ASSERT_NE(foo, bar);

  ASSERT_LT(foo, bar);

  ASSERT_GT(bar, foo);

  ASSERT_LE(foo, foo);
  ASSERT_LE(foo, bar);
  ASSERT_LE(bar, bar);

  ASSERT_GE(foo, foo);
  ASSERT_GE(bar, foo);
  ASSERT_GE(bar, bar);
}

TEST(LinearCurvePoint, TestComparisonWithAbstract) {
  const double NaN = std::numeric_limits<double>::signaling_NaN();
  LinearCurvePoint foo(0.0, NaN);
  AbstractCurvePoint bar(1.0);
  LinearCurvePoint baz(2.0, NaN);

  ASSERT_EQ(foo, foo);
  ASSERT_EQ(bar, bar);
  ASSERT_EQ(baz, baz);

  ASSERT_NE(foo, bar);
  ASSERT_NE(foo, baz);
  ASSERT_NE(bar, baz);

  ASSERT_LT(foo, bar);
  ASSERT_LT(foo, baz);
  ASSERT_LT(bar, baz);

  ASSERT_GT(bar, foo);
  ASSERT_GT(baz, foo);
  ASSERT_GT(baz, bar);

  ASSERT_LE(foo, foo);
  ASSERT_LE(foo, bar);
  ASSERT_LE(foo, baz);
  ASSERT_LE(bar, bar);
  ASSERT_LE(bar, baz);
  ASSERT_LE(baz, baz);

  ASSERT_GE(foo, foo);
  ASSERT_GE(bar, foo);
  ASSERT_GE(baz, foo);
  ASSERT_GE(bar, bar);
  ASSERT_GE(baz, bar);
  ASSERT_GE(baz, baz);
}

/**
 * @brief tests all the ways to get the point y coordinate
 */
TEST(LinearCurvePoint, TestConversionOperator) {
  const double NaN = std::numeric_limits<double>::signaling_NaN();

  const double y = 3.54;

  LinearCurvePoint foo(NaN, y);

  ASSERT_EQ(y, static_cast<double>(foo));
}

TEST(LinearCurvePoint, TestInterpolation) {
  const double NaN = std::numeric_limits<double>::signaling_NaN();

  const double x0 = 0.0;
  const double y0 = 1.0;
  const double x1 = 2.0;
  const double y1 = 4.0;

  LinearCurvePoint p1(x0, y0);
  LinearCurvePoint p2(x1, y1);

  ASSERT_EQ((y0 + y1) / 2.0, p1.interpolate(p2, NaN));
  ASSERT_EQ((y0 + y1) / 2.0, p2.interpolate(p1, NaN));
  ASSERT_EQ((y0 + y1) / 2.0, LinearCurvePoint::interpolate(p1, p2, NaN));
  ASSERT_EQ((y0 + y1) / 2.0, LinearCurvePoint::interpolate(p2, p1, NaN));
  ASSERT_EQ(p1.interpolate(p2, NaN),
            LinearCurvePoint::interpolate(p1, p2, NaN));
  ASSERT_EQ(p1.interpolate(p2, NaN),
            LinearCurvePoint::interpolate(p2, p1, NaN));
  ASSERT_EQ(p2.interpolate(p1, NaN),
            LinearCurvePoint::interpolate(p1, p2, NaN));
  ASSERT_EQ(p2.interpolate(p1, NaN),
            LinearCurvePoint::interpolate(p2, p1, NaN));
}

TEST(LinearCurvePoint, TestOnlyXMatters) {
  double vals[] = {-1.0, 1.0};

  std::sort(vals, vals + 2);

  do {
    ASSERT_EQ(LinearCurvePoint(0.0, vals[0]), LinearCurvePoint(0.0, vals[1]));
  } while (std::next_permutation(vals, vals + 2));
}

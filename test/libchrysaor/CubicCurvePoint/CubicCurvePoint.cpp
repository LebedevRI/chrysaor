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

#include "CubicCurvePoint.hpp" // for CubicCurvePoint
#include <algorithm>           // for next_permutation, sort
#include <gtest/gtest.h>       // for AssertHelper, ASSERT_EQ, TEST
#include <limits>              // for numeric_limits

TEST(CubicCurvePointTest, TestConstructor) {
  const double x = 0.0;
  const double y = 1.0;

  const double outTangent = 1.0;
  const double inTangent = 1.0;

  ASSERT_NO_THROW({ CubicCurvePoint foo(x, y, outTangent, inTangent); });
}

/**
 * @brief this will test the comparison of points.
 *
 * the points are compared by their x-coordinate only.
 */
TEST(CubicCurvePointTest, TestComparisonOperators) {
  const double NaN = std::numeric_limits<double>::signaling_NaN();
  CubicCurvePoint foo(0.0, NaN, NaN, NaN);
  CubicCurvePoint bar(1.0, NaN, NaN, NaN);

  ASSERT_NE(foo, bar);

  ASSERT_EQ(foo, foo);
  ASSERT_EQ(bar, bar);

  ASSERT_LT(foo, bar);
  ASSERT_GT(bar, foo);

  ASSERT_LE(foo, bar);
  ASSERT_GE(bar, foo);
}

/**
 * @brief tests all the ways to get the point y coordinate
 */
TEST(CubicCurvePointTest, TestConversionOperator) {
  const double NaN = std::numeric_limits<double>::signaling_NaN();

  const double y = 3.54;

  CubicCurvePoint foo(NaN, y, NaN, NaN);
  CubicCurvePoint bar(NaN, y, NaN, NaN);

  ASSERT_EQ(y, foo);
  ASSERT_EQ(y, static_cast<double>(foo));

  ASSERT_EQ(y, bar);
  ASSERT_EQ(y, static_cast<double>(bar));
}

/**
 * @brief tests all the ways to get the point x coordinate
 */
TEST(CubicCurvePointTest, TestGetterOperators) {
  const double NaN = std::numeric_limits<double>::signaling_NaN();

  const double x = 3.54;

  CubicCurvePoint foo(x, NaN, NaN, NaN);
  CubicCurvePoint bar(x, NaN, NaN, NaN);

  ASSERT_EQ(foo(), foo());
  ASSERT_EQ(foo(), *foo);
  ASSERT_EQ(foo(), x);

  ASSERT_EQ(bar(), bar());
  ASSERT_EQ(bar(), *bar);
  ASSERT_EQ(bar(), x);

  ASSERT_EQ(foo(), bar());
  ASSERT_EQ(foo(), *bar);
}

TEST(CubicCurvePointTest, TestOnlyXMatters) {
  double vals[] = {-1.0, -1.0, -1.0, 1.0, 1.0, 1.0};

  std::sort(vals, vals + 6);

  do {
    ASSERT_EQ(CubicCurvePoint(0.0, vals[0], vals[1], vals[2]),
              CubicCurvePoint(0.0, vals[3], vals[4], vals[5]));
  } while (std::next_permutation(vals, vals + 6));
}

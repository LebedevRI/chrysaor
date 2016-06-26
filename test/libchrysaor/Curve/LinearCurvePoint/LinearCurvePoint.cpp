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
#include "Curve/AbstractCurvePoint.hpp" // for AbstractCurvePoint, operator<<
#include <algorithm>                    // for next_permutation, sort
#include <array>                        // for array
#include <gtest/gtest.h>                // for Message, TestPartResult, Tes...
#include <iterator>                     // for reverse_iterator
#include <limits>                       // for numeric_limits
#include <map>                          // for map, _Rb_tree_iterator, map<...
#include <string>                       // for basic_string, string
#include <utility>                      // for pair

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
  std::map<double, double> testPts;
  testPts[0.0] = 4.0;
  testPts[0.5] = 5.0;
  testPts[1.0] = 6.0;
  testPts[1.5] = 7.0;
  testPts[2.0] = 8.0;

  LinearCurvePoint p1(testPts.begin()->first, testPts.begin()->second);
  LinearCurvePoint p2(testPts.rbegin()->first, testPts.rbegin()->second);

  for (auto &testPt : testPts) {
    const double x = testPt.first;
    const double y = testPt.second;

    ASSERT_DOUBLE_EQ(y, p1.interpolate(p2, x));
    ASSERT_DOUBLE_EQ(y, LinearCurvePoint::interpolate(p1, p2, x));
    ASSERT_DOUBLE_EQ(p1.interpolate(p2, x),
                     LinearCurvePoint::interpolate(p1, p2, x));
  }
}

TEST(LinearCurvePoint, TestOnlyXMatters) {
  std::array<double, 2> vals{{-1.0, 1.0}};

  std::sort(vals.begin(), vals.end());

  do {
    ASSERT_EQ(LinearCurvePoint(0.0, vals[0]), LinearCurvePoint(0.0, vals[1]));
  } while (std::next_permutation(vals.begin(), vals.end()));
}

TEST(Vec3Test, TestPrint) {
  LinearCurvePoint foo(2.71, 7.381);

  std::ostringstream output;
  output << foo;

  std::string foo_str("x: 2.71; y: 7.381");

  ASSERT_EQ(foo_str, output.str());
}

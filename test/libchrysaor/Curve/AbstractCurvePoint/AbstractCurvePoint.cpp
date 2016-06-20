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

#include "Curve/AbstractCurvePoint.hpp"
#include <gtest/gtest.h> // for ASSERT_EQ, ASSERT_GE, ASSERT_LE, TEST, ASSE...
#include <string>        // for string

TEST(AbstractCurvePointTest, TestConstructor) {
  const double x = 0.0;

  ASSERT_NO_THROW({ AbstractCurvePoint foo(x); });
}

/**
 * @brief this will test the comparison of points.
 *
 * the points are compared by their x-coordinate only.
 */
TEST(AbstractCurvePointTest, TestComparisonOperators) {
  AbstractCurvePoint foo(0.0);
  AbstractCurvePoint bar(1.0);

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

TEST(Vec3Test, TestPrint) {
  AbstractCurvePoint foo(3.14);

  std::ostringstream output;
  output << foo;

  std::string foo_str("x: 3.14");

  ASSERT_EQ(foo_str, output.str());
}

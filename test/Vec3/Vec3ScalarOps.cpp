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

#include "src/Vec3.hpp" // for Vec3
#include "gtest/gtest.h"            // for ASSERT_EQ, AssertHelper, TestWit...
#include <gtest/gtest-param-test.h> // for ParamIteratorInterface, ParamGen...
#include <iostream>                 // for operator<<, basic_ostream, basic...

struct Vec3ScalarData {
  double vec[3];
  double s;
  double res[3];
  friend std::ostream &operator<<(std::ostream &os, const Vec3ScalarData &obj) {
    return os << "vector: (" << obj.vec[0] << "; " << obj.vec[1] << "; "
              << obj.vec[2] << "), scalar = " << obj.s << ", result: ("
              << obj.res[0] << "; " << obj.res[1] << "; " << obj.res[2] << ")";
  }
};

class Vec3PlusScalarTest : public ::testing::TestWithParam<Vec3ScalarData> {};

TEST_P(Vec3PlusScalarTest, Plus) {
  auto as = GetParam();

  Vec3 foo(as.vec);
  const Vec3 res(as.res);

  foo += as.s;
  Vec3 baz(Vec3(as.vec) + as.s);

  ASSERT_EQ(res, foo);
  ASSERT_EQ(res, baz);
  ASSERT_EQ(foo, baz);
}

INSTANTIATE_TEST_CASE_P(
    Default, Vec3PlusScalarTest,
    // FIXME: this is ugly.
    testing::Values(Vec3ScalarData{{0.0, 0.0, 0.0}, 0.0, {0.0, 0.0, 0.0}},
                    Vec3ScalarData{{1.0, 2.0, 3.0}, 4.0, {5.0, 6.0, 7.0}},
                    Vec3ScalarData{
                        {-9.0, 4.42, 3.0}, -1.1, {-10.1, 3.32, 1.9}}));

class Vec3MinusScalarTest : public ::testing::TestWithParam<Vec3ScalarData> {};

TEST_P(Vec3MinusScalarTest, Minus) {
  auto as = GetParam();

  Vec3 foo(as.vec);
  const Vec3 res(as.res);

  foo -= as.s;
  Vec3 baz(Vec3(as.vec) - as.s);

  ASSERT_EQ(res, foo);
  ASSERT_EQ(res, baz);
  ASSERT_EQ(foo, baz);
}

INSTANTIATE_TEST_CASE_P(
    Default, Vec3MinusScalarTest,
    // FIXME: this is ugly.
    testing::Values(Vec3ScalarData{{0.0, 0.0, 0.0}, 0.0, {0.0, 0.0, 0.0}},
                    Vec3ScalarData{{1.0, 2.0, 3.0}, 2.0, {-1.0, -0.0, 1.0}},
                    Vec3ScalarData{
                        {-9.0, 4.42, 3.0}, -1.1, {-7.9, 5.52, 4.1}}));

class Vec3MultiplyScalarTest : public ::testing::TestWithParam<Vec3ScalarData> {
};

TEST_P(Vec3MultiplyScalarTest, Multiply) {
  auto as = GetParam();

  Vec3 foo(as.vec);
  const Vec3 res(as.res);

  foo *= as.s;
  Vec3 baz(Vec3(as.vec) * as.s);

  ASSERT_EQ(res, foo);
  ASSERT_EQ(res, baz);
  ASSERT_EQ(foo, baz);
}

INSTANTIATE_TEST_CASE_P(
    Default, Vec3MultiplyScalarTest,
    // FIXME: this is ugly.
    testing::Values(Vec3ScalarData{{0.0, 0.0, 0.0}, 0.0, {0.0, 0.0, 0.0}},
                    Vec3ScalarData{{1.0, -2.1, 3.0}, 1.0, {1.0, -2.1, 3.0}},
                    Vec3ScalarData{{-5.0, -3.1, 2.0}, -1.0, {5.0, 3.1, -2.0}},
                    Vec3ScalarData{{1.0, 2.1, 3.0}, 2.0, {2.0, 4.2, 6.0}},
                    Vec3ScalarData{
                        {-9.0, 4.42, 3.0}, -1.5, {13.5, -6.63, -4.5}}));

class Vec3DivideScalarTest : public ::testing::TestWithParam<Vec3ScalarData> {};

TEST_P(Vec3DivideScalarTest, Divide) {
  auto as = GetParam();

  Vec3 foo(as.vec);
  const Vec3 res(as.res);

  foo /= as.s;
  Vec3 baz(Vec3(as.vec) / as.s);

  ASSERT_EQ(res, foo);
  ASSERT_EQ(res, baz);
  ASSERT_EQ(foo, baz);
}

INSTANTIATE_TEST_CASE_P(
    Default, Vec3DivideScalarTest,
    // FIXME: this is ugly.
    testing::Values(Vec3ScalarData{{0.0, 0.0, 0.0}, 1.0, {0.0, 0.0, 0.0}},
                    Vec3ScalarData{{1.0, 2.1, 3.0}, 2.0, {0.5, 1.05, 1.5}},
                    Vec3ScalarData{
                        {-9.0, 6.666, 3.0}, -3.0, {3.0, -2.222, -1.0}}));

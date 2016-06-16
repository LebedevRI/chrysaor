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

#include "Vec3.hpp"                 // for Vec3
#include <gtest/gtest-param-test.h> // for ParamIteratorInterface, ParamGen...
#include <gtest/gtest.h>            // for ASSERT_EQ, AssertHelper, TestWit...
#include <iostream>                 // for operator<<, basic_ostream, basic...

struct Vec3VectorData {
  double in[3];
  double vec[3];
  double res[3];
  friend std::ostream &operator<<(std::ostream &os, const Vec3VectorData &obj) {
    return os << "in vector: (" << obj.in[0] << "; " << obj.in[1] << "; "
              << obj.in[2] << "), coeff vector: (" << obj.vec[0] << "; "
              << obj.vec[1] << "; " << obj.vec[2] << "), result: ("
              << obj.res[0] << "; " << obj.res[1] << "; " << obj.res[2] << ")";
  }
};

class Vec3PlusVectorTest : public ::testing::TestWithParam<Vec3VectorData> {};

TEST_P(Vec3PlusVectorTest, Plus) {
  auto as = GetParam();

  const Vec3 vec(as.vec);
  const Vec3 res(as.res);

  Vec3 foo(as.in);
  foo += vec;

  Vec3 bar(Vec3(as.in) + vec);

  Vec3 baz(Vec3(as.in) + as.vec);

  ASSERT_EQ(res, foo);
  ASSERT_EQ(res, bar);
  ASSERT_EQ(res, baz);

  ASSERT_EQ(foo, bar);
  ASSERT_EQ(foo, baz);
  ASSERT_EQ(bar, baz);
}

INSTANTIATE_TEST_CASE_P(
    Default, Vec3PlusVectorTest,
    // FIXME: this is ugly.
    testing::Values(
        Vec3VectorData{{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}},
        Vec3VectorData{{1.0, 2.0, 3.0}, {1.0, 1.0, 1.0}, {2.0, 3.0, 4.0}},
        Vec3VectorData{
            {-9.0, 4.42, 3.0}, {-2.0, -2.0, -2.0}, {-11.0, 2.42, 1.0}}));

class Vec3MinusVectorTest : public ::testing::TestWithParam<Vec3VectorData> {};

TEST_P(Vec3MinusVectorTest, Minus) {
  auto as = GetParam();

  const Vec3 vec(as.vec);
  const Vec3 res(as.res);

  Vec3 foo(as.in);
  foo -= vec;

  Vec3 bar(Vec3(as.in) - vec);

  Vec3 baz(Vec3(as.in) - as.vec);

  ASSERT_EQ(res, foo);
  ASSERT_EQ(res, bar);
  ASSERT_EQ(res, baz);

  ASSERT_EQ(foo, bar);
  ASSERT_EQ(foo, baz);
  ASSERT_EQ(bar, baz);
}

INSTANTIATE_TEST_CASE_P(
    Default, Vec3MinusVectorTest,
    // FIXME: this is ugly.
    testing::Values(
        Vec3VectorData{{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}},
        Vec3VectorData{{1.0, 2.0, 3.0}, {1.0, 2.0, 5.0}, {0.0, -0.0, -2.0}},
        Vec3VectorData{
            {-9.0, 4.42, 3.0}, {-1.0, -1.1, -1.5}, {-8.0, 5.52, 4.5}}));

class Vec3MultiplyVectorTest : public ::testing::TestWithParam<Vec3VectorData> {
};

TEST_P(Vec3MultiplyVectorTest, Multiply) {
  auto as = GetParam();

  const Vec3 vec(as.vec);
  const Vec3 res(as.res);

  Vec3 foo(as.in);
  foo *= vec;

  Vec3 bar(Vec3(as.in) * vec);

  Vec3 baz(Vec3(as.in) * as.vec);

  ASSERT_EQ(res, foo);
  ASSERT_EQ(res, bar);
  ASSERT_EQ(res, baz);

  ASSERT_EQ(foo, bar);
  ASSERT_EQ(foo, baz);
  ASSERT_EQ(bar, baz);
}

INSTANTIATE_TEST_CASE_P(
    Default, Vec3MultiplyVectorTest,
    // FIXME: this is ugly.
    testing::Values(
        Vec3VectorData{{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}},
        Vec3VectorData{{1.0, -2.1, 3.0}, {1.0, 1.0, 1.0}, {1.0, -2.1, 3.0}},
        Vec3VectorData{{-5.0, -3.1, 2.0}, {-1.0, 0.0, 1.0}, {5.0, 0.0, 2.0}},
        Vec3VectorData{{1.0, 2.1, 3.0}, {2.0, 2.0, 2.0}, {2.0, 4.2, 6.0}},
        Vec3VectorData{
            {-9.0, 4.42, 3.0}, {-1.5, -1.5, 1.5}, {13.5, -6.63, 4.5}}));

class Vec3DivideVectorTest : public ::testing::TestWithParam<Vec3VectorData> {};

TEST_P(Vec3DivideVectorTest, Divide) {
  auto as = GetParam();

  const Vec3 vec(as.vec);
  const Vec3 res(as.res);

  Vec3 foo(as.in);
  foo /= vec;

  Vec3 bar(Vec3(as.in) / vec);

  Vec3 baz(Vec3(as.in) / as.vec);

  ASSERT_EQ(res, foo);
  ASSERT_EQ(res, bar);
  ASSERT_EQ(res, baz);

  ASSERT_EQ(foo, bar);
  ASSERT_EQ(foo, baz);
  ASSERT_EQ(bar, baz);
}

INSTANTIATE_TEST_CASE_P(
    Default, Vec3DivideVectorTest,
    // FIXME: this is ugly.
    testing::Values(
        Vec3VectorData{{0.0, 0.0, 0.0}, {1.0, 2.0, 9.0}, {0.0, 0.0, 0.0}},
        Vec3VectorData{{1.0, 2.1, 3.0}, {1.0, 1.0, 3.0}, {1.0, 2.1, 1.0}},
        Vec3VectorData{
            {-9.0, 6.66, 3.0}, {-3.0, -3.0, 3.0}, {3.0, -2.22, 1.0}}));

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

#include "src/Vec3.hpp"             // for Vec3
#include <gtest/gtest-param-test.h> // for ParamIteratorInterface, ParamGen...
#include <gtest/gtest.h>            // for ASSERT_DOUBLE_EQ, AssertHelper
#include <iomanip>                  // for operator<<
#include <ostream>                  // for operator<<, basic_ostream, basic...

struct Vec3NormData {
  double v[3];
  double norm;
  friend std::ostream &operator<<(std::ostream &os, const Vec3NormData &obj) {
    return os << "vector: (" << obj.v[0] << "; " << obj.v[1] << "; " << obj.v[2]
              << "), norm: " << obj.norm;
  }
};

class Vec3NormTest : public ::testing::TestWithParam<Vec3NormData> {};

TEST_P(Vec3NormTest, Assert) {
  auto as = GetParam();

  {
    Vec3 foo(as.v);
    ASSERT_DOUBLE_EQ(as.norm, foo.norm());
  }

  // FIXME: this is ugly.
  // tests that x^2 == (-x)^2

  {
    Vec3 foo(-as.v[0], as.v[1], as.v[2]);
    ASSERT_DOUBLE_EQ(as.norm, foo.norm());
  }
  {
    Vec3 foo(as.v[0], -as.v[1], as.v[2]);
    ASSERT_DOUBLE_EQ(as.norm, foo.norm());
  }
  {
    Vec3 foo(as.v[0], as.v[1], -as.v[2]);
    ASSERT_DOUBLE_EQ(as.norm, foo.norm());
  }

  {
    Vec3 foo(-as.v[0], -as.v[1], as.v[2]);
    ASSERT_DOUBLE_EQ(as.norm, foo.norm());
  }
  {
    Vec3 foo(as.v[0], -as.v[1], -as.v[2]);
    ASSERT_DOUBLE_EQ(as.norm, foo.norm());
  }
  {
    Vec3 foo(-as.v[0], as.v[1], -as.v[2]);
    ASSERT_DOUBLE_EQ(as.norm, foo.norm());
  }

  {
    Vec3 foo(-as.v[0], -as.v[1], -as.v[2]);
    ASSERT_DOUBLE_EQ(as.norm, foo.norm());
  }
}

INSTANTIATE_TEST_CASE_P(
    Default, Vec3NormTest,
    // FIXME: this is ugly.
    testing::Values(Vec3NormData{{0.0, 0.0, 0.0}, 0.0},
                    Vec3NormData{{1.0, 0.0, 0.0}, 1.0},
                    Vec3NormData{{0.0, 1.0, 0.0}, 1.0},
                    Vec3NormData{{0.0, 0.0, 1.0}, 1.0},
                    Vec3NormData{{1.0, 1.0, 0.0}, 1.4142135623730951},
                    Vec3NormData{{0.0, 1.0, 1.0}, 1.4142135623730951},
                    Vec3NormData{{1.0, 0.0, 1.0}, 1.4142135623730951},
                    Vec3NormData{{1.0, 1.0, 1.0}, 1.7320508075688772}));

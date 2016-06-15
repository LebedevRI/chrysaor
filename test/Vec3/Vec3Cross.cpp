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

#include <gtest/gtest-param-test.h> // for ParamIteratorInterface, ParamGen...
#include <gtest/gtest.h>            // for ASSERT_EQ, AssertHelper, TestWit...
#include <iostream>                 // for operator<<, basic_ostream, basic...

struct Vec3CrossData {
  double v0[3];
  double v1[3];
  double c[3];
  friend std::ostream &operator<<(std::ostream &os, const Vec3CrossData &obj) {
    return os << "vector 1: (" << obj.v0[0] << "; " << obj.v0[1] << "; "
              << obj.v0[2] << "), vector 2: (" << obj.v1[0] << "; " << obj.v1[1]
              << "; " << obj.v1[2] << "), cross: (" << obj.c[0] << "; "
              << obj.c[1] << "; " << obj.c[2] << ")";
  }
};

class Vec3CrossTest : public ::testing::TestWithParam<Vec3CrossData> {};

TEST_P(Vec3CrossTest, Assert) {
  auto as = GetParam();

  Vec3 refcross(as.c);

  Vec3 foo(as.v0);
  Vec3 bar(as.v1);

  Vec3 cross(foo.cross(bar));

  ASSERT_EQ(refcross, cross);
}

INSTANTIATE_TEST_CASE_P(
    Default, Vec3CrossTest,
    // FIXME: this is ugly.
    testing::Values(
        Vec3CrossData{{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}},
        Vec3CrossData{{1.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}},
        Vec3CrossData{{1.0, 1.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}},
        Vec3CrossData{{1.0, 1.0, 1.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}},
        Vec3CrossData{{1.0, 1.0, 1.0}, {1.0, 0.0, 0.0}, {0.0, 1.0, -1.0}},
        Vec3CrossData{{1.0, 1.0, 1.0}, {0.0, 1.0, 0.0}, {-1.0, 0.0, 1.0}},
        Vec3CrossData{{1.0, 1.0, 1.0}, {0.0, 0.0, 1.0}, {1.0, -1.0, 0.0}},
        Vec3CrossData{{1.0, 1.0, 1.0}, {1.0, 1.0, 0.0}, {-1.0, 1.0, 0.0}},
        Vec3CrossData{{1.0, 1.0, 1.0}, {0.0, 1.0, 1.0}, {0.0, -1.0, 1.0}},
        Vec3CrossData{{1.0, 1.0, 1.0}, {1.0, 0.0, 1.0}, {1.0, 0.0, -1.0}},
        Vec3CrossData{{1.0, 1.0, 1.0}, {1.0, 1.0, 1.0}, {0.0, 0.0, 0.0}}));

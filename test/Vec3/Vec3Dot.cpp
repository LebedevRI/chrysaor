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

#include "src/Vec3.hpp"
#include <gtest/gtest-param-test.h> // for ParamIteratorInterface, ParamGen...
#include <gtest/gtest.h>            // for AssertHelper, ASSERT_EQ, ASSERT_...
#include <iomanip>                  // for operator<<
#include <iostream>                 // for operator<<, ostream, basic_ostream

struct Vec3DotData {
  double v0[3];
  double v1[3];
  double dot;
  friend std::ostream &operator<<(std::ostream &os, const Vec3DotData &obj) {
    return os << "vector 1: (" << obj.v0[0] << "; " << obj.v0[1] << "; "
              << obj.v0[2] << "), vector 2: (" << obj.v1[0] << "; " << obj.v1[1]
              << "; " << obj.v1[2] << "), dot: " << obj.dot;
  }
};

class Vec3DotTest : public ::testing::TestWithParam<Vec3DotData> {};

TEST_P(Vec3DotTest, Assert) {
  auto as = GetParam();

  Vec3 foo(as.v0);
  Vec3 bar(as.v1);

  ASSERT_DOUBLE_EQ(as.dot, foo.dot(bar));
  ASSERT_DOUBLE_EQ(as.dot, bar.dot(foo));
  ASSERT_DOUBLE_EQ(foo.dot(bar), bar.dot(foo));
}

INSTANTIATE_TEST_CASE_P(
    Default, Vec3DotTest,
    // FIXME: this is ugly.
    testing::Values(Vec3DotData{{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, 0.0},
                    Vec3DotData{{1.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, 0.0},
                    Vec3DotData{{1.0, 1.0, 0.0}, {0.0, 0.0, 0.0}, 0.0},
                    Vec3DotData{{1.0, 1.0, 1.0}, {0.0, 0.0, 0.0}, 0.0},
                    Vec3DotData{{1.0, 1.0, 1.0}, {1.0, 0.0, 0.0}, 1.0},
                    Vec3DotData{{1.0, 1.0, 1.0}, {0.0, 1.0, 0.0}, 1.0},
                    Vec3DotData{{1.0, 1.0, 1.0}, {0.0, 0.0, 1.0}, 1.0},
                    Vec3DotData{{1.0, 1.0, 1.0}, {1.0, 1.0, 0.0}, 2.0},
                    Vec3DotData{{1.0, 1.0, 1.0}, {0.0, 1.0, 1.0}, 2.0},
                    Vec3DotData{{1.0, 1.0, 1.0}, {1.0, 0.0, 1.0}, 2.0},
                    Vec3DotData{{1.0, 1.0, 1.0}, {1.0, 1.0, 1.0}, 3.0},

                    Vec3DotData{{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}, 32.0},
                    Vec3DotData{{1.78, -0.32, 4.2},
                                {-14.0, 0.999, 4.7},
                                -(34373.0 / 6250.0)}));

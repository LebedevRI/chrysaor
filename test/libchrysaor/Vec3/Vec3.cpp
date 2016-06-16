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

#include "Vec3.hpp"
#include <gtest/gtest.h> // for AssertHelper, ASSERT_EQ, ASSERT_NO_THROW, TEST

TEST(Vec3Test, TestConstructor) {
  ASSERT_NO_THROW({ Vec3 foo; });
  ASSERT_NO_THROW({ Vec3 bar(1.0, 2.0, 3.0); });
  ASSERT_NO_THROW({
    Vec3 bar({1.0, 2.0, 3.0});
    (void)bar;
  });
}

TEST(Vec3Test, TestComparison) {
  Vec3 foo;
  Vec3 bar(0.0, 0.0, 0.0);
  Vec3 baz({0.0, 0.0, 0.0});

  ASSERT_EQ(0.0, foo.x_);
  ASSERT_EQ(0.0, foo.y_);
  ASSERT_EQ(0.0, foo.z_);

  ASSERT_EQ(0.0, baz.x_);
  ASSERT_EQ(0.0, baz.y_);
  ASSERT_EQ(0.0, baz.z_);

  ASSERT_EQ(bar, foo);
  ASSERT_EQ(bar, baz);
  ASSERT_EQ(foo, baz);
}

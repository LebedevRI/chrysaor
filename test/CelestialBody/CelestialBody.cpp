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

#include "src/CelestialBody.hpp"
#include "gtest/gtest.h" // for AssertHelper, TEST, ASSERT_DOUBLE_EQ, ASSER...
#include <iomanip>       // for operator<<

TEST(CelestialBodyTest, TestConstructor) {
  ASSERT_NO_THROW({ CelestialBody foo; });
  ASSERT_NO_THROW({ CelestialBody foo(123.456, 6000.0); });
}

TEST(CelestialBodyTest, TestMuGetter) {
  const double mu = 2348634811.5235423;

  CelestialBody foo(mu, 0.0);

  ASSERT_DOUBLE_EQ(mu, foo.mu_);
}

TEST(CelestialBodyTest, TestRGetter) {
  const double R = 600000.0;

  CelestialBody foo(0.0, R);

  ASSERT_DOUBLE_EQ(R, foo.R_);
}

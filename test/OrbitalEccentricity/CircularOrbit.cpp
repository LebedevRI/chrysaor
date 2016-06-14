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

#include "test/CircularOrbit.hpp"
#include "src/OrbitalEccentricity.hpp" // for OrbitalEccentricity
#include <gtest/gtest.h>               // for AssertHelper, EXPECT_DOUBLE_EQ
#include <iomanip>                     // for operator<<

extern double ecc_max_abs_err;

TEST_P(CircularOrbitTest, TwoApsisR) {
  auto as = GetParam();

  OrbitalEccentricity foo(as.altitude + as.body->R_, as.altitude + as.body->R_);

  EXPECT_DOUBLE_EQ(0.0, foo);
}

TEST_P(CircularOrbitTest, TwoApsisA) {
  auto as = GetParam();

  OrbitalEccentricity foo(as.altitude, as.altitude, as.body);

  EXPECT_DOUBLE_EQ(0.0, foo);
}

TEST_P(CircularOrbitTest, VelAlt) {
  auto as = GetParam();

  OrbitalEccentricity foo(as.velocity, 0.0, as.altitude, as.body);

  // EXPECT_FLOAT_EQ(0.0, foo);
  EXPECT_NEAR(0.0, foo, ecc_max_abs_err);
}

TEST_P(CircularOrbitTest, Default) {
  auto as = GetParam();

  OrbitalEccentricity foo(as.velocity, 0.0, as.altitude, as.body);
  OrbitalEccentricity bar(as.altitude, as.altitude, as.body);
  OrbitalEccentricity baz(as.altitude + as.body->R_, as.altitude + as.body->R_);

  // EXPECT_FLOAT_EQ(0.0, foo);
  EXPECT_NEAR(0.0, foo, ecc_max_abs_err);
  EXPECT_DOUBLE_EQ(0.0, bar);
  EXPECT_DOUBLE_EQ(0.0, baz);
  EXPECT_NEAR(foo, bar, ecc_max_abs_err);
  EXPECT_NEAR(foo, baz, ecc_max_abs_err);
  EXPECT_DOUBLE_EQ(bar, baz);
}

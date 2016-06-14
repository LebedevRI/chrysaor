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

#include "test/EllipticalOrbit.hpp"
#include "src/SemiMajorAxis.hpp"         // for SemiMajorAxis
#include "src/SpecificOrbitalEnergy.hpp" // for SpecificOrbitalEnergy
#include <gtest/gtest.h>                 // for AssertHelper, EXPECT_DOUBLE_EQ
#include <iomanip>                       // for operator<<

TEST_P(EllipticalOrbitTest, SMA) {
  auto as = GetParam();

  SemiMajorAxis foo(as.sma);

  EXPECT_DOUBLE_EQ(as.sma, foo);
}

TEST_P(EllipticalOrbitTest, SOE) {
  auto as = GetParam();

  SpecificOrbitalEnergy foo_soe(as.altitude, as.apoapsis, as.body);
  SemiMajorAxis foo(foo_soe, as.body);

  EXPECT_DOUBLE_EQ(as.sma, foo);
}

TEST_P(EllipticalOrbitTest, TwoApsisR) {
  auto as = GetParam();

  SemiMajorAxis foo(as.apoapsis + as.body->R_, as.altitude + as.body->R_);

  EXPECT_DOUBLE_EQ(as.sma, foo);
}

TEST_P(EllipticalOrbitTest, TwoApsisA) {
  auto as = GetParam();

  SemiMajorAxis foo(as.apoapsis, as.altitude, as.body);

  EXPECT_DOUBLE_EQ(as.sma, foo);
}

TEST_P(EllipticalOrbitTest, VelAlt) {
  auto as = GetParam();

  SemiMajorAxis foo(as.velocity, 0.0, as.altitude, as.body);

  EXPECT_FLOAT_EQ(as.sma, foo);
}

// all the real constructors should result in same SMA
TEST_P(EllipticalOrbitTest, Default) {
  auto as = GetParam();

  SemiMajorAxis foo(as.velocity, 0.0, as.altitude, as.body);
  SemiMajorAxis bar(as.apoapsis + as.body->R_, as.altitude + as.body->R_);
  SemiMajorAxis baz(as.apoapsis, as.altitude, as.body);
  SemiMajorAxis qux(as.sma);

  SpecificOrbitalEnergy quux_soe(as.altitude, as.apoapsis, as.body);
  SemiMajorAxis quux(quux_soe, as.body);

  EXPECT_FLOAT_EQ(as.sma, foo);
  EXPECT_DOUBLE_EQ(as.sma, bar);
  EXPECT_DOUBLE_EQ(as.sma, baz);
  EXPECT_DOUBLE_EQ(as.sma, qux);
  EXPECT_DOUBLE_EQ(as.sma, quux);
  EXPECT_FLOAT_EQ(foo, bar);
  EXPECT_FLOAT_EQ(foo, baz);
  EXPECT_FLOAT_EQ(foo, qux);
  EXPECT_FLOAT_EQ(foo, quux);
  EXPECT_DOUBLE_EQ(bar, baz);
  EXPECT_DOUBLE_EQ(bar, qux);
  EXPECT_DOUBLE_EQ(bar, quux);
  EXPECT_DOUBLE_EQ(baz, qux);
  EXPECT_DOUBLE_EQ(baz, quux);
  EXPECT_DOUBLE_EQ(qux, quux);
}

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
#include "src/SemiMajorAxis.hpp"         // for SemiMajorAxis
#include "src/SpecificOrbitalEnergy.hpp" // for SpecificOrbitalEnergy
#include <gtest/gtest.h>                 // for AssertHelper, EXPECT_DOUBLE_EQ
#include <iomanip>                       // for operator<<

TEST_P(CircularOrbitTest, SMA) {
  auto as = GetParam();

  SemiMajorAxis foo(as.sma);

  EXPECT_DOUBLE_EQ(as.sma, foo);
}

TEST_P(CircularOrbitTest, SOE) {
  auto as = GetParam();

  SpecificOrbitalEnergy foo_soe(as.altitude, as.altitude, as.body);
  SemiMajorAxis foo_sma(foo_soe, as.body);

  EXPECT_DOUBLE_EQ(as.sma, foo_sma);
}

TEST_P(CircularOrbitTest, TwoApsisR) {
  auto as = GetParam();

  SemiMajorAxis foo(as.sma, as.sma);

  EXPECT_DOUBLE_EQ(as.sma, foo);
}

TEST_P(CircularOrbitTest, TwoApsisA) {
  auto as = GetParam();

  SemiMajorAxis foo(as.altitude, as.altitude, as.body);

  EXPECT_DOUBLE_EQ(as.sma, foo);
}

TEST_P(CircularOrbitTest, VelAlt) {
  auto as = GetParam();

  SemiMajorAxis foo(as.velocity, 0.0, as.altitude, as.body);

  EXPECT_DOUBLE_EQ(as.sma, foo);
}

// all the real constructors should result in same SMA
TEST_P(CircularOrbitTest, Default) {
  auto as = GetParam();

  SemiMajorAxis foo(as.velocity, 0.0, as.altitude, as.body);
  SemiMajorAxis bar(as.sma, as.sma);
  SemiMajorAxis baz(as.altitude, as.altitude, as.body);
  SemiMajorAxis qux(as.sma);

  SpecificOrbitalEnergy quux_soe(as.altitude, as.altitude, as.body);
  SemiMajorAxis quux(quux_soe, as.body);

  EXPECT_DOUBLE_EQ(as.sma, foo);
  EXPECT_DOUBLE_EQ(as.sma, bar);
  EXPECT_DOUBLE_EQ(as.sma, baz);
  EXPECT_DOUBLE_EQ(as.sma, qux);
  EXPECT_DOUBLE_EQ(as.sma, quux);
  EXPECT_DOUBLE_EQ(foo, bar);
  EXPECT_DOUBLE_EQ(foo, baz);
  EXPECT_DOUBLE_EQ(foo, qux);
  EXPECT_DOUBLE_EQ(foo, quux);
  EXPECT_DOUBLE_EQ(bar, baz);
  EXPECT_DOUBLE_EQ(bar, qux);
  EXPECT_DOUBLE_EQ(bar, quux);
  EXPECT_DOUBLE_EQ(baz, qux);
  EXPECT_DOUBLE_EQ(baz, quux);
  EXPECT_DOUBLE_EQ(qux, quux);
}

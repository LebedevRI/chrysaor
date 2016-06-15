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
#include "src/OrbitalEccentricity.hpp"             // for OrbitalEccentricity
#include "src/SemiMajorAxis.hpp"                   // for SemiMajorAxis
#include "src/SpecificOrbitalEnergy.hpp"           // for SpecificOrbitalEnergy
#include "src/SpecificRelativeAngularMomentum.hpp" // for SpecificRelativeAngularMomentum
#include <gtest/gtest.h> // for AssertHelper, EXPECT_DOUBLE_EQ
#include <iomanip>       // for operator<<

TEST_P(CircularOrbitTest, Epsilon) {
  auto as = GetParam();

  SpecificOrbitalEnergy foo(as.epsilon);

  EXPECT_DOUBLE_EQ(as.epsilon, foo);
}

TEST_P(CircularOrbitTest, SMA) {
  auto as = GetParam();

  SemiMajorAxis foo_sma(as.sma);
  SpecificOrbitalEnergy foo(foo_sma, as.body);

  EXPECT_DOUBLE_EQ(as.epsilon, foo);
}

TEST_P(CircularOrbitTest, TwoApsis) {
  auto as = GetParam();

  SpecificOrbitalEnergy foo(as.altitude, as.altitude, as.body);

  EXPECT_DOUBLE_EQ(as.epsilon, foo);
}

TEST_P(CircularOrbitTest, EccSrh) {
  auto as = GetParam();

  OrbitalEccentricity ecc(as.ecc);
  SpecificRelativeAngularMomentum srh(as.srh);
  SpecificOrbitalEnergy foo(ecc, srh, as.body);

  EXPECT_DOUBLE_EQ(as.epsilon, foo);
}

TEST_P(CircularOrbitTest, VelAlt) {
  auto as = GetParam();

  SpecificOrbitalEnergy foo(as.velocity, 0.0, as.altitude, as.body);

  EXPECT_DOUBLE_EQ(as.epsilon, foo);
}

TEST_P(CircularOrbitTest, Default) {
  auto as = GetParam();

  SpecificOrbitalEnergy foo(as.velocity, 0.0, as.altitude, as.body);
  SpecificOrbitalEnergy bar(as.altitude, as.altitude, as.body);
  SpecificOrbitalEnergy baz(as.epsilon);

  SemiMajorAxis qux_sma(as.sma);
  SpecificOrbitalEnergy qux(qux_sma, as.body);

  OrbitalEccentricity quux_ecc(as.ecc);
  SpecificRelativeAngularMomentum quux_srh(as.srh);
  SpecificOrbitalEnergy quux(quux_ecc, quux_srh, as.body);

  EXPECT_DOUBLE_EQ(as.epsilon, foo);
  EXPECT_DOUBLE_EQ(as.epsilon, bar);
  EXPECT_DOUBLE_EQ(as.epsilon, baz);
  EXPECT_DOUBLE_EQ(as.epsilon, qux);
  EXPECT_DOUBLE_EQ(foo, bar);
  EXPECT_DOUBLE_EQ(foo, baz);
  EXPECT_DOUBLE_EQ(foo, qux);
  EXPECT_DOUBLE_EQ(bar, baz);
  EXPECT_DOUBLE_EQ(bar, qux);
  EXPECT_DOUBLE_EQ(baz, qux);
}

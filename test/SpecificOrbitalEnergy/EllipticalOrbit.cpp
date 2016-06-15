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
#include "src/OrbitalEccentricity.hpp"                      // for OrbitalE...
#include "src/SemiMajorAxis.hpp"                            // for SemiMajo...
#include "src/SpecificOrbitalEnergy.hpp"                    // for Specific...
#include "src/SpecificRelativeAngularMomentum.hpp"          // for Specific...
#include "test/OrbitalEccentricity/OrbitalEccentricity.hpp" // for OrbitalE...
#include <gtest/gtest-param-test.h>                         // for Paramete...
#include <gtest/gtest.h>                                    // for EXPECT_D...
#include <iomanip>                                          // for operator<<

TEST_P(OrbitalEccentricityTest, Epsilon) {
  auto as = GetParam();

  SpecificOrbitalEnergy foo(as.epsilon);

  EXPECT_DOUBLE_EQ(as.epsilon, foo);
}

TEST_P(OrbitalEccentricityTest, SMA) {
  auto as = GetParam();

  SemiMajorAxis foo_sma(as.sma);
  SpecificOrbitalEnergy foo(foo_sma, as.body);

  EXPECT_DOUBLE_EQ(as.epsilon, foo);
}

TEST_P(OrbitalEccentricityTest, TwoApsis) {
  auto as = GetParam();

  SpecificOrbitalEnergy foo(as.altitude, as.apoapsis, as.body);

  EXPECT_DOUBLE_EQ(as.epsilon, foo);
}

TEST_P(OrbitalEccentricityTest, EccSrh) {
  auto as = GetParam();

  OrbitalEccentricity ecc(as.ecc);
  SpecificRelativeAngularMomentum srh(as.srh);
  SpecificOrbitalEnergy foo(ecc, srh, as.body);

  EXPECT_DOUBLE_EQ(as.epsilon, foo);
}

TEST_P(OrbitalEccentricityTest, VelAlt) {
  auto as = GetParam();

  SpecificOrbitalEnergy foo(as.velocity, 0.0, as.altitude, as.body);

  EXPECT_FLOAT_EQ(as.epsilon, foo);
}

TEST_P(OrbitalEccentricityTest, Default) {
  auto as = GetParam();

  SpecificOrbitalEnergy foo(as.velocity, 0.0, as.altitude, as.body);
  SpecificOrbitalEnergy bar(as.altitude, as.apoapsis, as.body);
  SpecificOrbitalEnergy baz(as.epsilon);

  SemiMajorAxis qux_sma(as.sma);
  SpecificOrbitalEnergy qux(qux_sma, as.body);

  OrbitalEccentricity quux_ecc(as.ecc);
  SpecificRelativeAngularMomentum quux_srh(as.srh);
  SpecificOrbitalEnergy quux(quux_ecc, quux_srh, as.body);

  EXPECT_FLOAT_EQ(as.epsilon, foo);
  EXPECT_DOUBLE_EQ(as.epsilon, bar);
  EXPECT_DOUBLE_EQ(as.epsilon, baz);
  EXPECT_DOUBLE_EQ(as.epsilon, qux);
  EXPECT_FLOAT_EQ(foo, bar);
  EXPECT_FLOAT_EQ(foo, baz);
  EXPECT_FLOAT_EQ(foo, qux);
  EXPECT_DOUBLE_EQ(bar, baz);
  EXPECT_DOUBLE_EQ(bar, qux);
  EXPECT_DOUBLE_EQ(baz, qux);
}

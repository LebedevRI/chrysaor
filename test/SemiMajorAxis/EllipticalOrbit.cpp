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

#include "test/EllipticalOrbit.hpp"                // for EllipticalOrbitData
#include "src/CelestialBody.hpp"                   // for CelestialBody
#include "src/OrbitalEccentricity.hpp"             // for OrbitalEccentricity
#include "src/SemiMajorAxis.hpp"                   // for SemiMajorAxis
#include "src/SpecificOrbitalEnergy.hpp"           // for SpecificOrbitalEn...
#include "src/SpecificRelativeAngularMomentum.hpp" // for SpecificRelativeA...
#include "test/SemiMajorAxis/SemiMajorAxis.hpp"    // for SemiMajorAxisTest
#include <gtest/gtest-param-test.h>                // for ParameterizedTest...
#include <gtest/gtest.h>                           // for EXPECT_DOUBLE_EQ
#include <iomanip>                                 // for operator<<

TEST_P(SemiMajorAxisTest, SMA) {
  auto as = GetParam();

  SemiMajorAxis foo(as.sma);

  EXPECT_DOUBLE_EQ(as.sma, foo);
}

TEST_P(SemiMajorAxisTest, SOE) {
  auto as = GetParam();

  SpecificOrbitalEnergy foo_soe(as.altitude, as.apoapsis, as.body);
  SemiMajorAxis foo(foo_soe, as.body);

  EXPECT_DOUBLE_EQ(as.sma, foo);
}

TEST_P(SemiMajorAxisTest, TwoApsisR) {
  auto as = GetParam();

  SemiMajorAxis foo(as.apoapsis + as.body->R_, as.altitude + as.body->R_);

  EXPECT_DOUBLE_EQ(as.sma, foo);
}

TEST_P(SemiMajorAxisTest, TwoApsisA) {
  auto as = GetParam();

  SemiMajorAxis foo(as.apoapsis, as.altitude, as.body);

  EXPECT_DOUBLE_EQ(as.sma, foo);
}

TEST_P(SemiMajorAxisTest, EccSrh) {
  auto as = GetParam();

  OrbitalEccentricity ecc(as.ecc);
  SpecificRelativeAngularMomentum srh(as.srh);
  SemiMajorAxis foo(ecc, srh, as.body);

  EXPECT_DOUBLE_EQ(as.sma, foo);
}

TEST_P(SemiMajorAxisTest, VelAlt) {
  auto as = GetParam();

  SemiMajorAxis foo(as.velocity, 0.0, as.altitude, as.body);

  EXPECT_FLOAT_EQ(as.sma, foo);
}

// all the real constructors should result in same SMA
TEST_P(SemiMajorAxisTest, Default) {
  auto as = GetParam();

  SemiMajorAxis foo(as.velocity, 0.0, as.altitude, as.body);
  SemiMajorAxis bar(as.apoapsis + as.body->R_, as.altitude + as.body->R_);
  SemiMajorAxis baz(as.apoapsis, as.altitude, as.body);
  SemiMajorAxis qux(as.sma);

  SpecificOrbitalEnergy quux_soe(as.altitude, as.apoapsis, as.body);
  SemiMajorAxis quux(quux_soe, as.body);

  OrbitalEccentricity corge_ecc(as.ecc);
  SpecificRelativeAngularMomentum corge_srh(as.srh);
  SemiMajorAxis corge(corge_ecc, corge_srh, as.body);

  EXPECT_FLOAT_EQ(as.sma, foo);
  EXPECT_DOUBLE_EQ(as.sma, bar);
  EXPECT_DOUBLE_EQ(as.sma, baz);
  EXPECT_DOUBLE_EQ(as.sma, qux);
  EXPECT_DOUBLE_EQ(as.sma, quux);
  EXPECT_DOUBLE_EQ(as.sma, corge);
  EXPECT_FLOAT_EQ(foo, bar);
  EXPECT_FLOAT_EQ(foo, baz);
  EXPECT_FLOAT_EQ(foo, qux);
  EXPECT_FLOAT_EQ(foo, quux);
  EXPECT_FLOAT_EQ(foo, corge);
  EXPECT_DOUBLE_EQ(bar, baz);
  EXPECT_DOUBLE_EQ(bar, qux);
  EXPECT_DOUBLE_EQ(bar, quux);
  EXPECT_DOUBLE_EQ(bar, corge);
  EXPECT_DOUBLE_EQ(baz, qux);
  EXPECT_DOUBLE_EQ(baz, quux);
  EXPECT_DOUBLE_EQ(baz, corge);
  EXPECT_DOUBLE_EQ(qux, quux);
  EXPECT_DOUBLE_EQ(qux, corge);
  EXPECT_DOUBLE_EQ(quux, corge);
}

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
#include "src/OrbitalEccentricity.hpp"             // for OrbitalEccentricity
#include "src/SemiMajorAxis.hpp"                   // for SemiMajorAxis
#include "src/SpecificOrbitalEnergy.hpp"           // for SpecificOrbitalEnergy
#include "src/SpecificRelativeAngularMomentum.hpp" // for SpecificRelativeAngularMomentum
#include <gtest/gtest.h> // for AssertHelper, EXPECT_DOUBLE_EQ
#include <iomanip>       // for operator<<

extern double ecc_max_abs_err;

TEST_P(EllipticalOrbitTest, Eccentricity) {
  auto as = GetParam();

  OrbitalEccentricity foo(as.ecc);

  EXPECT_DOUBLE_EQ(as.ecc, foo);
}

TEST_P(EllipticalOrbitTest, TwoApsisR) {
  auto as = GetParam();

  OrbitalEccentricity foo(as.apoapsis + as.body->R_, as.altitude + as.body->R_);

  EXPECT_DOUBLE_EQ(as.ecc, foo);
}

TEST_P(EllipticalOrbitTest, TwoApsisA) {
  auto as = GetParam();

  OrbitalEccentricity foo(as.apoapsis, as.altitude, as.body);

  EXPECT_DOUBLE_EQ(as.ecc, foo);
}

TEST_P(EllipticalOrbitTest, SmaSrh) {
  auto as = GetParam();

  SemiMajorAxis sma(as.sma);
  SpecificRelativeAngularMomentum srh(as.srh);
  OrbitalEccentricity foo(sma, srh, as.body);

  EXPECT_NEAR(as.ecc, foo, ecc_max_abs_err);
}

TEST_P(EllipticalOrbitTest, EpsSrh) {
  auto as = GetParam();

  SpecificOrbitalEnergy soe(as.epsilon);
  SpecificRelativeAngularMomentum srh(as.srh);
  OrbitalEccentricity foo(soe, srh, as.body);

  EXPECT_NEAR(as.ecc, foo, ecc_max_abs_err);
}

TEST_P(EllipticalOrbitTest, VelAlt) {
  auto as = GetParam();

  OrbitalEccentricity foo(as.velocity, 0.0, as.altitude, as.body);

  EXPECT_NEAR(as.ecc, foo, ecc_max_abs_err);
}

TEST_P(EllipticalOrbitTest, Default) {
  auto as = GetParam();

  OrbitalEccentricity foo(as.ecc);
  OrbitalEccentricity bar(as.velocity, 0.0, as.altitude, as.body);
  OrbitalEccentricity baz(as.apoapsis, as.altitude, as.body);
  OrbitalEccentricity qux(as.apoapsis + as.body->R_, as.altitude + as.body->R_);

  SpecificOrbitalEnergy quux_soe(as.epsilon);
  SpecificRelativeAngularMomentum quux_srh(as.srh);
  OrbitalEccentricity quux(quux_soe, quux_srh, as.body);

  SemiMajorAxis corge_sma(as.sma);
  SpecificRelativeAngularMomentum corge_srh(as.srh);
  OrbitalEccentricity corge(corge_sma, corge_srh, as.body);

  EXPECT_DOUBLE_EQ(as.ecc, foo);
  EXPECT_NEAR(as.ecc, bar, ecc_max_abs_err);
  EXPECT_DOUBLE_EQ(as.ecc, baz);
  EXPECT_DOUBLE_EQ(as.ecc, qux);
  EXPECT_NEAR(as.ecc, quux, ecc_max_abs_err);
  EXPECT_NEAR(as.ecc, corge, ecc_max_abs_err);
  EXPECT_NEAR(foo, bar, ecc_max_abs_err);
  EXPECT_DOUBLE_EQ(foo, baz);
  EXPECT_DOUBLE_EQ(foo, qux);
  EXPECT_NEAR(foo, quux, ecc_max_abs_err);
  EXPECT_NEAR(foo, corge, ecc_max_abs_err);
  EXPECT_NEAR(bar, baz, ecc_max_abs_err);
  EXPECT_NEAR(bar, qux, ecc_max_abs_err);
  EXPECT_NEAR(bar, quux, ecc_max_abs_err);
  EXPECT_NEAR(bar, corge, ecc_max_abs_err);
  EXPECT_DOUBLE_EQ(baz, qux);
  EXPECT_NEAR(baz, quux, ecc_max_abs_err);
  EXPECT_NEAR(baz, corge, ecc_max_abs_err);
  EXPECT_NEAR(qux, quux, ecc_max_abs_err);
  EXPECT_NEAR(qux, corge, ecc_max_abs_err);
  EXPECT_NEAR(quux, corge, ecc_max_abs_err);
}

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

extern double ecc_max_abs_err;

TEST_P(CircularOrbitTest, TwoApsisR) {
  auto as = GetParam();

  OrbitalEccentricity foo(as.sma, as.sma);

  EXPECT_DOUBLE_EQ(0.0, foo);
}

TEST_P(CircularOrbitTest, TwoApsisA) {
  auto as = GetParam();

  OrbitalEccentricity foo(as.altitude, as.altitude, as.body);

  EXPECT_DOUBLE_EQ(0.0, foo);
}

TEST_P(CircularOrbitTest, SmaSrh) {
  auto as = GetParam();

  SemiMajorAxis sma(as.sma);
  SpecificRelativeAngularMomentum srh(as.srh);
  OrbitalEccentricity foo(sma, srh, as.body);

  EXPECT_NEAR(0.0, foo, ecc_max_abs_err);
}

TEST_P(CircularOrbitTest, EpsSrh) {
  auto as = GetParam();

  SpecificOrbitalEnergy soe(as.epsilon);
  SpecificRelativeAngularMomentum srh(as.srh);
  OrbitalEccentricity foo(soe, srh, as.body);

  EXPECT_NEAR(0.0, foo, ecc_max_abs_err);
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
  OrbitalEccentricity baz(as.sma, as.sma);

  SpecificOrbitalEnergy qux_soe(as.epsilon);
  SpecificRelativeAngularMomentum qux_srh(as.srh);
  OrbitalEccentricity qux(qux_soe, qux_srh, as.body);

  SemiMajorAxis quux_sma(as.sma);
  SpecificRelativeAngularMomentum quux_srh(as.srh);
  OrbitalEccentricity quux(quux_sma, quux_srh, as.body);

  // EXPECT_FLOAT_EQ(0.0, foo);
  EXPECT_NEAR(0.0, foo, ecc_max_abs_err);
  EXPECT_DOUBLE_EQ(0.0, bar);
  EXPECT_DOUBLE_EQ(0.0, baz);
  EXPECT_NEAR(0.0, qux, ecc_max_abs_err);
  EXPECT_NEAR(0.0, quux, ecc_max_abs_err);
  EXPECT_NEAR(foo, bar, ecc_max_abs_err);
  EXPECT_NEAR(foo, baz, ecc_max_abs_err);
  EXPECT_NEAR(foo, qux, ecc_max_abs_err);
  EXPECT_NEAR(foo, quux, ecc_max_abs_err);
  EXPECT_DOUBLE_EQ(bar, baz);
  EXPECT_NEAR(bar, qux, ecc_max_abs_err);
  EXPECT_NEAR(bar, quux, ecc_max_abs_err);
  EXPECT_NEAR(baz, qux, ecc_max_abs_err);
  EXPECT_NEAR(baz, quux, ecc_max_abs_err);
  EXPECT_NEAR(qux, quux, ecc_max_abs_err);
}

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
#include "src/SpecificRelativeAngularMomentum.hpp" // for SpecificRelativeAngularMomentum
#include <gtest/gtest.h> // for AssertHelper, EXPECT_DOUBLE_EQ
#include <iomanip>       // for operator<<

TEST_P(CircularOrbitTest, SRH) {
  auto as = GetParam();

  SpecificRelativeAngularMomentum foo(as.srh);

  EXPECT_DOUBLE_EQ(as.srh, foo);
}

TEST_P(CircularOrbitTest, SmaEcc) {
  auto as = GetParam();

  SemiMajorAxis sma(as.sma);
  OrbitalEccentricity ecc(as.ecc);
  SpecificRelativeAngularMomentum foo(sma, ecc, as.body);

  EXPECT_DOUBLE_EQ(as.srh, foo);
}

TEST_P(CircularOrbitTest, VelAlt) {
  auto as = GetParam();

  SpecificRelativeAngularMomentum foo(as.velocity, as.altitude, as.body);

  EXPECT_DOUBLE_EQ(as.srh, foo);
}

// all the real constructors should result in same SMA
TEST_P(CircularOrbitTest, Default) {
  auto as = GetParam();

  SpecificRelativeAngularMomentum foo(as.srh);
  SpecificRelativeAngularMomentum bar(as.velocity, as.altitude, as.body);

  SemiMajorAxis baz_sma(as.sma);
  OrbitalEccentricity baz_ecc(as.ecc);
  SpecificRelativeAngularMomentum baz(baz_sma, baz_ecc, as.body);

  EXPECT_DOUBLE_EQ(as.srh, foo);
  EXPECT_DOUBLE_EQ(as.srh, bar);
  EXPECT_DOUBLE_EQ(as.srh, baz);
  EXPECT_DOUBLE_EQ(foo, bar);
  EXPECT_DOUBLE_EQ(foo, baz);
  EXPECT_DOUBLE_EQ(bar, baz);
}

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
#include "src/Apoapsis.hpp"            // for Apoapsis
#include "src/OrbitalEccentricity.hpp" // for OrbitalEccentricity
#include "src/Periapsis.hpp"           // for Periapsis
#include "src/SemiMajorAxis.hpp"       // for SemiMajorAxis
#include "test/Apsis/Apsis.hpp"        // for ApsisTest
#include <gtest/gtest-param-test.h>    // for ApsisTest_Default_Test::AddTo...
#include <gtest/gtest.h>               // for EXPECT_DOUBLE_EQ
#include <iomanip>                     // for operator<<

TEST_P(ApsisTest, Default) {
  auto as = GetParam();

  SemiMajorAxis foo_sma(as.sma);
  OrbitalEccentricity foo_ecc(as.ecc);
  Apoapsis foo_ap(foo_sma, foo_ecc, as.body);
  Periapsis foo_pe(foo_sma, foo_ecc, as.body);

  EXPECT_DOUBLE_EQ(as.altitude + as.body->R_, foo_pe);
  EXPECT_DOUBLE_EQ(as.apoapsis + as.body->R_, foo_ap);

  EXPECT_DOUBLE_EQ(as.altitude + as.body->R_, foo_pe.Radius());
  EXPECT_DOUBLE_EQ(as.apoapsis + as.body->R_, foo_ap.Radius());

  EXPECT_NEAR(as.altitude, foo_pe.Altitude(), 1.0e-08);
  EXPECT_FLOAT_EQ(as.apoapsis, foo_ap.Altitude());
}

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

#include "CelestialBody.hpp"                       // for CelestialBody
#include "OrbitalElements/Apoapsis.hpp"            // for Apoapsis
#include "OrbitalElements/CelestialBodyData.hpp"   // for Earth
#include "OrbitalElements/EllipticalOrbitData.hpp" // for EllipticalOrbitData
#include "OrbitalElements/OrbitalEccentricity.hpp" // for OrbitalEccentricity
#include "OrbitalElements/Periapsis.hpp"           // for Periapsis
#include "OrbitalElements/SemiMajorAxis.hpp"       // for SemiMajorAxis
#include <gtest/gtest.h>                           // for CmpHelperFloating...

class ApsisTest : public ::testing::TestWithParam<EllipticalOrbitData> {};

INSTANTIATE_TEST_CASE_P(Kerbin, ApsisTest,
                        testing::ValuesIn(KerbinEllipticalOrbitData));

INSTANTIATE_TEST_CASE_P(Earth, ApsisTest,
                        testing::ValuesIn(EarthEllipticalOrbitData));

TEST(FluidDynamicsTest, TestConstructor) {
  SemiMajorAxis foo_sma(122141.4314);
  OrbitalEccentricity foo_ecc(0.71);
  ASSERT_NO_THROW({ Apoapsis foo_ap(foo_sma, foo_ecc, &Earth); });
  ASSERT_NO_THROW({ Periapsis foo_pe(foo_sma, foo_ecc, &Earth); });
}

TEST(FluidDynamicsTest, TestDynamicConstructor) {
  SemiMajorAxis foo_sma(122141.4314);
  OrbitalEccentricity foo_ecc(0.71);
  ASSERT_NO_THROW({
    Apoapsis *foo_ap;
    foo_ap = new Apoapsis(foo_sma, foo_ecc, &Earth);
    delete foo_ap;
  });
  ASSERT_NO_THROW({
    Periapsis *foo_pe;
    foo_pe = new Periapsis(foo_sma, foo_ecc, &Earth);
    delete foo_pe;
  });
}

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

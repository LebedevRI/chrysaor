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

#include "OrbitalElements/SpecificOrbitalEnergy.hpp" // for SpecificOrbitalEnergy
#include "CelestialBody.hpp"                         // for CelestialBody
#include "OrbitalElements/OrbitalEccentricity.hpp"   // for OrbitalEccentricity
#include "OrbitalElements/SemiMajorAxis.hpp"         // for SemiMajorAxis
#include "SpecificRelativeAngularMomentum.hpp" // for SpecificRelativeAngularMomentum
#include <gtest/gtest.h> // for AssertHelper, ASSERT_NO_THROW, ASSE...
#include <iomanip>       // for operator<<

CelestialBody Kerbin(3.5316000e+12, 600000);
CelestialBody Earth(3.986004418e+14, 6378136.6);

TEST(SpecificOrbitalEnergyTest, TestConstructor) {
  ASSERT_NO_THROW({ SpecificOrbitalEnergy foo; });
  ASSERT_NO_THROW({ SpecificOrbitalEnergy foo(0.0); });
  ASSERT_NO_THROW({
    SemiMajorAxis a(1.0);
    SpecificOrbitalEnergy foo(a, &Kerbin);
  });
  ASSERT_NO_THROW({
    OrbitalEccentricity ecc(0.0);
    SpecificRelativeAngularMomentum srh(1.0);
    SpecificOrbitalEnergy foo(ecc, srh, &Kerbin);
  });
  ASSERT_NO_THROW({ SpecificOrbitalEnergy foo(0.0, 0.0, &Kerbin); });
  ASSERT_NO_THROW({ SpecificOrbitalEnergy foo(0.0, 0.0, 0.0, &Kerbin); });
}

TEST(SpecificOrbitalEnergyTest, TestConverters) {
  const double value = 823902213.65253211;
  SpecificOrbitalEnergy foo(value);

  ASSERT_EQ(value, foo);
  ASSERT_EQ(value, static_cast<double>(foo));
}

TEST(SpecificOrbitalEnergyTest, TestGetter) {
  {
    SpecificOrbitalEnergy foo;
    ASSERT_EQ(0.0, foo);
  }
  {
    const double sma = 123456789.0123456789;
    SpecificOrbitalEnergy foo(sma);
    ASSERT_EQ(sma, foo);
  }
  {
    // not testing all the SMA constructors. SMA tests will do that.
    SemiMajorAxis a(0.5);
    CelestialBody planet(1.0, 0.0);

    SpecificOrbitalEnergy foo(a, &planet);
    ASSERT_DOUBLE_EQ(-planet.mu_, foo);
  }
  {
    CelestialBody planet(2.0, 0.0);

    OrbitalEccentricity ecc(0.0);
    SpecificRelativeAngularMomentum srh(1.0);
    SpecificOrbitalEnergy foo(ecc, srh, &planet);
    ASSERT_DOUBLE_EQ(-2.0, foo);
  }
  {
    CelestialBody planet(1.0, 0.5);

    SpecificOrbitalEnergy foo(0.0, 0.0, &planet);
    ASSERT_DOUBLE_EQ(-planet.mu_, foo);
  }
  {
    CelestialBody planet(2.0, 1.0);

    SpecificOrbitalEnergy foo(0.0, 0.0, 0.0, &planet);
    ASSERT_DOUBLE_EQ(-planet.mu_, foo);
  }
}

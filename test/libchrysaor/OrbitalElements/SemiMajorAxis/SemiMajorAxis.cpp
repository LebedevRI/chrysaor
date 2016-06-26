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

#include "OrbitalElements/SemiMajorAxis.hpp" // for SemiMajorAxis
#include "CelestialBody.hpp"                 // for CelestialBody
#include "OrbitalElements/CelestialBodyData.hpp"
#include "OrbitalElements/OrbitalEccentricity.hpp"   // for OrbitalEccentri...
#include "OrbitalElements/SpecificOrbitalEnergy.hpp" // for SpecificOrbital...
#include "SpecificRelativeAngularMomentum.hpp"       // for SpecificRelativ...
#include <gtest/gtest.h>                             // for Message, TestPa...

TEST(SemiMajorAxisTest, TestConstructor) {
  ASSERT_NO_THROW({ SemiMajorAxis foo; });
  ASSERT_NO_THROW({ SemiMajorAxis foo(0.0); });
  ASSERT_NO_THROW({
    SpecificOrbitalEnergy epsilon(1.0);
    SemiMajorAxis foo(epsilon, &Kerbin);
  });
  ASSERT_NO_THROW({ SemiMajorAxis foo(0.0, 0.0); });
  ASSERT_NO_THROW({
    OrbitalEccentricity ecc(0.0);
    SpecificRelativeAngularMomentum srh(0.0);
    SemiMajorAxis foo(ecc, srh, &Kerbin);
  });
  ASSERT_NO_THROW({ SemiMajorAxis foo(0.0, 0.0, &Kerbin); });
  ASSERT_NO_THROW({ SemiMajorAxis foo(0.0, 0.0, 0.0, &Kerbin); });
}

TEST(SemiMajorAxisTest, TestConverters) {
  const double value = 43896214.435412451;
  SemiMajorAxis foo(value);

  ASSERT_EQ(value, foo);
  ASSERT_EQ(value, static_cast<double>(foo));
}

TEST(SemiMajorAxisTest, TestGetter) {
  {
    SemiMajorAxis foo;
    ASSERT_EQ(0.0, foo);
  }
  {
    const double sma = 123456789.0123456789;
    SemiMajorAxis foo(sma);
    ASSERT_EQ(sma, foo);
  }
  {
    // not testing all the SOE constructors. SOE tests will do that.
    SpecificOrbitalEnergy epsilon(-1.0);
    CelestialBody planet(2.0, 1.0);

    SemiMajorAxis foo(epsilon, &planet);
    ASSERT_EQ(planet.R_, foo);
  }
  {
    const double r = 1.0;
    SemiMajorAxis foo(r, r);
    ASSERT_DOUBLE_EQ(r, foo);
  }
  {
    CelestialBody planet(0.0, 1.0);

    const double r = 1.0;
    SemiMajorAxis foo(r, r, &planet);
    ASSERT_DOUBLE_EQ(r + planet.R_, foo);
  }
  {
    CelestialBody planet(1.0, 0.0);

    OrbitalEccentricity ecc(0.0);
    SpecificRelativeAngularMomentum srh(1.0);

    SemiMajorAxis foo(ecc, srh, &planet);
    ASSERT_DOUBLE_EQ(1.0, foo);
  }
  {
    CelestialBody planet(2.0, 1.0);

    const double r = 1.0;
    SemiMajorAxis foo(1.0, 0.0, r, &planet);
    ASSERT_DOUBLE_EQ(r + planet.R_, foo);
  }
}

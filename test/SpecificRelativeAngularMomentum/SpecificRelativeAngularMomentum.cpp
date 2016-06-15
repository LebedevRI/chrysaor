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

#include "src/SpecificRelativeAngularMomentum.hpp"
#include "src/CelestialBody.hpp"       // for CelestialBody
#include "src/OrbitalEccentricity.hpp" // for OrbitalEccentricity
#include "src/SemiMajorAxis.hpp"       // for SemiMajorAxis
#include <gtest/gtest.h> // for AssertHelper, ASSERT_EQ, ASSERT_NO_...
#include <iomanip>       // for operator<<

CelestialBody Kerbin(3.5316000e+12, 600000);
CelestialBody Earth(3.986004418e+14, 6378136.6);

TEST(SpecificRelativeAngularMomentumTest, TestConstructor) {
  ASSERT_NO_THROW({ SpecificRelativeAngularMomentum foo; });
  ASSERT_NO_THROW({ SpecificRelativeAngularMomentum foo(0.0); });
  ASSERT_NO_THROW({ SpecificRelativeAngularMomentum foo(0.0, 0.0, &Kerbin); });
  ASSERT_NO_THROW({
    SemiMajorAxis sma(0.0);
    OrbitalEccentricity ecc(0.0);
    SpecificRelativeAngularMomentum foo(sma, ecc, &Kerbin);
  });
}

TEST(SpecificRelativeAngularMomentumTest, TestConverters) {
  const double value = 704321.5109;
  SpecificRelativeAngularMomentum foo(value);

  ASSERT_EQ(value, foo);
  ASSERT_EQ(value, static_cast<double>(foo));
}

TEST(SpecificRelativeAngularMomentumTest, TestGetter) {
  {
    SpecificRelativeAngularMomentum foo;
    ASSERT_EQ(0.0, foo);
  }
  {
    const double sma = 123456789.0123456789;
    SpecificRelativeAngularMomentum foo(sma);
    ASSERT_EQ(sma, foo);
  }
  {
    CelestialBody planet(1.0, 0.0);

    SemiMajorAxis sma(1.0);
    OrbitalEccentricity ecc(0.0);
    SpecificRelativeAngularMomentum foo(sma, ecc, &planet);
    ASSERT_DOUBLE_EQ(1.0, foo);
  }
  {
    CelestialBody planet(0.0, 1.0);

    const double r = 0.0;
    const double v = 1.0;
    SpecificRelativeAngularMomentum foo(v, r, &planet);
    ASSERT_DOUBLE_EQ(1.0, foo);
  }
}

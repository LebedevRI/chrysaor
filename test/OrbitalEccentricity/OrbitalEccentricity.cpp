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

#include "src/OrbitalEccentricity.hpp" // for OrbitalEccentricity
#include "src/CelestialBody.hpp"       // for CelestialBody
#include "gtest/gtest.h" // for AssertHelper, ASSERT_NO_THROW, ASSE...
#include <iomanip>       // for operator<<

double ecc_max_abs_err = 1.0e-07;

CelestialBody Kerbin(3.5316000e+12, 600000);
CelestialBody Earth(3.986004418e+14, 6378136.6);

TEST(OrbitalEccentricityTest, TestConstructor) {
  ASSERT_NO_THROW({ OrbitalEccentricity foo; });
  ASSERT_NO_THROW({ OrbitalEccentricity foo(0.0); });
  ASSERT_NO_THROW({ OrbitalEccentricity foo(0.0, 0.0, 0.0, &Kerbin); });
}

TEST(OrbitalEccentricityTest, TestConverters) {
  const double value = 0.0436218423941;
  OrbitalEccentricity foo(value);

  ASSERT_EQ(value, foo);
  ASSERT_EQ(value, static_cast<double>(foo));
}

TEST(OrbitalEccentricityTest, TestGetter) {
  {
    OrbitalEccentricity foo;
    ASSERT_EQ(0.0, foo);
  }
  {
    const double ecc = 0.958951515;
    OrbitalEccentricity foo(ecc);
    ASSERT_EQ(ecc, foo);
  }
  {
    CelestialBody planet(2.0, 1.0);

    const double r = 1.0;
    OrbitalEccentricity foo(1.0, 0.0, r, &planet);
    ASSERT_DOUBLE_EQ(0.0, foo);
  }
}

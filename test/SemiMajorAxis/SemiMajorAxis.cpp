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

#include "src/SemiMajorAxis.hpp"
#include "src/CelestialBody.hpp" // for CelestialBody
#include "gtest/gtest.h"         // for AssertHelper, ASSERT_NO_THROW, ASSE...
#include <iomanip>               // for operator<<

CelestialBody Kerbin(3.5316000e+12, 600000);
CelestialBody Earth(3.986004418e+14, 6378136.6);

TEST(SemiMajorAxisTest, TestConstructor) {
  ASSERT_NO_THROW({ SemiMajorAxis foo; });
  ASSERT_NO_THROW({ SemiMajorAxis foo(0.0); });
  ASSERT_NO_THROW({ SemiMajorAxis foo(0.0, 0.0, &Kerbin); });
  ASSERT_NO_THROW({ SemiMajorAxis foo(0.0, 0.0, 0.0, &Kerbin); });
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
    CelestialBody planet(0.0, 1.0);

    const double r = 1.0;
    SemiMajorAxis foo(r, r, &planet);
    ASSERT_DOUBLE_EQ(r + planet.R_, foo);
  }
}

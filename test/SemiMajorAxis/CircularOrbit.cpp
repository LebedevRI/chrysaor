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

#include "src/CelestialBody.hpp"    // for CelestialBody
#include "src/SemiMajorAxis.hpp"    // for SemiMajorAxis
#include "gtest/gtest.h"            // for AssertHelper, EXPECT_DOUBLE_EQ
#include <gtest/gtest-param-test.h> // for ParamIteratorInterface, Circular...
#include <iomanip>                  // for operator<<
#include <iostream>                 // for operator<<, ostream, basic_ostream

struct CircularOrbitData {
  CelestialBody *body;
  double altitude;
  double velocity;

  friend std::ostream &operator<<(std::ostream &os,
                                  const CircularOrbitData &obj) {
    return os << "altitude: " << obj.altitude << ", velocity: " << obj.velocity;
  }
};

class CircularOrbitTest : public ::testing::TestWithParam<CircularOrbitData> {};

TEST_P(CircularOrbitTest, Default) {
  auto as = GetParam();

  SemiMajorAxis foo(as.velocity, 0.0, as.altitude, as.body);

  EXPECT_DOUBLE_EQ(as.altitude + as.body->R_, foo);
}

extern CelestialBody Kerbin;
extern CelestialBody Earth;

/*
 * computed using following Sage code:
 *
 * # repeat for each (mu,R)
 * mu = 3.5316000e+12
 * R = 600000
 *
 * # from Vis-viva equation, since r == a
 * v(r) = sqrt(mu/(r+R))
 *
 * RealField(128)(v(70000)) # repeat for each alt
 */

INSTANTIATE_TEST_CASE_P(
    Default, CircularOrbitTest,
    testing::Values(
        CircularOrbitData{&Kerbin, 0.0e+00, // on the surface
                          2.4261079942986873059631362994849223761e+03L},
        CircularOrbitData{&Kerbin, 7.0e+04, // min orbit, LKO
                          2.2958756011856136609450298639424336392e+03L},
        CircularOrbitData{&Kerbin, 1.0e+05, // LKO
                          2.2461395453405958017358997226141148212e+03L},
        CircularOrbitData{&Kerbin, 2.86333406e+06, // KEO
                          1.0098074305900465787999564781785011292e+03L},
        CircularOrbitData{&Earth, 0.0e+00, // on the surface
                          7.9053659669038524953066371381282806396e+03L},
        CircularOrbitData{&Earth, 1.6e+05, // min orbit, LEO
                          7.8080375433456320024561136960983276367e+03L},
        CircularOrbitData{&Earth, 2.5e+05, // LEO
                          7.7548457313704493572004139423370361328e+03L},
        CircularOrbitData{&Earth, 3.5786e+07, // GEO / GSO
                          3.0746613035946006675658281892538070679e+03L}));
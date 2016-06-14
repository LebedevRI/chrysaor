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

#include "src/CelestialBody.hpp"                   // for CelestialBody
#include "src/SpecificRelativeAngularMomentum.hpp" // for SpecificRelativeAngularMomentum
#include "gtest/gtest.h"            // for AssertHelper, EXPECT_DOUBLE_EQ
#include <gtest/gtest-param-test.h> // for ParamIteratorInterface, Circular...
#include <iomanip>                  // for operator<<
#include <iostream>                 // for operator<<, ostream, basic_ostream

struct CircularOrbitData {
  CelestialBody *body;
  double altitude;
  double velocity;
  double srh;

  friend std::ostream &operator<<(std::ostream &os,
                                  const CircularOrbitData &obj) {
    return os << "altitude: " << obj.altitude << ", velocity: " << obj.velocity
              << ", srh: " << obj.srh;
  }
};

class CircularOrbitTest : public ::testing::TestWithParam<CircularOrbitData> {};

TEST_P(CircularOrbitTest, SRH) {
  auto as = GetParam();

  SpecificRelativeAngularMomentum foo(as.srh);

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

  EXPECT_DOUBLE_EQ(as.srh, foo);
  EXPECT_DOUBLE_EQ(as.srh, bar);
  EXPECT_DOUBLE_EQ(foo, bar);
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
 * srh(r) = v(r)*(r+R)
 *
 * RealField(128)(srh(70000)) # repeat for each alt
 */

INSTANTIATE_TEST_CASE_P(
    Kerbin, CircularOrbitTest,
    testing::Values(
        CircularOrbitData{&Kerbin, 0.0e+00, // on the surface
                          2.4261079942986873059631362994849223761e+03,
                          1.4556647965792124395708714999011052224e9},
        CircularOrbitData{&Kerbin, 7.0e+04, // min orbit, LKO
                          2.2958756011856136609450298639424336392e+03,
                          1.5382366527943611329041498723061859286e9},
        CircularOrbitData{&Kerbin, 1.0e+05, // LKO
                          2.2461395453405958017358997226141148212e+03,
                          1.5722976817384168363427730291524682315e9},
        CircularOrbitData{&Kerbin, 2.86333406e+06, // KEO
                          1.0098074305900465787999564781785011292e+03,
                          3.4973004684035944938659667968750000000e9}));

INSTANTIATE_TEST_CASE_P(
    Earth, CircularOrbitTest,
    testing::Values(
        CircularOrbitData{&Earth, 0.0e+00, // on the surface
                          7.9053659669038524953066371381282806396e+03,
                          5.0421504009903854370117187500000000000e10},
        CircularOrbitData{&Earth, 1.6e+05, // min orbit, LEO
                          7.8080375433456320024561136960983276367e+03,
                          5.1050016036322166442871093750000000000e10},
        CircularOrbitData{&Earth, 2.5e+05, // LEO
                          7.7548457313704493572004139423370361328e+03,
                          5.1400176819450241088867187500000000000e10},
        CircularOrbitData{&Earth, 3.5786e+07, // GEO / GSO
                          3.0746613035946006675658281892538070679e+03,
                          1.2964043920349681091308593750000000000e11}));

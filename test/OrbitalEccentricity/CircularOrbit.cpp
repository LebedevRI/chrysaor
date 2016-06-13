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

#include "src/CelestialBody.hpp"       // for CelestialBody
#include "src/OrbitalEccentricity.hpp" // for OrbitalEccentricity
#include "gtest/gtest.h"               // for ASSERT_NEAR, AssertHelper
#include <gtest/gtest-param-test.h>    // for ParamIteratorInterface, Param...
#include <iostream>                    // for operator<<, basic_ostream

struct CircularOrbitData {
  CelestialBody *body;
  double altitude;
  double velocity;
  double epsilon;

  friend std::ostream &operator<<(std::ostream &os,
                                  const CircularOrbitData &obj) {
    return os << "altitude: " << obj.altitude << ", velocity: " << obj.velocity
              << ", epsilon: " << obj.epsilon;
  }
};

extern double ecc_max_abs_err;

class CircularOrbitTest : public ::testing::TestWithParam<CircularOrbitData> {};

TEST_P(CircularOrbitTest, VelAlt) {
  auto as = GetParam();

  OrbitalEccentricity foo(as.velocity, 0.0, as.altitude, as.body);

  // EXPECT_FLOAT_EQ(0.0, foo);
  EXPECT_NEAR(0.0, foo, ecc_max_abs_err);
}

TEST_P(CircularOrbitTest, Default) {
  auto as = GetParam();

  OrbitalEccentricity foo(as.velocity, 0.0, as.altitude, as.body);

  // EXPECT_FLOAT_EQ(0.0, foo);
  EXPECT_NEAR(0.0, foo, ecc_max_abs_err);
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
 * soe(r) = (((v(r))^2)/2) - (mu/(r+R))
 *
 * RealField(128)(soe(70000)) # repeat for each alt
 */

INSTANTIATE_TEST_CASE_P(
    Kerbin, CircularOrbitTest,
    testing::Values(
        CircularOrbitData{&Kerbin, 0.0e+00, // on the surface
                          2.4261079942986873059631362994849223761e+03,
                          -2.9430000000000000000000000000000000000e+06},
        CircularOrbitData{&Kerbin, 7.0e+04, // min orbit, LKO
                          2.2958756011856136609450298639424336392e+03,
                          -2.6355223880597013048827648162841796875e6},
        CircularOrbitData{&Kerbin, 1.0e+05, // LKO
                          2.2461395453405958017358997226141148212e+03,
                          -2.5225714285714286379516124725341796875e6},
        CircularOrbitData{&Kerbin, 2.86333406e+06, // KEO
                          1.0098074305900465787999564781785011292e+03,
                          -509855.52343743591336533427238464355469}));

INSTANTIATE_TEST_CASE_P(
    Earth, CircularOrbitTest,
    testing::Values(
        CircularOrbitData{&Earth, 0.0e+00, // on the surface
                          7.9053659669038524953066371381282806396e+03,
                          -3.1247405535340834408998489379882812500e7},
        CircularOrbitData{&Earth, 1.6e+05, // min orbit, LEO
                          7.8080375433456320024561136960983276367e+03,
                          -3.0482725139147445559501647949218750000e7},
        CircularOrbitData{&Earth, 2.5e+05, // LEO
                          7.7548457313704493572004139423370361328e+03,
                          -3.0068816158677231520414352416992187500e7},
        CircularOrbitData{&Earth, 3.5786e+07, // GEO / GSO
                          3.0746613035946006675658281892538070679e+03,
                          -4.7267710659110229462385177612304687500e6}));

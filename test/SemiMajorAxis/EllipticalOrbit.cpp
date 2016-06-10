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
#include <gtest/gtest-param-test.h> // for ParamIteratorInterface, Elliptical...
#include <iomanip>                  // for operator<<
#include <iostream>                 // for operator<<, ostream, basic_ostream

struct EllipticalOrbitData {
  CelestialBody *body;
  double altitude; // periapsis
  double velocity;

  double apoapsis;

  friend std::ostream &operator<<(std::ostream &os,
                                  const EllipticalOrbitData &obj) {
    return os << "altitude: " << obj.altitude << ", velocity: " << obj.velocity
              << ", apoapsis: " << obj.apoapsis;
  }
};

class EllipticalOrbitTest
    : public ::testing::TestWithParam<EllipticalOrbitData> {};

TEST_P(EllipticalOrbitTest, SMA) {
  auto as = GetParam();

  SemiMajorAxis foo((as.altitude + as.apoapsis + 2.0 * as.body->R_) / 2.0);

  EXPECT_DOUBLE_EQ((as.altitude + as.apoapsis + 2.0 * as.body->R_) / 2.0, foo);
}

TEST_P(EllipticalOrbitTest, TwoApsisR) {
  auto as = GetParam();

  SemiMajorAxis foo(as.apoapsis + as.body->R_, as.altitude + as.body->R_);

  EXPECT_DOUBLE_EQ((as.altitude + as.apoapsis + 2.0 * as.body->R_) / 2.0, foo);
}

TEST_P(EllipticalOrbitTest, TwoApsisA) {
  auto as = GetParam();

  SemiMajorAxis foo(as.apoapsis, as.altitude, as.body);

  EXPECT_DOUBLE_EQ((as.altitude + as.apoapsis + 2.0 * as.body->R_) / 2.0, foo);
}

TEST_P(EllipticalOrbitTest, VelAlt) {
  auto as = GetParam();

  SemiMajorAxis foo(as.velocity, 0.0, as.altitude, as.body);

  EXPECT_FLOAT_EQ((as.altitude + as.apoapsis + 2.0 * as.body->R_) / 2.0, foo);
}

// all the real constructors should result in same SMA
TEST_P(EllipticalOrbitTest, Default) {
  auto as = GetParam();

  SemiMajorAxis foo(as.velocity, 0.0, as.altitude, as.body);
  SemiMajorAxis bar(as.apoapsis + as.body->R_, as.altitude + as.body->R_);
  SemiMajorAxis baz(as.apoapsis, as.altitude, as.body);
  SemiMajorAxis qux((as.altitude + as.apoapsis + 2.0 * as.body->R_) / 2.0);

  EXPECT_FLOAT_EQ((as.altitude + as.apoapsis + 2.0 * as.body->R_) / 2.0, foo);
  EXPECT_DOUBLE_EQ((as.altitude + as.apoapsis + 2.0 * as.body->R_) / 2.0, bar);
  EXPECT_DOUBLE_EQ((as.altitude + as.apoapsis + 2.0 * as.body->R_) / 2.0, baz);
  EXPECT_DOUBLE_EQ((as.altitude + as.apoapsis + 2.0 * as.body->R_) / 2.0, qux);
  EXPECT_FLOAT_EQ(foo, bar);
  EXPECT_FLOAT_EQ(foo, baz);
  EXPECT_FLOAT_EQ(foo, qux);
  EXPECT_DOUBLE_EQ(bar, baz);
  EXPECT_DOUBLE_EQ(bar, qux);
  EXPECT_DOUBLE_EQ(baz, qux);
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
 * # from Vis-viva equation, a = (r+r2)/2
 * v(r, r2) = sqrt(mu*((2/(r+R))-(2/(r+r2+2*R))))
 *
 * RealField(128)(v(70000, 2.86333406e+06)) # repeat for each (alt, ap)
 */

INSTANTIATE_TEST_CASE_P(
    Kerbin, EllipticalOrbitTest,
    testing::Values(
        EllipticalOrbitData{&Kerbin,
                            0.0e+00, // on the surface -> min orbit, LKO
                            2.4920724702244101536052767187356948853e+03L,
                            7.0e+04},
        EllipticalOrbitData{&Kerbin,
                            0.0e+00, // on the surface -> LKO
                            2.5176912500879116123542189598083496094e+03L,
                            1.0e+05},
        EllipticalOrbitData{&Kerbin,
                            0.0e+00, // on the surface -> KEO
                            3.1676052523016251143417321145534515381e+03L,
                            2.86333406e+06},
        EllipticalOrbitData{&Kerbin,
                            7.0e+04, // min orbit, LKO -> LKO
                            2.3208767986006064347748178988695144653e+03L,
                            1.0e+05},
        EllipticalOrbitData{&Kerbin,
                            7.0e+04, // min orbit, LKO -> KEO
                            2.9720785896382690225436817854642868042e+03L,
                            2.86333406e+06},
        EllipticalOrbitData{&Kerbin,
                            1.0e+05, // LKO -> KEO
                            2.8971987833458042587153613567352294922e+03L,
                            2.86333406e+06}));

INSTANTIATE_TEST_CASE_P(
    Earth, EllipticalOrbitTest,
    testing::Values(
        EllipticalOrbitData{&Earth,
                            0.0e+00, // on the surface -> min orbit, LEO
                            7.9541790227209166914690285921096801758e+03L,
                            1.6e+05},
        EllipticalOrbitData{&Earth,
                            0.0e+00, // on the surface -> LEO
                            7.9809808103873447180376388132572174072e+03L,
                            2.5e+05},
        EllipticalOrbitData{&Earth,
                            0.0e+00, // on the surface -> GEO / GSO
                            1.0419539570032044139225035905838012695e+04L,
                            3.5786e+07},
        EllipticalOrbitData{&Earth, 1.6e+05, // min orbit, LEO -> LEO
                            7.8346785891046356482547707855701446533e+03L,
                            2.5e+05},
        EllipticalOrbitData{&Earth, 1.6e+05, // min orbit, LEO -> GEO / GSO
                            1.0274338743499216434429399669170379639e+04L,
                            3.5786e+07},
        EllipticalOrbitData{&Earth, 2.5e+05, // LEO -> GEO / GSO
                            1.0194929816018779092701151967048645020e+04L,
                            3.5786e+07}));

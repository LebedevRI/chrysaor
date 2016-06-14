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
#include <gtest/gtest-param-test.h> // for ParamIteratorInterface, Elliptical...
#include <iomanip>                  // for operator<<
#include <iostream>                 // for operator<<, ostream, basic_ostream

struct EllipticalOrbitData {
  CelestialBody *body;
  double altitude; // periapsis
  double velocity;
  double srh;

  double apoapsis;

  friend std::ostream &operator<<(std::ostream &os,
                                  const EllipticalOrbitData &obj) {
    return os << "altitude: " << obj.altitude << ", velocity: " << obj.velocity
              << ", apoapsis: " << obj.apoapsis;
  }
};

class EllipticalOrbitTest
    : public ::testing::TestWithParam<EllipticalOrbitData> {};

TEST_P(EllipticalOrbitTest, SRH) {
  auto as = GetParam();

  SpecificRelativeAngularMomentum foo(as.srh);

  EXPECT_DOUBLE_EQ(as.srh, foo);
}

TEST_P(EllipticalOrbitTest, VelAlt) {
  auto as = GetParam();

  SpecificRelativeAngularMomentum foo(as.velocity, as.altitude, as.body);

  EXPECT_DOUBLE_EQ(as.srh, foo);
}

// all the real constructors should result in same SMA
TEST_P(EllipticalOrbitTest, Default) {
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
 * # from Vis-viva equation, a = (r+r2)/2
 * v(r, r2) = sqrt(mu*((2/(r+R))-(2/(r+r2+2*R))))
 * srh(r, r2) = v(r, r2)*(r+R)
 *
 * RealField(128)(v(70000, 2.86333406e+06)) # repeat for each (alt, ap)
 */

INSTANTIATE_TEST_CASE_P(
    Kerbin, EllipticalOrbitTest,
    testing::Values(
        EllipticalOrbitData{&Kerbin,
                            0.0e+00, // on the surface -> min orbit, LKO
                            2.4920724702244101536052767187356948853e+03L,
                            1.4952434821346461772918701171875000000e9, 7.0e+04},
        EllipticalOrbitData{&Kerbin,
                            0.0e+00, // on the surface -> LKO
                            2.5176912500879116123542189598083496094e+03L,
                            1.5106147500527470111846923828125000000e9, 1.0e+05},
        EllipticalOrbitData{&Kerbin,
                            0.0e+00, // on the surface -> KEO
                            3.1676052523016251143417321145534515381e+03L,
                            1.9005631513809750080108642578125000000e9,
                            2.86333406e+06},
        EllipticalOrbitData{&Kerbin,
                            7.0e+04, // min orbit, LKO -> LKO
                            2.3208767986006064347748178988695144653e+03L,
                            1.5549874550624063014984130859375000000e9, 1.0e+05},
        EllipticalOrbitData{&Kerbin,
                            7.0e+04, // min orbit, LKO -> KEO
                            2.9720785896382690225436817854642868042e+03L,
                            1.9912926550576403141021728515625000000e9,
                            2.86333406e+06},
        EllipticalOrbitData{&Kerbin,
                            1.0e+05, // LKO -> KEO
                            2.8971987833458042587153613567352294922e+03L,
                            2.0280391483420629501342773437500000000e9,
                            2.86333406e+06}));

INSTANTIATE_TEST_CASE_P(
    Earth, EllipticalOrbitTest,
    testing::Values(
        EllipticalOrbitData{&Earth,
                            0.0e+00, // on the surface -> min orbit, LEO
                            7.9541790227209166914690285921096801758e+03L,
                            5.0732840347768508911132812500000000000e10,
                            1.6e+05},
        EllipticalOrbitData{&Earth,
                            0.0e+00, // on the surface -> LEO
                            7.9809808103873447180376388132572174072e+03L,
                            5.0903785810629180908203125000000000000e10,
                            2.5e+05},
        EllipticalOrbitData{&Earth,
                            0.0e+00, // on the surface -> GEO / GSO
                            1.0419539570032044139225035905838012695e+04L,
                            6.6457246686769638061523437500000000000e10,
                            3.5786e+07},
        EllipticalOrbitData{&Earth, 1.6e+05, // min orbit, LEO -> LEO
                            7.8346785891046356482547707855701446533e+03L,
                            5.1224198832661376953125000000000000000e10,
                            2.5e+05},
        EllipticalOrbitData{&Earth, 1.6e+05, // min orbit, LEO -> GEO / GSO
                            1.0274338743499216434429399669170379639e+04L,
                            6.7175030179670234680175781250000000000e10,
                            3.5786e+07},
        EllipticalOrbitData{&Earth, 2.5e+05, // LEO -> GEO / GSO
                            1.0194929816018779092701151967048645020e+04L,
                            6.7573387447985328674316406250000000000e10,
                            3.5786e+07}));

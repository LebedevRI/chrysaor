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

#include "src/CelestialBody.hpp"         // for CelestialBody
#include "src/SpecificOrbitalEnergy.hpp" // for SpecificOrbitalEnergy
#include "gtest/gtest.h"                 // for AssertHelper, EXPECT_DOUBLE_EQ
#include <gtest/gtest-param-test.h> // for ParamIteratorInterface, Elliptical...
#include <iomanip>                  // for operator<<
#include <iostream>                 // for operator<<, ostream, basic_ostream

struct EllipticalOrbitData {
  CelestialBody *body;
  double altitude; // periapsis
  double velocity;
  double apoapsis; // just for reference

  double epsilon;

  friend std::ostream &operator<<(std::ostream &os,
                                  const EllipticalOrbitData &obj) {
    return os << "altitude: " << obj.altitude << ", velocity: " << obj.velocity
              << ", apoapsis: " << obj.apoapsis << ", epsilon: " << obj.epsilon;
  }
};

class EllipticalOrbitTest
    : public ::testing::TestWithParam<EllipticalOrbitData> {};

TEST_P(EllipticalOrbitTest, Epsilon) {
  auto as = GetParam();

  SpecificOrbitalEnergy foo(as.epsilon);

  EXPECT_DOUBLE_EQ(as.epsilon, foo);
}

TEST_P(EllipticalOrbitTest, TwoApsis) {
  auto as = GetParam();

  SpecificOrbitalEnergy foo(as.altitude, as.apoapsis, as.body);

  EXPECT_DOUBLE_EQ(as.epsilon, foo);
}

TEST_P(EllipticalOrbitTest, VelAlt) {
  auto as = GetParam();

  SpecificOrbitalEnergy foo(as.velocity, 0.0, as.altitude, as.body);

  EXPECT_FLOAT_EQ(as.epsilon, foo);
}

TEST_P(EllipticalOrbitTest, Default) {
  auto as = GetParam();

  SpecificOrbitalEnergy foo(as.velocity, 0.0, as.altitude, as.body);
  SpecificOrbitalEnergy bar(as.altitude, as.apoapsis, as.body);
  SpecificOrbitalEnergy baz(as.epsilon);

  EXPECT_FLOAT_EQ(as.epsilon, foo);
  EXPECT_DOUBLE_EQ(as.epsilon, bar);
  EXPECT_DOUBLE_EQ(as.epsilon, baz);
  EXPECT_FLOAT_EQ(foo, bar);
  EXPECT_FLOAT_EQ(foo, baz);
  EXPECT_DOUBLE_EQ(bar, baz);
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
 * soe(r, r2) = (((v(r, r2))^2)/2) - (mu/(r+R))
 *  or
 * soe(r, r2) = -(mu/(r+r2+2*R))
 *
 * RealField(128)(soe(70000, 2.86333406e+06)) # repeat for each (alt, ap)
 */

INSTANTIATE_TEST_CASE_P(
    Kerbin, EllipticalOrbitTest,
    testing::Values(
        EllipticalOrbitData{&Kerbin,
                            0.0e+00, // on the surface -> min orbit, LKO
                            2.4920724702244101536052767187356948853e+03,
                            7.0e+04,
                            -2.7807874015748030506074428558349609375e6},
        EllipticalOrbitData{&Kerbin,
                            0.0e+00, // on the surface -> LKO
                            2.5176912500879116123542189598083496094e+03,
                            1.0e+05,
                            -2.7166153846153845079243183135986328125e6},
        EllipticalOrbitData{&Kerbin,
                            0.0e+00, // on the surface -> KEO
                            3.1676052523016251143417321145534515381e+03,
                            2.86333406e+06,
                            -8.6913848279557900968939065933227539062e5},
        EllipticalOrbitData{&Kerbin,
                            7.0e+04, // min orbit, LKO -> LKO
                            2.3208767986006064347748178988695144653e+03,
                            1.0e+05,
                            -2.5778102189781023189425468444824218750e6},
        EllipticalOrbitData{&Kerbin,
                            7.0e+04, // min orbit, LKO -> KEO
                            2.9720785896382690225436817854642868042e+03,
                            2.86333406e+06,
                            -8.5441920462630107067525386810302734375e5},
        EllipticalOrbitData{&Kerbin,
                            1.0e+05, // LKO -> KEO
                            2.8971987833458042587153613567352294922e+03,
                            2.86333406e+06,
                            -8.4826246203265280928462743759155273438e5}));

INSTANTIATE_TEST_CASE_P(
    Earth, EllipticalOrbitTest,
    testing::Values(
        EllipticalOrbitData{&Earth,
                            0.0e+00, // on the surface -> min orbit, LEO
                            7.9541790227209166914690285921096801758e+03,
                            1.6e+05,
                            -3.0860329107934944331645965576171875000e7},
        EllipticalOrbitData{&Earth,
                            0.0e+00, // on the surface -> LEO
                            7.9809808103873447180376388132572174072e+03,
                            2.5e+05,
                            -3.0646783722796164453029632568359375000e7},
        EllipticalOrbitData{&Earth,
                            0.0e+00, // on the surface -> GEO / GSO
                            1.0419539570032044139225035905838012695e+04,
                            3.5786e+07,
                            -8.2114086449499027803540229797363281250e6},
        EllipticalOrbitData{&Earth, 1.6e+05, // min orbit, LEO -> LEO
                            7.8346785891046356482547707855701446533e+03,
                            2.5e+05,
                            -3.0274355981007594615221023559570312500e7},
        EllipticalOrbitData{&Earth, 1.6e+05, // min orbit, LEO -> GEO / GSO
                            1.0274338743499216434429399669170379639e+04,
                            3.5786e+07,
                            -8.1844319702103761956095695495605468750e6},
        EllipticalOrbitData{&Earth, 2.5e+05, // LEO -> GEO / GSO
                            1.0194929816018779092701151967048645020e+04,
                            3.5786e+07,
                            -8.1693353405801141634583473205566406250e6}));

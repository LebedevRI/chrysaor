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

#include "CelestialBody.hpp"
#include "Atmosphere.hpp"             // for Atmosphere
#include "Curve/AbstractCurve.hpp"    // for AbstractCurve
#include "Curve/LinearCurvePoint.hpp" // for LinearCurvePoint
#include <gtest/gtest.h>              // for Message, TestPartResult, TestP...

TEST(CelestialBodyTest, TestConstructor) {
  ASSERT_NO_THROW({ CelestialBody foo; });
  ASSERT_NO_THROW({ CelestialBody foo(123.456, 6000.0); });
  ASSERT_NO_THROW({ CelestialBody foo(123.456, 6000.0, 246814.341); });
}

TEST(CelestialBodyTest, TestMuGetter) {
  const double mu = 2348634811.5235423;

  CelestialBody foo(mu, 0.0);

  ASSERT_DOUBLE_EQ(mu, foo.mu_);
}

TEST(CelestialBodyTest, TestRGetter) {
  const double R = 600000.0;

  CelestialBody foo(0.0, R);

  ASSERT_DOUBLE_EQ(R, foo.R_);
}

TEST(CelestialBodyTest, TestTrotGetter) {
  const double Trot = 23479.42431;

  CelestialBody foo(0.0, 0.0, Trot);

  ASSERT_DOUBLE_EQ(Trot, foo.Trot_);
}

TEST(CelestialBodyTest, TestAtmosphere) {
  auto atmPressure =
      AbstractCurve<LinearCurvePoint>({LinearCurvePoint(0.0, 101325)});
  auto atmTemperature =
      AbstractCurve<LinearCurvePoint>({LinearCurvePoint(0.0, 282.5)});

  Atmosphere foo_atm(&atmPressure, &atmTemperature);

  CelestialBody foo(0.0, 0.0, 0.0, &foo_atm);

  ASSERT_DOUBLE_EQ(101325, foo.atmosphere_->Pressure(0));
  ASSERT_DOUBLE_EQ(282.5, foo.atmosphere_->Temperature(0));
  ASSERT_DOUBLE_EQ(1.2494776887307841, foo.atmosphere_->Density(0));
}

TEST(CelestialBodyTest, TestGravitationalAcceleration) {
  CelestialBody Earth(3.986004418e+14, 6378136.6);

  const double g_0 = Earth.GravitationalAcceleration(0.0);
  ASSERT_NEAR(9.80665, g_0, 1.0e-02);

  const double g_1km = Earth.GravitationalAcceleration(1.0e+03);
  ASSERT_GT(g_0, g_1km);

  const double g_10km = Earth.GravitationalAcceleration(1.0e+04);
  ASSERT_GT(g_0, g_10km);
  ASSERT_GT(g_1km, g_10km);

  const double g_100km = Earth.GravitationalAcceleration(1.0e+05);
  ASSERT_GT(g_0, g_100km);
  ASSERT_GT(g_1km, g_10km);
  ASSERT_GT(g_10km, g_100km);
}

TEST(CelestialBodyTest, TestEquatorialSpeed) {
  CelestialBody Earth(3.986004418e+14, 6378136.6, 86164.098903691);

  const double equator = Earth.EquatorialSpeed();
  ASSERT_NEAR(465.1, equator, 1.0e-02);
}

TEST(CelestialBodyTest, TestSpeedAtLat) {
  CelestialBody Earth(3.986004418e+14, 6378136.6, 86164.098903691);

  const double equator = Earth.EquatorialSpeed();
  const double s_0deg = Earth.EquatorialSpeed(0.0);
  ASSERT_NEAR(465.1, equator, 1.0e-02);
  ASSERT_NEAR(465.1, s_0deg, 1.0e-02);
  ASSERT_DOUBLE_EQ(equator, s_0deg);

  const double s_2859deg = Earth.EquatorialSpeed(28.59);
  ASSERT_NEAR(408.40, s_2859deg, 1.0e-01);

  const double s_90deg = Earth.EquatorialSpeed(90.0);
  ASSERT_NEAR(0.0, s_90deg, 1.0e-13);
  ASSERT_LT(s_90deg, s_2859deg);
  ASSERT_LT(s_90deg, s_0deg);

  const double s_minus90deg = Earth.EquatorialSpeed(-90.0);
  ASSERT_NEAR(0.0, s_minus90deg, 1.0e-13);
  ASSERT_NEAR(s_90deg, s_minus90deg, 1.0e-13);
  ASSERT_LT(s_minus90deg, s_2859deg);
  ASSERT_LT(s_minus90deg, s_0deg);
}

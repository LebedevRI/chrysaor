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

#include "Atmosphere.hpp"
#include <gtest/gtest.h> // for ASSERT_NO_THROW, TEST

extern AbstractCurve<LinearCurvePoint> *atmPressure;
extern AbstractCurve<LinearCurvePoint> *atmTemperature;

TEST(AtmosphereTest, TestConstructor) {
  ASSERT_NO_THROW({ Atmosphere Earth(atmPressure, atmTemperature); });
}

TEST(AtmosphereTest, TestPressure) {
  Atmosphere Earth(atmPressure, atmTemperature);

  for (auto i = 0; i <= 185; i++) {
    ASSERT_NO_THROW({ (void)Earth.Pressure(i); });
    ASSERT_EQ((*atmPressure)[i], Earth.Pressure(i));
  }
}

TEST(AtmosphereTest, TestTemperature) {
  Atmosphere Earth(atmPressure, atmTemperature);

  for (auto i = 0; i <= 185; i++) {
    ASSERT_NO_THROW({ (void)Earth.Temperature(i); });
    ASSERT_EQ((*atmTemperature)[i], Earth.Temperature(i));
  }
}

TEST(AtmosphereTest, TestDensity) {
  Atmosphere Earth(atmPressure, atmTemperature);

  for (auto i = 0; i <= 185; i++) {
    ASSERT_NO_THROW({ (void)Earth.Density(i); });
  }
}

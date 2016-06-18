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

#include "IdealGas.hpp"
#include <gtest/gtest.h> // for AssertHelper, TEST, ASSERT_DOUBLE_EQ, ASSER...

TEST(IdealGasTest, TestDensity) {
  // IUPAC
  const double gas0 = IdealGas::Density(100000.0, 273.15);
  ASSERT_NEAR(1.2754, gas0, 1.0e-4);
}

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

#include "FluidDynamics.hpp"
#include "IdealGas.hpp"
#include <gtest/gtest.h> // for ASSERT_DOUBLE_EQ, TEST
#include <iomanip>       // for operator<<

TEST(FluidDynamicsTest, TestQ) {
  const double Q0 = FluidDynamics::DynamicPressure(1.2754, 0.0);
  ASSERT_DOUBLE_EQ(0.0, Q0);

  // mach 1
  const double Qm1 = FluidDynamics::DynamicPressure(1.2041, 343.21);
  ASSERT_NEAR(70920.0, Qm1, 1.0e+01);
  ASSERT_GT(Qm1, Q0);

  const double Qm1_2 = FluidDynamics::DynamicPressure(
      IdealGas::Density(101325.0, 293.15), 343.21);
  ASSERT_NEAR(70920.0, Qm1_2, 1.0e+01);
  ASSERT_NEAR(Qm1, Qm1_2, 1.0e-00);
  ASSERT_GT(Qm1_2, Q0);
}

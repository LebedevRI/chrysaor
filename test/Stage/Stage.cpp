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

#include "src/Stage.hpp" // for Stage
#include <cstddef>       // for size_t
#include <gtest/gtest.h> // for ASSERT_DOUBLE_EQ, AssertHelper, TEST
#include <iomanip>       // for operator<<

TEST(Stage, TestStageDm_Thrust) {
  const std::size_t thrust = 1000; // [N]
  const std::size_t isp1 = 200;    // [s]

  Stage foo(0, thrust, 0, isp1, 0, 0);
  auto dm1 = foo.dm(); // [kg/s]

  Stage bar(0, 2 * thrust, 0, isp1, 0, 0);
  auto dm2 = bar.dm(); // [kg/s]

  ASSERT_NE(dm1, dm2);
  ASSERT_LT(dm1, dm2);

  ASSERT_DOUBLE_EQ(2.0 * dm1, dm2);
}

TEST(Stage, TestStageDm_Isp1) {
  const std::size_t thrust = 1000; // [N]
  const std::size_t isp1 = 200;    // [s]

  Stage foo(0, thrust, 0, isp1, 0, 0);
  auto dm1 = foo.dm(); // [kg/s]

  Stage bar(0, thrust, 0, 2 * isp1, 0, 0);
  auto dm2 = bar.dm(); // [kg/s]

  ASSERT_NE(dm1, dm2);
  ASSERT_GT(dm1, dm2);
}

TEST(Stage, TestStageMaxT_Thrust) {
  const std::size_t thrust = 1000; // [N]
  const std::size_t isp1 = 200;    // [s]
  const std::size_t fm = 200;      // [kg]

  Stage foo(0, thrust, 0, isp1, fm, 0);
  auto maxT1 = foo.maxT(); // [s]

  Stage bar(0, 2 * thrust, 0, isp1, fm, 0);
  auto maxT2 = bar.maxT(); // [s]

  ASSERT_NE(maxT1, maxT2);
  ASSERT_GT(maxT1, maxT2);

  ASSERT_DOUBLE_EQ(maxT1, 2.0 * maxT2);
}

TEST(Stage, TestStageMaxT_Isp1) {
  const std::size_t thrust = 1000; // [N]
  const std::size_t isp1 = 200;    // [s]
  const std::size_t fm = 200;      // [kg]

  Stage foo(0, thrust, 0, isp1, fm, 0);
  auto maxT1 = foo.maxT(); // [s]

  Stage bar(0, thrust, 0, 2 * isp1, fm, 0);
  auto maxT2 = bar.maxT(); // [s]

  ASSERT_NE(maxT1, maxT2);
  ASSERT_LT(maxT1, maxT2);
}

TEST(Stage, TestStageMaxT_Fm) {
  const std::size_t thrust = 1000; // [N]
  const std::size_t isp1 = 200;    // [s]
  const std::size_t fm = 200;      // [kg]

  Stage foo(0, thrust, 0, isp1, fm, 0);
  auto maxT1 = foo.maxT(); // [s]

  Stage bar(0, thrust, 0, isp1, 2 * fm, 0);
  auto maxT2 = bar.maxT(); // [s]

  ASSERT_NE(maxT1, maxT2);
  ASSERT_LT(maxT1, maxT2);
}

TEST(Stage, TestStageTWR) {
  const std::size_t launchMass = 100; // [kg]
  const std::size_t thrust = 1000;    // [N]

  Stage foo(launchMass, thrust, 0, 0, 0, 0);
  auto TWR1 = foo.TWR(); // [const]

  Stage bar(launchMass, 2 * thrust, 0, 0, 0, 0);
  auto TWR2 = bar.TWR(); // [const]

  ASSERT_NE(TWR1, TWR2);
  ASSERT_LT(TWR1, TWR2);

  ASSERT_DOUBLE_EQ(2.0 * TWR1, TWR2);
}

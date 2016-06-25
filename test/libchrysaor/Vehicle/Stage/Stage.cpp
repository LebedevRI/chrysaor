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

#include "Vehicle/Stage.hpp"  // for Stage
#include "Vehicle/Engine.hpp" // for Engine
#include <gtest/gtest.h>      // for ASSERT_DOUBLE_EQ, AssertHelper, TEST
#include <iomanip>            // for operator<<

TEST(Engine, TestConstructor) {
  ASSERT_NO_THROW({ Stage foo; });

  ASSERT_NO_THROW({ Stage foo(Engine(1.0e+06, 250), 1000, 9500); });
}

TEST(Stage, TestStageMaxT) {
  Stage foo(Engine(980665, 100), 0, 1.0e+03);

  ASSERT_EQ(1.0, foo.maxT());
}

TEST(Stage, TestStageMaxT_Thrust) {
  Stage foo(Engine(1.0e+06, 250), 0, 1000);
  Stage bar(Engine(2.0e+06, 250), 0, 1000);

  ASSERT_NE(foo.maxT(), bar.maxT());
  ASSERT_GT(foo.maxT(), bar.maxT());
  ASSERT_DOUBLE_EQ(foo.maxT(), 2.0 * bar.maxT());
}

TEST(Stage, TestStageMaxT_Isp) {
  Stage foo(Engine(1.0e+06, 250), 0, 1000);
  Stage bar(Engine(1.0e+06, 500), 0, 1000);

  ASSERT_NE(foo.maxT(), bar.maxT());
  ASSERT_LT(foo.maxT(), bar.maxT());
  ASSERT_DOUBLE_EQ(2.0 * foo.maxT(), bar.maxT());
}

TEST(Stage, TestStageMaxT_Fm) {
  Stage foo(Engine(1.0e+06, 250), 0, 1000);
  Stage bar(Engine(1.0e+06, 250), 0, 2000);

  ASSERT_NE(foo.maxT(), bar.maxT());
  ASSERT_LT(foo.maxT(), bar.maxT());
  ASSERT_DOUBLE_EQ(2.0 * foo.maxT(), bar.maxT());
}

TEST(Stage, TestStageTWR) {
  Stage foo(Engine(980665, 0), 10000, 0);

  ASSERT_DOUBLE_EQ(10, foo.TWR());
}

TEST(Stage, TestStageTWR_Thrust) {
  Stage foo(Engine(1.0e+06, 0), 9.0e+04, 0);
  Stage bar(Engine(2.0e+06, 0), 9.0e+04, 0);

  ASSERT_NE(foo.TWR(), bar.TWR());
  ASSERT_LT(foo.TWR(), bar.TWR());
  ASSERT_DOUBLE_EQ(2.0 * foo.TWR(), bar.TWR());
}

TEST(Stage, TestStageTWR_Isp) {
  Stage foo(Engine(1.0e+06, 250), 9.0e+04, 0);
  Stage bar(Engine(1.0e+06, 500), 9.0e+04, 0);

  ASSERT_EQ(foo.TWR(), bar.TWR());
}

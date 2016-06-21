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

#include "Curve/AbstractCurve.hpp"    // for AbstractCurve
#include "Curve/LinearCurvePoint.hpp" // for LinearCurvePoint
#include <gtest/gtest.h>              // for InitGoogleTest, RUN_ALL_TESTS
#include <vector>                     // for vector, allocator

AbstractCurve<LinearCurvePoint> *atmPressure;
AbstractCurve<LinearCurvePoint> *atmTemperature;

int main(int argc, char **argv) {
  std::vector<LinearCurvePoint> presVec;
  presVec.push_back(LinearCurvePoint(0, 101325));
  presVec.push_back(LinearCurvePoint(32500, 1000));
  presVec.push_back(LinearCurvePoint(80000, 1));
  presVec.push_back(LinearCurvePoint(140000, 0));

  atmPressure =
      new AbstractCurve<LinearCurvePoint>(presVec.begin(), presVec.end());

  std::vector<LinearCurvePoint> tempVec;
  tempVec.push_back(LinearCurvePoint(0, 282.5));
  tempVec.push_back(LinearCurvePoint(20000, 215));
  tempVec.push_back(LinearCurvePoint(50000, 268));
  tempVec.push_back(LinearCurvePoint(90000, 192));
  tempVec.push_back(LinearCurvePoint(140000, 560));

  atmTemperature =
      new AbstractCurve<LinearCurvePoint>(tempVec.begin(), tempVec.end());

  ::testing::InitGoogleTest(&argc, argv);
  int ret = RUN_ALL_TESTS();

  delete atmTemperature;
  delete atmPressure;

  return ret;
}

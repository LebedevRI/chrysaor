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

#include "Vehicle/Engine.hpp"
#include "Curve/AbstractCurve.hpp"    // for AbstractCurve
#include "Curve/LinearCurvePoint.hpp" // for LinearCurvePoint
#include <gtest/gtest.h>              // for Test, Message, TestPartResult

TEST(Engine, TestConstructor) {
  ASSERT_NO_THROW({ Engine foo; });

  ASSERT_NO_THROW({
    Engine foo(1.0e+03, 250);
    ASSERT_EQ(1.0e+03, foo.thrust(0));
  });

  ASSERT_NO_THROW({
    AbstractCurve<LinearCurvePoint> thrust({LinearCurvePoint(0, 980665)});
    AbstractCurve<LinearCurvePoint> isp({LinearCurvePoint(0, 1.0e+05)});
    Engine foo(thrust, isp);
  });

  ASSERT_NO_THROW({
    AbstractCurve<LinearCurvePoint> thrust(
        {LinearCurvePoint(101325, 980665), LinearCurvePoint(0, 9.80665)});
    AbstractCurve<LinearCurvePoint> isp(
        {LinearCurvePoint(101325, 100), LinearCurvePoint(0, 1000)});
    Engine foo(thrust, isp);
  });
}

TEST(Engine, TestThrust) {
  AbstractCurve<LinearCurvePoint> thrust(
      {LinearCurvePoint(101325, 1.860e+06), LinearCurvePoint(0, 2.279e+06)});
  AbstractCurve<LinearCurvePoint> isp(
      {LinearCurvePoint(101325, 366), LinearCurvePoint(0, 453)});
  Engine foo(thrust, isp);

  ASSERT_DOUBLE_EQ(1.860e+06, foo.thrust(101325));
  ASSERT_DOUBLE_EQ(2.279e+06, foo.thrust(0));

  // !!! linear thrust curve
  ASSERT_DOUBLE_EQ((1.860e+06 + 2.279e+06) / 2.0, foo.thrust(101325.0 / 2.0));
}

TEST(Engine, TestIsp) {
  AbstractCurve<LinearCurvePoint> thrust(
      {LinearCurvePoint(101325, 1.860e+06), LinearCurvePoint(0, 2.279e+06)});
  AbstractCurve<LinearCurvePoint> isp(
      {LinearCurvePoint(101325, 366), LinearCurvePoint(0, 453)});
  Engine foo(thrust, isp);

  ASSERT_DOUBLE_EQ(366, foo.isp(101325));
  ASSERT_DOUBLE_EQ(453, foo.isp(0));

  // !!! linear isp curve
  ASSERT_DOUBLE_EQ((366 + 453) / 2.0, foo.isp(101325.0 / 2.0));
}

TEST(Engine, TestExhaustVelocity) {
  AbstractCurve<LinearCurvePoint> thrust({LinearCurvePoint(0, 2.279e+06)});
  AbstractCurve<LinearCurvePoint> isp({LinearCurvePoint(0, 453)});
  Engine foo(thrust, isp);

  ASSERT_NEAR(4442, foo.exhaustVelocity(0), 1.0);
}

TEST(Engine, TestConstMassFlow) {
  AbstractCurve<LinearCurvePoint> thrust(
      {LinearCurvePoint(101325, 845000), LinearCurvePoint(0, 914000)});
  AbstractCurve<LinearCurvePoint> isp(
      {LinearCurvePoint(101325, 282), LinearCurvePoint(0, 311)});
  Engine foo(thrust, isp);

  ASSERT_NEAR(foo.massFlow(101325), foo.massFlow(0), 1.0e+01);
}

TEST(Engine, TestThrust_MassFlow) {
  Engine foo(1.0e+06, 250);
  Engine bar(2.0e+06, 250);

  ASSERT_NE(foo.massFlow(0), bar.massFlow(0));
  ASSERT_LT(foo.massFlow(0), bar.massFlow(0));
  ASSERT_DOUBLE_EQ(2.0 * foo.massFlow(0), bar.massFlow(0));
}

TEST(Engine, TestIsp_MassFlow) {
  Engine foo(1.0e+06, 250);
  Engine bar(1.0e+06, 500);

  ASSERT_NE(foo.massFlow(0), bar.massFlow(0));
  ASSERT_GT(foo.massFlow(0), bar.massFlow(0));
  ASSERT_DOUBLE_EQ(foo.massFlow(0), 2.0 * bar.massFlow(0));
}

TEST(Engine, TestThrust_ExhaustVelocity) {
  Engine foo(1.0e+06, 250);
  Engine bar(2.0e+06, 250);

  ASSERT_EQ(foo.exhaustVelocity(0), bar.exhaustVelocity(0));
}

TEST(Engine, TestIsp_ExhaustVelocity) {
  Engine foo(1.0e+06, 250);
  Engine bar(1.0e+06, 500);

  ASSERT_NE(foo.exhaustVelocity(0), bar.exhaustVelocity(0));
  ASSERT_LT(foo.exhaustVelocity(0), bar.exhaustVelocity(0));
  ASSERT_DOUBLE_EQ(2.0 * foo.exhaustVelocity(0), bar.exhaustVelocity(0));
}

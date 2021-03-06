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
#include <algorithm>                  // for max, min
#include <cstddef>                    // for size_t
#include <gtest/gtest.h>              // for ASSERT_EQ, ASSERT_NO_THROW, TEST
#include <map>                        // for map, _Rb_tree_iterator, map<>:...
#include <utility>                    // for pair
#include <vector>                     // for vector, allocator

TEST(LinearCurveTest, TestConstructor) {
  {
    ASSERT_NO_THROW(AbstractCurve<LinearCurvePoint> foo;);

    AbstractCurve<LinearCurvePoint> foo;
    ASSERT_EQ(foo.size(), 0);
  }

  const double x0 = 0.0;
  const double y0 = 0.0;
  const double x1 = 1.0;
  const double y1 = 1.0;

  LinearCurvePoint p1(x0, y0);
  LinearCurvePoint p2(x1, y1);

  {
    ASSERT_NO_THROW(AbstractCurve<LinearCurvePoint> bar({p1, p2}););

    AbstractCurve<LinearCurvePoint> bar({p1, p2});
    ASSERT_EQ(bar.size(), 2);
  }

  std::vector<LinearCurvePoint> vec;
  vec.push_back(p1);
  vec.push_back(p2);

  {
    ASSERT_NO_THROW(
        AbstractCurve<LinearCurvePoint> baz(vec.begin(), vec.end()););

    AbstractCurve<LinearCurvePoint> baz(vec.begin(), vec.end());
    ASSERT_EQ(baz.size(), 2);
  }
}

TEST(LinearCurveTest, TestGetter) {
  const double x0 = 0.0;
  const double y0 = 2.0;
  const double x1 = 3.0;
  const double y1 = 4.0;

  LinearCurvePoint p1(x0, y0);
  LinearCurvePoint p2(x1, y1);

  AbstractCurve<LinearCurvePoint> bar({p1, p2});
  ASSERT_EQ(bar.size(), 2);

  ASSERT_EQ(y0, bar[x0 - x1]);
  ASSERT_EQ(y0, bar[x0]);

  ASSERT_EQ(y1, bar[x1]);
  ASSERT_EQ(y1, bar[2 * x1]);

  // WIP
  ASSERT_EQ((y0 + y1) / 2.0, bar[(x0 + x1) / 2.0]);
}

TEST(LinearCurveTest, TestSmall) {
  const double x0 = 0.0;
  const double y0 = 2.0;

  LinearCurvePoint p1(x0, y0);

  AbstractCurve<LinearCurvePoint> bar({p1});
  ASSERT_EQ(bar.size(), 1);

  ASSERT_EQ(y0, bar[-1.0]);
  ASSERT_EQ(y0, bar[x0]);
  ASSERT_EQ(y0, bar[1.0]);
}

TEST(LinearCurveTest, TestBigger) {
  const double x0 = 0.0;
  const double y0 = 2.0;
  const double x1 = 3.0;
  const double y1 = 4.0;

  const std::size_t numPts = 101;

  std::map<double, double> testPts;
  std::vector<LinearCurvePoint> ptsVec;
  for (std::size_t i = 0; i < numPts; i++) {
    const double t = std::min(
        std::max(static_cast<double>(i) / static_cast<double>(numPts - 1), 0.0),
        1.0);

    const double x = (1.0 - t) * x0 + t * x1;
    const double y = (1.0 - t) * y0 + t * y1;

    testPts[x] = y;

    LinearCurvePoint p(x, y);
    ptsVec.push_back(p);
  }

  ASSERT_EQ(ptsVec.size(), numPts);

  AbstractCurve<LinearCurvePoint> bar(ptsVec.begin(), ptsVec.end());

  ASSERT_EQ(bar.size(), numPts);
  ASSERT_EQ(bar.size(), ptsVec.size());

  ASSERT_EQ(y0, bar[x0 - x1]);
  ASSERT_EQ(y0, bar[x0]);

  ASSERT_EQ(y1, bar[x1]);
  ASSERT_EQ(y1, bar[2 * x1]);

  for (auto it = testPts.begin(); it != testPts.end(); ++it) {
    ASSERT_EQ(it->second, bar[it->first]);
  }

  ASSERT_EQ(bar.size(), numPts);
}

TEST(LinearCurveTest, TestSlike) {
  std::vector<LinearCurvePoint> testVec;
  testVec.push_back(LinearCurvePoint(0, 100));
  testVec.push_back(LinearCurvePoint(5, 150));
  testVec.push_back(LinearCurvePoint(10, 50));
  testVec.push_back(LinearCurvePoint(15, 200));

  AbstractCurve<LinearCurvePoint> foo(testVec.begin(), testVec.end());

  for (auto i = -10; i <= 25; i++) {
    ASSERT_NO_THROW({ (void)foo[i]; });
  }
}

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

#include "LaunchSite.hpp"
#include "CelestialBody.hpp"
#include <cstddef>
#include <gtest/gtest.h>

TEST(LaunchSiteTest, TestLatitudeGetter) {
  double lattitude = 23.484013324312;
  LaunchSite foo(lattitude, 0.0, 0);
  EXPECT_EQ(foo.Latitude(), lattitude);
}

TEST(LaunchSiteTest, TestLongitudeGetter) {
  double longitude = 42.12345362145531;
  LaunchSite foo(0.0, longitude, 0);
  EXPECT_EQ(foo.Longitude(), longitude);
}

TEST(LaunchSiteTest, TestLatitudegetter) {
  std::size_t altitude = 123.0;
  LaunchSite foo(0.0, 0.0, altitude);
  EXPECT_EQ(foo.Altitude(), altitude);
}

TEST(LaunchSiteTest, TestParentBody) {
  CelestialBody parentBody;
  LaunchSite foo(&parentBody, 0.0, 0.0, 0.0);
  EXPECT_EQ(&parentBody, foo.Body());
}

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
#include <cstddef>

double LaunchSite::Latitude() const { return latitude_; }

double LaunchSite::Longitude() const { return longitude_; }

std::size_t LaunchSite::Altitude() const { return altitude_; }

LaunchSite::LaunchSite(double latitude, double longitude, std::size_t altitude)
    : latitude_(latitude), longitude_(longitude), altitude_(altitude) {}

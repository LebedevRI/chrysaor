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

#include <cstddef>

class LaunchSite {
private:
  /**
  * @brief latitude of the launch site [deg]
  */
  double latitude;

  /**
  * @brief longitude of the launch site [deg]
  */
  double longitude;

  /**
  * @brief launch site altitude ASL [m]
  */
  std::size_t altitude;

public:
  /**
   * @brief returns latitude of the launch site [deg]
   *
   * @return double latitude
   */
  double Latitude() const { return this->latitude; }

  /**
   * @brief returns longitude of the launch site [deg]
   *
   * @return double longitude
   */
  double Longitude() const { return this->longitude; }

  /**
   * @brief returns launch site altitude ASL [m]
   *
   * @return std::size_t altitude
   */
  std::size_t Altitude() const { return this->altitude; }

  LaunchSite(double latitude, double longitude, std::size_t altitude)
      : latitude(latitude), longitude(longitude), altitude(altitude) {}
};

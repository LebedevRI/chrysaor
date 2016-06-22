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

#pragma once

#include <cstddef>
class CelestialBody;

class LaunchSite {
private:
  /**
   * @brief the body on which this site is located
   *
   */
  CelestialBody *body_;

  /**
  * @brief latitude of the launch site [deg]
  */
  double latitude_;

  /**
  * @brief longitude of the launch site [deg]
  */
  double longitude_;

  /**
  * @brief launch site altitude ASL [m]
  */
  std::size_t altitude_;

public:
  /**
   * @brief returns pointer to the body on which this lauchsite is located
   *
   * @return CelestialBody *
   */
  CelestialBody *Body() const;

  /**
   * @brief returns latitude of the launch site [deg]
   *
   * @return double latitude
   */
  double Latitude() const;

  /**
   * @brief returns longitude of the launch site [deg]
   *
   * @return double longitude
   */
  double Longitude() const;

  /**
   * @brief returns launch site altitude ASL [m]
   *
   * @return std::size_t altitude
   */
  std::size_t Altitude() const;

  LaunchSite(double latitude, double longitude, std::size_t altitude);
  LaunchSite(CelestialBody *parentBody, double latitude, double longitude,
             std::size_t altitude);
};

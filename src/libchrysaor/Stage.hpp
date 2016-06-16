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

/**
* @brief std gravity asl [m/s2]
* http://physics.nist.gov/cgi-bin/cuu/Value?gn
*/
static const double g0 = 9.80665;

class Stage {
private:
  /**
  * @brief launch mass [kg]
  */
  std::size_t launchMass_;

  /**
  * @brief thrust ASL [N] [kg * m/s^2]
  */
  std::size_t thrust_;

  /**
  * @brief isp vacuum [s]
  */
  std::size_t isp0_;

  /**
  * @brief isp asl [s]
  */
  std::size_t isp1_;

  /**
  * @brief stage fuel mass [kg]
  */
  std::size_t fm_;

  /**
  * @brief reference cross section area [m^2]
  */
  std::size_t A_;

public:
  /**
   * @brief returns mass flow rate [kg/s]
   *
   * @return double dm [kg/s]
   */
  double dm() const;

  /**
   * @brief returns expected stage burn time [s]
   *
   * @return double maxT [s]
   */
  double maxT() const;

  /**
   * @brief returns TWR at launch
   *
   * @return double TWR [const]
   */
  double TWR() const;

  Stage(std::size_t launchMass, std::size_t thrust, std::size_t isp0,
        std::size_t isp1, std::size_t fm, std::size_t A);
};

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

#include "Vehicle/Engine.hpp"

/**
 * @brief provides all the necessary functionality to model a vehicle's stage
 */
class Stage {
private:
  Engine engine_;

  /**
  * @brief total mass of the stage [kg]
  */
  double massTotal_;

  /**
  * @brief stage fuel mass [kg]
  */
  double fuelMass_;

public:
  /**
   * @brief returns expected stage burn time [s]
   *
   * @param p atmospheric pressure
   * @return double maxT [s]
   */
  double maxT(double p = 0.0) const;

  /**
   * @brief returns TWR
   *
   * @param p atmospheric pressure
   * @return double TWR [const]
   */
  double TWR(double p = 0.0) const;

  /**
   * @brief dummy constructor
   *
   */
  Stage();

  /**
   * @brief constructs stage with given parameters
   *
   * @param engine engine object
   * @param totalMass *total* mass of the stage [kg]
   * @param fuelMass mass of fuel in *this* stage [kg]
   */
  Stage(Engine engine, double totalMass, double fuelMass);
};

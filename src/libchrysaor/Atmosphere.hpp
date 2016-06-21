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

#include "Curve/AbstractCurve.hpp"    // IWYU pragma: keep
#include "Curve/LinearCurvePoint.hpp" // IWYU pragma: keep

/**
 * @brief defines atmosphere parameters
 *
 */
class Atmosphere {
protected:
  /**
   * @brief pressure curve
   *
   * Key   - altitude [m]
   * Value - atmospheric pressure [Pa]
   */
  AbstractCurve<LinearCurvePoint> *pressure_;

  /**
   * @brief temperature curve
   *
   * Key   - altitude [m]
   * Value - atmospheric temperature [K]
   */
  AbstractCurve<LinearCurvePoint> *temperature_;

public:
  /**
   * @brief atmospheric pressure at given altitude
   *
   * @param altitude distance from the surface of the parent body [m]
   * @return double pressure [Pa]
   */
  double Pressure(double altitude) const;

  /**
   * @brief atmospheric temperature at given altitude
   *
   * @param altitude distance from the surface of the parent body [m]
   * @return double temperature [K]
   */
  double Temperature(double altitude) const;

  /**
   * @brief atmospheric density at given altitude
   *
   * @param altitude distance from the surface of the parent body [m]
   * @return double density [kg/m^3]
   */
  double Density(double altitude) const;

  /**
   * @brief constructor
   *
   * @param atmPressure pressure curve, [m] => [Pa]
   * @param atmTemperature temperature curve, [m] => [K]
   */
  Atmosphere(AbstractCurve<LinearCurvePoint> *atmPressure,
             AbstractCurve<LinearCurvePoint> *atmTemperature);
};

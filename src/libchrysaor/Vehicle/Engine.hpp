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

#include "Curve/AbstractCurve.hpp"    // for AbstractCurve
#include "Curve/LinearCurvePoint.hpp" // for LinearCurvePoint

/**
* @brief std gravity asl [m/s^2]
* http://physics.nist.gov/cgi-bin/cuu/Value?gn
*/
static const double g0 = 9.80665;

/**
 * @brief provides all the necessary functionality to model an engine
 *
 * I'm using LinearCurvePoint because engine properties seem to be in
 * linear relationship with atmospheric pressure.
 */
class Engine {
private:
  /**
  * @brief thrust curve [Pa => N] [Pa => kg * m/s^2]
  */
  const AbstractCurve<LinearCurvePoint> thrust_;

  /**
  * @brief isp curve [Pa => s]
  */
  const AbstractCurve<LinearCurvePoint> isp_;

public:
  /**
   * @brief returns thrust [N] [kg * m/s^2]
   *
   * @param p atmospheric pressure
   * @return double engine thrust at given pressure [N] [kg * m/s^2]
   */
  double thrust(double p = 0.0) const;

  /**
   * @brief returns isp [s]
   *
   * @param p atmospheric pressure
   * @return double engine isp at given pressure [s]
   */
  double isp(double p = 0.0) const;

  /**
   * @brief returns Effective exhaust velocity [m/s]
   *
   * \f$V_e = I_{sp} \cdot g_0\f$
   *
   * @param p atmospheric pressure
   * @return double effective exhaust velocity at given pressure [m/s]
   */
  double exhaustVelocity(double p = 0.0) const;

  /**
   * @brief returns mass flow rate [kg/s]
   *
   * \f$\dot{m}=\frac{F_{thrust}}{V_e}=\frac{F_{thrust}}{I_{sp}\cdot g_0} \f$
   *
   * @param p atmospheric pressure
   * @return double mass flow rate at given pressure [kg/s]
   */
  double massFlow(double p = 0.0) const;

  /**
   * @brief dummy constructor
   *
   */
  Engine();

  /**
   * @brief constructs engine with only one datapoint, assumed to be vacuum
   *
   * @param thrust0 engine-produced thrust, vac [N] [kg * m/s^2]
   * @param isp0 engine specific impulse, vac [s]
   */
  Engine(double thrust0, double isp0);

  /**
   * @brief constructs engine with data-points provided as curves
   *
   * @param thrust engine-produced thrust [Pa => N] [Pa => kg * m/s^2]
   * @param isp engine specific impulse [Pa => s]
   */
  Engine(AbstractCurve<LinearCurvePoint> thrust,
         AbstractCurve<LinearCurvePoint> isp);
};

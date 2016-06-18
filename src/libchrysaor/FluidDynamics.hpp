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

class FluidDynamics {
public:
  /**
   * @brief returns dynamic pressure \f$q\f$
   *
   * \f$ q = {{1\over{2}} \rho v^2} \f$, or \f$v=\sqrt{{2q}\over{\rho}}\f$
   *
   * @param rho fluid density [kg/m^3]
   * @param v fluid velocity [m/s]
   *
   * @see https://en.wikipedia.org/wiki/Dynamic_pressure
   *
   * @return double dynamic pressure [Pa]
   */
  static double DynamicPressure(double rho, double v);
};

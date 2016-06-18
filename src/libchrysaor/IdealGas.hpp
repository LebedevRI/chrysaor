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

class IdealGas {
public:
  /**
   * @brief specific gas constant for dry air [J/(kg*K)]
   *
   * @see https://en.wikipedia.org/wiki/Gas_constant#Specific_gas_constant
   */
  static const double Rspec;

  /**
   * @brief returns density \f$\rho\f$ of ideal gas with given (p, T)
   *
   * @param p absolute pressure [Pa]
   * @param T absolute temperature [K]
   *
   * \f$\rho = \frac{p}{R_{\rm specific} T} \f$
   *
   * @see https://en.wikipedia.org/wiki/Density_of_air
   *
   * @return double fluid density [kg/m^3]
   */
  static double Density(double p, double T);
};

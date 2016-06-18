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

#include "FluidDynamics.hpp"
#include <cassert> // for assert
#include <cmath>   // for pow

double FluidDynamics::DynamicPressure(double rho, double v) {
  assert(std::isfinite(rho));
  assert(rho >= 0.0);
  assert(std::isfinite(v));
  assert(v >= 0.0);

  assert(std::isfinite(std::pow(v, 2.0)));
  assert(std::isfinite(rho * std::pow(v, 2.0)));

  const double q = ((rho * std::pow(v, 2.0)) / 2.0);

  assert(std::isfinite(q));
  assert(q >= 0.0);

  return q;
}

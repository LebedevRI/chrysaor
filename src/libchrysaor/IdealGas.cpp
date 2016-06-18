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

#include "IdealGas.hpp"
#include <cassert> // for assert
#include <cmath>   // for pow

const double IdealGas::Rspec = 287.058;

double IdealGas::Density(double p, double T) {
  assert(std::isfinite(p));
  assert(std::isfinite(T));
  assert(std::isfinite(Rspec));
  assert(Rspec != 0.0);

  assert(T >= 0.0);
  assert(T != 0.0);

  assert(std::isfinite(Rspec * T));
  assert((Rspec * T) != 0.0);

  const double rho = ((p) / (Rspec * T));

  assert(std::isfinite(rho));
  assert(rho >= 0.0);

  return rho;
}

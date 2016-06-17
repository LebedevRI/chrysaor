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

#include "CelestialBody.hpp"
#include <cassert> // for assert
#include <cmath>   // for pow
#include <cstddef>

double CelestialBody::GravitationalAcceleration(double alt) const {
  assert(std::isfinite(R_));
  assert(R_ >= 0.0);
  assert(std::isfinite(mu_));
  assert(mu_ >= 0.0);

  assert(std::isfinite(alt));
  assert(alt >= 0.0);

  const double r = alt + R_;

  assert(std::isfinite(r));
  assert(r >= 0.0);
  assert(r != 0.0);

  assert(std::isfinite(std::pow(r, 2.0)));
  assert((std::pow(r, 2.0)) != 0.0);

  const double g = ((mu_) / (std::pow(r, 2.0)));

  assert(std::isfinite(g));
  assert(g >= 0.0);

  return g;
}

CelestialBody::CelestialBody()
    : parentBody_(NULL), orbit_(NULL), mu_(0.0), R_(0.0) {}

CelestialBody::CelestialBody(double mu, double R)
    : parentBody_(NULL), orbit_(NULL), mu_(mu), R_(R) {
  assert(std::isfinite(mu));
  assert(mu >= 0.0);
  assert(std::isfinite(R));
  assert(R >= 0.0);
}

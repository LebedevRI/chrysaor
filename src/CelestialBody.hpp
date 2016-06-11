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

#include <cassert> // for assert
#include <cmath>   // for pow
#include <cstddef>

class Orbit;

class CelestialBody {
private:
  /**
   * @brief the body around which this orbit is
   *
   */
  CelestialBody *parentBody_;

  /**
   * @brief orbit around the parent body
   *
   */
  Orbit *orbit_;

public:
  /**
   * @brief standard gravitational parameter [m^3/s^2]
   *
   * https://en.wikipedia.org/wiki/Standard_gravitational_parameter
   */
  const double mu_;

  /**
   * @brief body radius [m]
   *
   */
  const double R_;

  CelestialBody() : parentBody_(NULL), orbit_(NULL), mu_(0.0), R_(0.0) {}
  CelestialBody(double mu, double R)
      : parentBody_(NULL), orbit_(NULL), mu_(mu), R_(R) {
    assert(std::isfinite(mu));
    assert(mu >= 0.0);
    assert(std::isfinite(R));
    assert(R >= 0.0);
  }
};

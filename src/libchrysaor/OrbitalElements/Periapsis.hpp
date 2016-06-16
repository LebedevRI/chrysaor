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

#include "OrbitalElements/Apsis.hpp" // for Apsis

class CelestialBody;
class SemiMajorAxis;
class OrbitalEccentricity;

/**
 * @brief apoapsis class
 *
 * Extreme point of orbit, the orbit's nearest point
 *
 * \see https://en.wikipedia.org/wiki/Apsis
 */
class Periapsis : public Apsis {
public:
  operator double() const;

  ~Periapsis() {}

  /**
   * @brief creates Periapsis object from passed characteristics
   *
   * This 'creates' orbit's nearest point
   *
   * @param sma semi-major axis of the orbit [m]
   * @param ecc eccentricity of the orbit
   * @param parentBody the parent body
   */
  Periapsis(SemiMajorAxis sma, OrbitalEccentricity ecc,
            CelestialBody *parentBody);
};

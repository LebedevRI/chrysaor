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
 * Extreme point of orbit, the orbit's farthest point
 *
 * \see https://en.wikipedia.org/wiki/Apsis
 */
class Apoapsis : public Apsis {
public:
  operator double() const override;

  ~Apoapsis() override = default;

  /**
   * @brief creates Apoapsis object from passed characteristics
   *
   * This 'creates' orbit's farthest point
   *
   * @param sma semi-major axis of the orbit [m]
   * @param ecc eccentricity of the orbit
   * @param parentBody the parent body
   */
  Apoapsis(SemiMajorAxis sma, OrbitalEccentricity ecc,
           const CelestialBody *parentBody);
};

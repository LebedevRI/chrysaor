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

#include "src/OrbitalEccentricity.hpp" // for OrbitalEccentricity
#include "src/SemiMajorAxis.hpp"       // for SemiMajorAxis

class CelestialBody;

/**
 * @brief apsis class
 *
 * Extreme point of orbit
 *
 * \see https://en.wikipedia.org/wiki/Apsis
 */
class Apsis {
protected:
  /**
   * @brief the parent body
   *
   */
  CelestialBody *parentBody_;

  /**
   * @brief semi-major axis of the orbit [m]
   *
   */
  SemiMajorAxis sma_;

  /**
   * @brief eccentricity of the orbit
   *
   */
  OrbitalEccentricity ecc_;

public:
  /**
   * @brief radius of the orbit, in this Apsis [m]
   *
   * @return double
   */
  virtual operator double() const = 0;

  /**
   * @brief radius of the orbit, in this Apsis [m]
   *
   * @return double
   */
  double Radius() const;

  /**
   * @brief altitude, from the surface of the parent body, in this Apsis [m]
   *
   * @return double
   */
  double Altitude() const;

  virtual ~Apsis() {}

  /**
   * @brief creates Apsis object from passed characteristics
   *
   * @param sma semi-major axis of the orbit [m]
   * @param ecc eccentricity of the orbit
   * @param parentBody the parent body
   */
  Apsis(SemiMajorAxis sma, OrbitalEccentricity ecc, CelestialBody *parentBody)
      : parentBody_(parentBody), sma_(sma), ecc_(ecc) {}
};

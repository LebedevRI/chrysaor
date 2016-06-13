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

class CelestialBody;

/**
 * @brief orbital eccentricity class
 *
 * Orbital eccentricity is a parameter that determines the amount by which its
 * orbit around another body deviates from a
 * perfect circle.
 *
 * A value of 0 is a circular orbit, values between 0 and 1 form an elliptical
 * orbit, 1 is a parabolic escape orbit, and greater than 1 is a hyperbola.
 *
 * \f$e=\sqrt{1+{{2\epsilon h^2}\over{\mu^2}}}\f$
 *
 * \see https://en.wikipedia.org/wiki/Orbital_eccentricity
 */
class OrbitalEccentricity {
private:
  /**
   * @brief eccentricity of the orbit,
   *
   */
  double value_;

public:
  /**
   * @brief eccentricity of the orbit
   *
   * @return double
   */
  operator double() const;

  /**
   * @brief dummy constructor.
   *
   */
  OrbitalEccentricity();

  /**
   * @brief sets \f$e\f$ to the passed value
   *
   * @param eccentricity eccentricity of the orbit
   */
  OrbitalEccentricity(double eccentricity);

  /**
   * @brief calculates \f$e\f$ from given velocity vector and altitude.
   *
   * By definition, given 2 velocity's components, \f$V_x\f$ and \f$V_y\f$,
   * the velocity magnitude is: \f$v = \sqrt{V_x^2+V_y^2}\f$.
   *
   * FIXME
   *
   * See math/orbit/ecc.sage and math/orbit/ecc.rkt
   *
   * \see https://en.wikipedia.org/wiki/Orbital_eccentricity
   *
   * @param Vx horizontal velocity [m/s]
   * @param Vy vertical velocity [m/s]
   * @param altitude altitude, from the surface of the parent body [m]
   * @param parentBody the parent body
   */
  OrbitalEccentricity(double Vx, double Vy, double altitude,
                      CelestialBody *parentBody);
};

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

class Orbit;
class Atmosphere;

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

  /**
   * @brief stellar day [s]
   *
   */
  const double Trot_;

  /**
   * @brief planetary atmosphere
   *
   */
  const Atmosphere *atmosphere_;

  /**
   * @brief barycentric gravitational acceleration at given radius [m/s^2]
   *
   * \f$g = {{GM}\over{r^2}} = {\mu\over{r^2}}\f$
   *
   * @param alt altitude, from the surface of the parent body [m]
   *
   * \see https://en.wikipedia.org/wiki/Gravitational_acceleration
   */
  double GravitationalAcceleration(double alt) const;

  /**
   * @brief planet's angular rotation speed, at equator [m/s]
   *
   * \f$v = {{2\pi{R}}\over{T_{rot}}} = \omega{R}\f$
   *
   * \see https://en.wikipedia.org/wiki/Earth%27s_rotation#Angular_speed
   */
  double EquatorialSpeed() const;

  /**
   * @brief planet's angular rotation speed, at given latitude [m/s]
   *
   * \f$v = {{{2\pi{R}}\over{T_{rot}}}cos(\phi)} = {\omega{R}cos(\phi)}\f$
   *
   * @param latitude geographical latitude [deg]
   *
   * \see https://en.wikipedia.org/wiki/Earth%27s_rotation#Angular_speed
   */
  double EquatorialSpeed(double latitude) const;

  CelestialBody();
  CelestialBody(double mu, double R);
  CelestialBody(double mu, double R, double Trot);
  CelestialBody(double mu, double R, double Trot, Atmosphere *atmosphere);
};

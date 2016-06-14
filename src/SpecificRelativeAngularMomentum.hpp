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
 * @brief specific relative angular momentum class
 *
 * It is a constant vector for a given orbit under ideal conditions.
 *
 * \f$\vec{h} = \frac{\vec{L}}{m} = \vec{r}\times \vec{v}\f$
 *
 * \see https://en.wikipedia.org/wiki/Specific_relative_angular_momentum
 */
class SpecificRelativeAngularMomentum {
private:
  /**
   * @brief magnitude of the specific relative angular momentum [m^2/s]
   *
   */
  double value_;

public:
  /**
   * @brief magnitude of the specific relative angular momentum [m^2/s]
   *
   * @return double
   */
  operator double() const;

  /**
   * @brief dummy constructor.
   *
   */
  SpecificRelativeAngularMomentum();

  /**
   * @brief sets \f$h\f$ to the passed value
   *
   * @param srh magnitude of the specific relative angular momentum [m^2/s]
   */
  SpecificRelativeAngularMomentum(double srh);

  /**
   * @brief calculates \f$h\f$ from given velocity vector and altitude.
   *
   * \f$\vec{h} = \vec{r}\times \vec{v}\f$
   *
   * \f$h = \left \| \vec{h} \right \| \f$
   *
   * See math/orbit/srh.sage
   *
   * \see https://en.wikipedia.org/wiki/Orbital_eccentricity
   *
   * @param Vx horizontal velocity [m/s]
   * @param altitude altitude, from the surface of the parent body [m]
   * @param parentBody the parent body
   */
  SpecificRelativeAngularMomentum(double Vx, double altitude,
                                  CelestialBody *parentBody);
};

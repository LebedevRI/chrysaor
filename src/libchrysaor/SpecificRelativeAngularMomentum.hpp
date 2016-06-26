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
class SemiMajorAxis;
class OrbitalEccentricity;
class SpecificOrbitalEnergy;

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
  explicit SpecificRelativeAngularMomentum(double srh);

  /**
   * @brief calculates \f$h\f$ from given semi-major axis and orbital orbital
   * eccentricity.
   *
   * \f$h = \sqrt{(1-e^2)\mu{a}}\f$
   *
   * \see https://en.wikipedia.org/wiki/Orbital_eccentricity
   *
   * @param sma semi-major axis [m]
   * @param ecc eccentricity of the orbit
   * @param parentBody the parent body
   */
  SpecificRelativeAngularMomentum(SemiMajorAxis sma, OrbitalEccentricity ecc,
                                  const CelestialBody *parentBody);

  /**
   * @brief calculates \f$h\f$ from given specific orbital energy and orbital
   * orbital eccentricity.
   *
   * \f$e=\sqrt{1+{{2\epsilon{h^2}}\over{\mu^2}}}\f$
   *
   * \f$e^2={1+{{2\epsilon{h^2}}\over{\mu^2}}}\f$
   *
   * \f$e^2\mu^2={\mu^2+{2\epsilon{h^2}}}\f$
   *
   * \f${2\epsilon{h^2}} = {e^2\mu^2-\mu^2}\f$
   *
   * \f${h^2} = {{e^2\mu^2-\mu^2}\over{2\epsilon}}\f$
   *
   * \f$h = \sqrt{{e^2\mu^2-\mu^2}\over{2\epsilon}}\f$
   *
   * \see https://en.wikipedia.org/wiki/Orbital_eccentricity
   * \see https://en.wikipedia.org/wiki/Orbital_eccentricity
   *
   * @param epsilon specific orbital energy \f$\epsilon\f$ [J/kg] [m^2/s^2]
   * @param ecc eccentricity of the orbit
   * @param parentBody the parent body
   */
  SpecificRelativeAngularMomentum(SpecificOrbitalEnergy epsilon,
                                  OrbitalEccentricity ecc,
                                  const CelestialBody *parentBody);

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
                                  const CelestialBody *parentBody);
};

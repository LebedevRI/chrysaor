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
class SpecificOrbitalEnergy;
class SpecificRelativeAngularMomentum;

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
  explicit OrbitalEccentricity(double eccentricity);

  /**
   * @brief calculates \f$e\f$ from passed orbit's Ap and Pe.
   *
   * Since \f$r_p = a(1-e)\f$ and \f$r_a = a(1+e)\f$, where \f$a\f$ is the
   * semi-major axis:
   *
   * \f$e={{r_a-r_p}\over{r_a+r_p}}=1-{2\over{{r_a\over{r_p}}+1}}\f$
   *
   * See math/orbit/ecc-from-r1-and-r2-2.rkt
   *
   * \see https://en.wikipedia.org/wiki/Orbital_eccentricity
   *
   * @param ApR radius of the orbit, at the orbit's farthest point (apoapsis)
   * [m]
   * @param PeR radius of the orbit, at the orbit's nearest point (periapsis)
   * [m]
   */
  OrbitalEccentricity(double ApR, double PeR);

  /**
   * @brief calculates \f$e\f$ from passed orbit's Ap and Pe.
   *
   * Since \f$r_p = a(1-e)\f$ and \f$r_a = a(1+e)\f$, where \f$a\f$ is the
   * semi-major axis:
   *
   * \f$e={{r_a-r_p}\over{r_a+r_p}}=1-{2\over{{r_a\over{r_p}}+1}}\f$
   *
   * However, for the reasons of floating-point precision, we'll use
   * optimized version:
   * \f$e={{r_a-r_p}\over{r_a+r_p}}\f$. (the difference is in adding parent's
   * body radius only in the bottom)
   *
   * According to herbie, it is the most precise version given the
   * expected input data range (error = 0.0 bits).
   * See math/orbit/ecc-from-r1-and-r2.rkt
   *
   * \see https://en.wikipedia.org/wiki/Orbital_eccentricity
   *
   * @param ApA altitude, from the surface of the parent body, at the orbit's
   * farthest point (apoapsis) [m]
   * @param PeA altitude, from the surface of the parent body, at the orbit's
   * nearest point (eriapsis) [m]
   * @param parentBody the parent body
   */
  OrbitalEccentricity(double ApA, double PeA, const CelestialBody *parentBody);

  /**
   * @brief calculates \f$e\f$ from given length of semi-major axis and
   * specific relative angular momentum.
   *
   * \f$h = \sqrt{(1-e^2)a\mu}\f$
   *
   * \f$h^2 = {(1-e^2)a\mu}\f$
   *
   * \f$h^2 = {a\mu-a\mu{e^2}}\f$
   *
   * \f$a\mu{e^2} = {a\mu-h^2}\f$
   *
   * \f${e^2} = {{a\mu-h^2}\over{a\mu}}\f$
   *
   * \f$e = \sqrt{{a\mu-h^2}\over{a\mu}}\f$
   *
   * \see https://en.wikipedia.org/wiki/Orbital_eccentricity
   *
   * @param sma length of semi-major axis [m]
   * @param srh specific relative angular momentum [m^2/s]
   * @param parentBody the parent body
   */
  OrbitalEccentricity(SemiMajorAxis sma, SpecificRelativeAngularMomentum srh,
                      const CelestialBody *parentBody);

  /**
   * @brief calculates \f$e\f$ from given specific relative angular momentum and
   * specific orbital energy.
   *
   * \f$e=\sqrt{1+{{2\epsilon{h^2}}\over{\mu^2}}}\f$
   *
   * \see https://en.wikipedia.org/wiki/Orbital_eccentricity
   *
   * @param epsilon specific orbital energy \f$\epsilon\f$ [J/kg] [m^2/s^2]
   * @param srh specific relative angular momentum [m^2/s]
   * @param parentBody the parent body
   */
  OrbitalEccentricity(SpecificOrbitalEnergy epsilon,
                      SpecificRelativeAngularMomentum srh,
                      const CelestialBody *parentBody);

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
                      const CelestialBody *parentBody);
};

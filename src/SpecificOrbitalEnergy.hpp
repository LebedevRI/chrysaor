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

/**
 * @brief specific orbital energy class
 *
 * The specific orbital energy \f$\epsilon\f$ (or vis-viva energy)
 * of two orbiting bodies is the constant sum of their mutual potential
 * energy (\f$\epsilon _{p}\f$) and their total kinetic energy (\f$\epsilon
 * _{k}\f$), divided by the reduced mass.
 *
 * \f$\epsilon=\epsilon_{p}+\epsilon_{k}\f$
 *
 * \f$\epsilon={{v^2}\over{2}}-{{\mu}\over{r}}=-{\mu\over{2a}}\f$
 *
 * \see https://en.wikipedia.org/wiki/Specific_orbital_energy
 */
class SpecificOrbitalEnergy {
private:
  /**
   * @brief the specific orbital energy \f$\epsilon\f$ [J/kg] [m^2/s^2]
   *
   */
  double value_;

public:
  /**
   * @brief the specific orbital energy \f$\epsilon\f$ [J/kg] [m^2/s^2]
   *
   * @return double
   */
  operator double() const;

  /**
   * @brief dummy constructor.
   *
   */
  SpecificOrbitalEnergy();

  /**
   * @brief sets \f$\epsilon\f$ to the passed value
   *
   * @param epsilon specific orbital energy \f$\epsilon\f$ [J/kg] [m^2/s^2]
   */
  SpecificOrbitalEnergy(double epsilon);

  /**
   * @brief calculates \f$\epsilon\f$ from passed orbit's Ap and Pe.
   *
   * From the geometry of an ellipse, \f$2a=r_p+r_a\f$
   *
   * Vis-viva equation, orbital-energy-invariance law:
   * \f$\epsilon={{v^2}\over{2}}-{{\mu}\over{r}}=-{\mu\over{2a}}\f$
   *
   * We can substitute \f$2a\f$:
   *
   * \f$\epsilon=-{\mu\over{r_p+r_a}}\f$
   *
   * See math/orbit/soe-from-r1-and-r2.rkt
   *
   * @param ApA altitude, from the surface of the parent body, at the orbit's
   * farthest point (apoapsis) [m]
   * @param PeA altitude, from the surface of the parent body, at the orbit's
   * nearest point (eriapsis) [m]
   * @param parentBody the parent body
   */
  SpecificOrbitalEnergy(double ApA, double PeA, CelestialBody *parentBody);

  /**
   * @brief calculates \f$\epsilon\f$ from given velocity vector and altitude.
   *
   * By definition, given 2 velocity's components, \f$V_x\f$ and \f$V_y\f$,
   * the velocity magnitude is: \f$v = \sqrt{V_x^2+V_y^2}\f$.
   *
   * Vis-viva equation, orbital-energy-invariance law:
   * \f$\epsilon={{v^2}\over{2}}-{{\mu}\over{r}}=-{\mu\over{2a}}\f$
   *
   * Where, \f$v\f$ is the relative orbital speed,
   * \f$\mu\f$ is the standard gravitational parameter,
   * \f$r\f$ is the distance between the orbiting bodies, and
   * \f$a\f$ is the length of the semi-major axis.
   *
   * However, for the reasons of floating-point precision, we'll use
   * optimized version:
   * \f$\epsilon={{\left({{1\over2}{V_x^2}}+{{1\over2}{V_y}^2}\right)}-{{\mu}\over{r}}}\f$.
   *
   * According to herbie, it is the most precise version given the
   * expected input data range (error = 0.0 bits).
   * See math/orbit/soe.rkt
   *
   * \see https://en.wikipedia.org/wiki/Orbital_speed
   * \see https://en.wikipedia.org/wiki/Vis-viva_equation
   * \see https://en.wikipedia.org/wiki/Orbital_mechanics#Velocity
   * \see https://en.wikipedia.org/wiki/Specific_orbital_energy
   *
   * @param Vx horizontal velocity [m/s]
   * @param Vy vertical velocity [m/s]
   * @param altitude altitude, from the surface of the parent body [m]
   * @param parentBody the parent body
   */
  SpecificOrbitalEnergy(double Vx, double Vy, double altitude,
                        CelestialBody *parentBody);
};
